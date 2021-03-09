#ifndef DOMAIN_ENTITY_FACTORY_HPP
#define DOMAIN_ENTITY_FACTORY_HPP

#include "domain/Sprite.hpp"
#include "domain/Vector.hpp"

#include <entt/entity/registry.hpp>
#include <memory>

namespace Domain::Entity {

class Factory {
public:
  Factory(std::shared_ptr<entt::registry> registry);

  entt::entity wall(const Vector2i &pos, Sprite::ID spriteID);
  entt::entity tank(const Vector2i &pos, Sprite::ID spriteID);

private:
  std::shared_ptr<entt::registry> _registry;
};

} // namespace Domain::Entity

#endif // DOMAIN_ENTITY_FACTORY_HPP
