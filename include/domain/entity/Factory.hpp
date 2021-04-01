#ifndef DOMAIN_ENTITY_FACTORY_HPP
#define DOMAIN_ENTITY_FACTORY_HPP

#include "domain/Vector.hpp"
#include "domain/entity/Identity.hpp"
#include "domain/physic/ShapeConfManager.hpp"

#include <PlayRho/PlayRho.hpp>
#include <entt/entity/registry.hpp>
#include <memory>

namespace Domain::Entity {

class Factory {
public:
  Factory(std::shared_ptr<entt::registry>           registry,
          std::shared_ptr<playrho::d2::World>       world,
          std::shared_ptr<Physic::ShapeConfManager> shapeConfManager);

  entt::entity wall(const Vector2f &pos, Entity::ID id);
  entt::entity tank(const Vector2f &pos);

private:
  std::shared_ptr<entt::registry>           _registry;
  std::shared_ptr<playrho::d2::World>       _world;
  std::shared_ptr<Physic::ShapeConfManager> _shapeConfManager;
};

} // namespace Domain::Entity

#endif // DOMAIN_ENTITY_FACTORY_HPP
