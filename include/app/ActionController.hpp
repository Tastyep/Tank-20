#ifndef APP_ACTION_CONTROLLER_HPP
#define APP_ACTION_CONTROLLER_HPP

#include "domain/Action.hpp"
#include "domain/Vector.hpp"
#include "domain/component/Character.hpp"
#include "domain/component/Physic.hpp"

#include <PlayRho/Common/UnitVec.hpp>
#include <PlayRho/Common/Vector2.hpp>
#include <PlayRho/Common/Velocity.hpp>
#include <PlayRho/Dynamics/Body.hpp>
#include <PlayRho/Dynamics/World.hpp>
#include <PlayRho/Dynamics/WorldBody.hpp>
#include <entt/entity/registry.hpp>

#include <cmath>
#include <iostream>
#include <memory>

namespace App::Controller {
namespace {

namespace Component = Domain::Component;
using Domain::ActionCode;

} // namespace

class ActionController {
public:
  ActionController(std::shared_ptr<entt::registry>     registry,
                   std::shared_ptr<playrho::d2::World> world)
      : _registry(std::move(registry)), _world(std::move(world)) {}

  template <Domain::ActionCode code>
  void handle(const Domain::Action<code> &) requires(
      Domain::Action<code>::isMovement()) {
    auto view =
        _registry->view<const Component::Player, const Component::Body>();
    view.each([this](const auto & /* player */, const auto &bodyComp) {
      const auto force = (code == ActionCode::Forward) ? 5.F : -5.F;
      const auto speed = playrho::LinearVelocity2(force, 0);
      const auto velocity = playrho::d2::Rotate(
          speed, playrho::d2::GetTransformation(*_world, bodyComp.id).q);

      playrho::d2::SetVelocity(*_world, bodyComp.id, velocity);

      // kinematic.acceleration = force * kinematic.angle.toVec();
      // kinematic.velocity = kinematic.acceleration * dt;
      // position.value += kinematic.velocity * dt;
    });
    std::cout << "Movement action " << static_cast<int>(code) << '\n';
  }

  template <Domain::ActionCode code>
  void handle(const Domain::Action<code> &) requires(
      Domain::Action<code>::isRotation()) {

    auto view = _registry->view<const Component::Player, //
                                const Component::Body>();
    view.each([this](const auto & /* player */, const auto &bodyComp) {
      // const auto &body = _world->GetBody(bodyComp.id);

      const auto force = (code == ActionCode::RotateRight) ? 0.1F : -0.1F;

      const auto angle = playrho::d2::GetAngle(*_world, bodyComp.id);
      playrho::d2::SetAngle(*_world, bodyComp.id, angle + force);
      // playrho::d2::SetVelocity(
      //*_world, bodyComp.id,
      // playrho::d2::Rotate(
      // playrho::d2::GetLinearVelocity(*_world, bodyComp.id),
      // playrho::d2::GetTransformation(*_world, bodyComp.id).q));
    });
  }

  template <Domain::ActionCode code>
  void handle(const Domain::Action<code> &) {
    std::cout << "Use action " << static_cast<int>(code) << '\n';
  }

private:
  std::shared_ptr<entt::registry>     _registry;
  std::shared_ptr<playrho::d2::World> _world;
};

} // namespace App::Controller

#endif // APP_ACTION_CONTROLLER_HPP
