#ifndef APP_ACTION_CONTROLLER_HPP
#define APP_ACTION_CONTROLLER_HPP

#include "domain/Action.hpp"
#include "domain/Vector.hpp"
#include "domain/component/Character.hpp"
#include "domain/component/Physic.hpp"
#include <cmath>
#include <entt/entity/registry.hpp>
#include <iostream>
#include <memory>

namespace App::Controller {
namespace {

namespace Component = Domain::Component;
using Domain::ActionCode;

} // namespace

class ActionController {
public:
  ActionController(std::shared_ptr<entt::registry> registry)
      : _registry(std::move(registry)) {}

  template <Domain::ActionCode code>
  void handle(const Domain::Action<code> &) requires(
      Domain::Action<code>::isMovement()) {
    auto view = _registry->view<const Component::Player, Component::Kinematic,
                                Component::Position>();
    view.each([](const auto & /* player */, auto &kinematic, auto &position) {
      const auto force = (code == ActionCode::Forward) ? 1.F : -1.F;
      const auto dt = 3.0F;
      kinematic.acceleration = force * kinematic.angle.toVec();
      kinematic.velocity = kinematic.acceleration * dt;
      position.value += kinematic.velocity * dt;
    });
    std::cout << "Movement action " << static_cast<int>(code) << '\n';
  }
  template <Domain::ActionCode code>
  void handle(const Domain::Action<code> &) requires(
      Domain::Action<code>::isRotation()) {

    auto view = _registry->view<const Component::Player, //
                                Component::Kinematic>();
    view.each([](const auto & /* player */, auto &kinematic) {
      const auto force = (code == ActionCode::RotateRight) ? 1.F : -1.F;
      const auto dt = 3.0F;
      const auto angleStep = 1;
      kinematic.angle.degree += force * angleStep * dt;
    });

    std::cout << "Rotation action " << static_cast<int>(code) << '\n';
  }

  template <Domain::ActionCode code>
  void handle(const Domain::Action<code> &) {
    std::cout << "Use action " << static_cast<int>(code) << '\n';
  }

private:
  std::shared_ptr<entt::registry> _registry;
};

} // namespace App::Controller

#endif // APP_ACTION_CONTROLLER_HPP
