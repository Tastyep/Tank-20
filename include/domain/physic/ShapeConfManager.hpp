#ifndef DOMAIN_PHYSIC_SHAPE_CONF_MANAGER
#define DOMAIN_PHYSIC_SHAPE_CONF_MANAGER

#include "domain/Vector.hpp"
#include "domain/entity/Identity.hpp"

#include <PlayRho/Collision/Shapes/Shape.hpp>

#include <unordered_map>

namespace Domain::Physic {

class ShapeConfManager {
public:
  void load(Entity::ID id, const std::vector<Vector2f> &polygon);
  void load(Entity::ID id, const std::vector<std::vector<Vector2f>> &polygons);
  void load(Entity::ID id, const Vector2f &center, float radius);

  const playrho::d2::Shape &get(Entity::ID id) const;

private:
  std::unordered_map<Entity::ID, playrho::d2::Shape> _shapes;
};

} // namespace Domain::Physic

#endif // DOMAIN_PHYSIC_SHAPE_CONF_MANAGER
