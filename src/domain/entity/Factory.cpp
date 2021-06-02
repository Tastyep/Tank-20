#include "domain/entity/Factory.hpp"
#include "domain/component/Character.hpp"
#include "domain/component/Graphic.hpp"
#include "domain/component/Physic.hpp"

#include <PlayRho/Dynamics/BodyConf.hpp>
#include <PlayRho/Dynamics/BodyType.hpp>
#include <PlayRho/Dynamics/FixtureConf.hpp>

namespace Domain::Entity {

Factory::Factory(std::shared_ptr<entt::registry>           registry,
                 std::shared_ptr<playrho::d2::World>       world,
                 std::shared_ptr<Physic::ShapeConfManager> shapeConfManager)
    : _registry(std::move(registry)), _world(std::move(world)),
      _shapeConfManager(std::move(shapeConfManager)) {}

entt::entity Factory::wall(const Vector2f &pos, Entity::ID id) {
  const auto bodyId =
      _world->CreateBody(playrho::d2::BodyConf{}
                             .UseType(playrho::BodyType::Dynamic)
                             .UseLocation({pos.x, pos.y}));
  auto       shapeConf = _shapeConfManager->get(id);
  const auto fixtureId =
      _world->CreateFixture(playrho::d2::FixtureConf{}.UseBody(bodyId).UseShape(
          std::move(shapeConf)));

  auto e = _registry->create();
  _registry->emplace<Component::Body>(e, bodyId, fixtureId);
  _registry->emplace<Component::Sprite>(e, id);

  return e;
}

entt::entity Factory::tank(const Vector2f &pos) {
  auto       shapeConf = _shapeConfManager->get(Entity::ID::Tank);
  const auto bodyId =
      _world->CreateBody(playrho::d2::BodyConf{}
                             .UseType(playrho::BodyType::Kinematic)
                             .UseLocation({pos.x, pos.y}));

  const auto fixtureId = _world->CreateFixture(
      playrho::d2::FixtureConf{}.UseBody(bodyId).UseShape(shapeConf));

  auto e = _registry->create();
  _registry->emplace<Component::Player>(e);
  _registry->emplace<Component::Body>(e, bodyId, fixtureId);
  _registry->emplace<Component::Sprite>(e, Entity::ID::Tank);

  return e;
}

} // namespace Domain::Entity
