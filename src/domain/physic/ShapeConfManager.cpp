#include "domain/physic/ShapeConfManager.hpp"

#include <PlayRho/Collision/Shapes/DiskShapeConf.hpp>
#include <PlayRho/Collision/Shapes/MultiShapeConf.hpp>
#include <PlayRho/Collision/Shapes/PolygonShapeConf.hpp>
#include <PlayRho/Common/Vector2.hpp>
#include <PlayRho/Common/VertexSet.hpp>

#include <algorithm>
#include <utility>

namespace Domain::Physic {

using playrho::d2::DiskShapeConf;
using playrho::d2::MultiShapeConf;
using playrho::d2::PolygonShapeConf;
using playrho::d2::Shape;

void ShapeConfManager::load(Entity::ID                   id,
                            const std::vector<Vector2f> &polygon) {
  auto                          conf = PolygonShapeConf{};
  std::vector<playrho::Length2> vertices;

  vertices.reserve(polygon.size());
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(vertices),
                 [](const auto &v) {
                   return playrho::Length2{v.x, v.y};
                 });

  conf.UseVertices(vertices);
  _shapes[id] = Shape{std::move(conf)};
}

void ShapeConfManager::load(
    Entity::ID id, const std::vector<std::vector<Vector2f>> &polygons) {
  auto conf = MultiShapeConf{};

  for (const auto &polygon : polygons) {
    playrho::d2::VertexSet vertices;

    for (const auto &vertex : polygon) {
      vertices.add({vertex.x, vertex.y});
    }

    conf.AddConvexHull(vertices);
  }

  _shapes[id] = Shape{std::move(conf)};
}

void ShapeConfManager::load(Entity::ID id, const Vector2f &center,
                            float radius) {
  auto conf = DiskShapeConf{};

  conf.UseLocation({center.x, center.y});
  conf.UseRadius(radius);
  _shapes[id] = Shape{std::move(conf)};
}

const playrho::d2::Shape &ShapeConfManager::get(Entity::ID id) const {
  return _shapes.at(id);
}

} // namespace Domain::Physic
