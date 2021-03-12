#ifndef DOMAIN_COMPONENT_PHYSIC_HPP
#define DOMAIN_COMPONENT_PHYSIC_HPP

#include "domain/Angle.hpp"
#include "domain/Vector.hpp"

namespace Domain::Component {

struct Position {
  Vector2f value;
};

struct Kinematic {
  Vector2f velocity;
  Vector2f acceleration;
  Angle    angle;
};

} // namespace Domain::Component

#endif // DOMAIN_COMPONENT_PHYSIC_HPP
