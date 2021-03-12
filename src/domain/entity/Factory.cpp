#include "domain/entity/Factory.hpp"
#include "domain/component/Character.hpp"
#include "domain/component/Graphic.hpp"
#include "domain/component/Physic.hpp"

namespace Domain::Entity {

Factory::Factory(std::shared_ptr<entt::registry> registry)
    : _registry(std::move(registry)) {}

entt::entity Factory::wall(const Vector2i &pos, Sprite::ID spriteID) {
  auto e = _registry->create();
  _registry->emplace<Component::Position>(e, pos.x, pos.y);
  _registry->emplace<Component::Sprite>(e, spriteID);

  return e;
}

entt::entity Factory::tank(const Vector2i &pos) {
  auto e = _registry->create();
  _registry->emplace<Component::Player>(e);
  _registry->emplace<Component::Position>(
      e, Vector2f{static_cast<float>(pos.x), static_cast<float>(pos.y)});
  _registry->emplace<Component::Kinematic>(e, Vector2f{0, 0}, Vector2f{0, 0},
                                           Angle{0.F});
  _registry->emplace<Component::Sprite>(e, Sprite::ID::Tank);

  return e;
}

} // namespace Domain::Entity
