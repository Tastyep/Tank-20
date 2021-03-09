#include "domain/entity/Factory.hpp"
#include "domain/component/Position.hpp"
#include "domain/component/Sprite.hpp"

namespace Domain::Entity {

Factory::Factory(std::shared_ptr<entt::registry> registry)
    : _registry(std::move(registry)) {}

entt::entity Factory::wall(const Vector2i &pos, Sprite::ID spriteID) {
  auto e = _registry->create();
  _registry->emplace<Component::Position>(e, pos.x, pos.y);
  _registry->emplace<Component::Sprite>(e, spriteID);

  return e;
}

entt::entity Factory::tank(const Vector2i &pos, Sprite::ID spriteID) {
  auto e = _registry->create();
  _registry->emplace<Component::Position>(e, pos.x, pos.y);
  _registry->emplace<Component::Sprite>(e, spriteID);

  return e;
}

} // namespace Domain::Entity
