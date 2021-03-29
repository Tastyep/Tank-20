#include "interface/Map.hpp"
#include "domain/Sprite.hpp"
#include "interface/Tile.hpp"
#include <iostream>
#include <memory>
#include <tmxlite/TileLayer.hpp>

namespace Interface {

Map::Map(std::shared_ptr<TileManager> tileManager)
    : _tileManager(std::move(tileManager)) {}

bool Map::load(const std::string &path) {
  if (!_map.load(path)) {
    return false;
  }

  const auto &tileSets = _map.getTilesets();
  for (const auto &tileSet : tileSets) {
    const auto &tileSetPath = tileSet.getImagePath();
    const auto &tileSize = tileSet.getTileSize();
    const auto  tileCount = tileSet.getTileCount();
    const auto  columnCount = tileSet.getColumnCount();
    if (!_tileManager->load(tileSetPath, {tileSize.x, tileSize.y}, tileCount,
                            columnCount)) {
      return false;
    }
  }
  return true;
}

void Map::render(sf::RenderWindow &window) {
  const auto &layers = _map.getLayers();
  const auto  tileCount = _map.getTileCount();
  const auto &tileSize = _map.getTileSize();

  for (const auto &layer : layers) {
    const auto &tileLayer = layer->getLayerAs<tmx::TileLayer>();
    const auto &tiles = tileLayer.getTiles();

    for (unsigned int y = 0; y < tileCount.y; ++y) {
      for (unsigned int x = 0; x < tileCount.x; ++x) {
        const auto tile = tiles[y * tileCount.x + x];
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

} // namespace Interface
