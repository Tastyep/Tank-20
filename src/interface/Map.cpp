#include "interface/Map.hpp"
#include "domain/Coordinate.hpp"
#include "domain/Vector.hpp"
#include "domain/entity/Factory.hpp"
#include "domain/entity/Identity.hpp"
#include "interface/Tile.hpp"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <memory>

#include <tmxlite/Object.hpp>
#include <tmxlite/TileLayer.hpp>

namespace Interface {

Map::Map(std::shared_ptr<TileManager> tileManager)
    : _tileManager(std::move(tileManager)) {}

bool Map::load(
    const std::string &                               path,
    std::shared_ptr<Domain::Physic::ShapeConfManager> shapeConfManager,
    std::shared_ptr<Domain::Entity::Factory>          entityFactory) {
  if (!_map.load(path)) {
    return false;
  }

  // TODO: Check that id doesn't become bigger than Count(EntityId)
  std::vector<std::uint32_t> entityTileIds;
  const auto &               tileSets = _map.getTilesets();
  for (size_t id = 0; const auto &tileSet : tileSets) {
    const auto &tileSetPath = tileSet.getImagePath();
    const auto &tileSize = tileSet.getTileSize();
    const auto  tileCount = tileSet.getTileCount();
    const auto  columnCount = tileSet.getColumnCount();
    if (!_tileManager->load(tileSetPath, {tileSize.x, tileSize.y}, tileCount,
                            columnCount)) {
      return false;
    }

    const auto &tiles = tileSet.getTiles();
    for (const auto &tile : tiles) {
      const auto &objects = tile.objectGroup.getObjects();

      // const auto &properties = tile.properties;
      // for (const auto &property : properties) {
      // std::cout << property.getName() << " " << property.getStringValue()
      //<< '\n';
      //}

      if (objects.size() > 1) {
        const auto polygons = this->parseMultiPolygon(objects);
        shapeConfManager->load(static_cast<Domain::Entity::ID>(id), polygons);
      } else {
        for (const auto &object : objects) {
          switch (object.getShape()) {
          case tmx::Object::Shape::Ellipse: {
            const auto [center, radius] = this->parseEllipse(object);
            shapeConfManager->load(static_cast<Domain::Entity::ID>(id), center,
                                   radius);
            break;
          }
          case tmx::Object::Shape::Polygon: {
            const auto polygon = this->parsePolygon(object);
            shapeConfManager->load(static_cast<Domain::Entity::ID>(id),
                                   polygon);
            break;
          }
          case tmx::Object::Shape::Rectangle: {
            const auto polygon = this->parseRectangle(object);
            shapeConfManager->load(static_cast<Domain::Entity::ID>(id),
                                   polygon);
            break;
          }
          default:
            // error: unsuported shape
            break;
          }
        }
      }
      // Only increment the entityID if collision objects are available
      if (!objects.empty()) {
        ++id;
        entityTileIds.push_back(tile.ID);
      }
    }
  }

  const auto &layers = _map.getLayers();
  const auto &tileSize = _map.getTileSize();
  const auto  tileCount = _map.getTileCount();
  for (const auto &layer : layers) {
    const auto &tileLayer = layer->getLayerAs<tmx::TileLayer>();
    const auto &tiles = tileLayer.getTiles();

    for (unsigned int y = 0; y < tileCount.y; ++y) {
      for (unsigned int x = 0; x < tileCount.x; ++x) {
        const auto &tile = tiles[y * tileCount.x + x];
        // Empty tile or no associated object
        if (tile.ID == 0 ||
            std::find(entityTileIds.begin(), entityTileIds.end(), tile.ID) ==
                entityTileIds.end()) {
          continue;
        }

        const auto entityId = static_cast<Domain::Entity::ID>(tile.ID - 1);
        if (entityId >= Domain::Entity::ID::URDLWall &&
            entityId <= Domain::Entity::ID::BallWall) {

          entityFactory->wall(Domain::Coordinate::toMeter(Domain::Vector2u{
                                  x * tileSize.x, y * tileSize.y}),
                              entityId);
        }
      }
    }
  }

  return true;
}

void Map::render(sf::RenderWindow &window) {
  const auto &layers = _map.getLayers();
  const auto &tileSize = _map.getTileSize();
  const auto  tileCount = _map.getTileCount();

  for (const auto &layer : layers) {
    const auto &tileLayer = layer->getLayerAs<tmx::TileLayer>();
    const auto &tiles = tileLayer.getTiles();

    for (unsigned int y = 0; y < tileCount.y; ++y) {
      for (unsigned int x = 0; x < tileCount.x; ++x) {
        const auto &tile = tiles[y * tileCount.x + x];
        if (tile.ID == 0) { // Empty
          continue;
        }

        auto sprite = _tileManager->get(
            Domain::Entity::ID{static_cast<int>(tile.ID) - 1});
        sprite.setPosition(static_cast<float>(x * tileSize.x),
                           static_cast<float>(y * tileSize.y));
        window.draw(sprite);
      }
    }
  }
}

// private

std::pair<Domain::Vector2f, float>
Map::parseEllipse(const tmx::Object &object) {
  const auto &pos = object.getPosition();
  const auto &box = object.getAABB();
  if (box.width != box.height) {
    // throw exception
  }

  const auto radius = box.width / 2;
  return {Domain::Coordinate::toMeter<float>({pos.x + radius, pos.y + radius}),
          radius};
}

std::vector<Domain::Vector2f> Map::parsePolygon(const tmx::Object &object) {
  const auto &                  points = object.getPoints();
  std::vector<Domain::Vector2f> vertices{};

  vertices.reserve(points.size());
  std::transform(points.begin(), points.end(), std::back_inserter(vertices),
                 [](const auto &v) {
                   return Domain::Coordinate::toMeter<float>({v.x, v.y});
                 });
  return vertices;
}

std::vector<Domain::Vector2f> Map::parseRectangle(const tmx::Object &object) {
  const auto &box = object.getAABB();
  return {
      Domain::Coordinate::toMeter<float>({box.left, box.top}),
      Domain::Coordinate::toMeter<float>({box.left + box.width, box.top}),
      Domain::Coordinate::toMeter<float>(
          {box.left + box.width, box.top + box.height}),
      Domain::Coordinate::toMeter<float>({box.left, box.top + box.height}),
  };
}

std::vector<std::vector<Domain::Vector2f>>
Map::parseMultiPolygon(const std::vector<tmx::Object> &objects) {
  std::vector<std::vector<Domain::Vector2f>> polygons;

  for (const auto &object : objects) {
    switch (object.getShape()) {
    case tmx::Object::Shape::Polygon:
      polygons.push_back(this->parsePolygon(object));
      break;
    case tmx::Object::Shape::Rectangle:
      polygons.push_back(this->parseRectangle(object));
      break;
    default:
      // error: unsuported shape, must be a convex polygon
      break;
    }
  }

  return polygons;
}

} // namespace Interface
