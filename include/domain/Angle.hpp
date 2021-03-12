#ifndef DOMAIN_ANGLE_HPP
#define DOMAIN_ANGLE_HPP

#include "domain/Vector.hpp"

namespace Domain {

struct Angle {
  float degree;

  float    toRad() const;
  Vector2f toVec() const;
};

} // namespace Domain

#endif // DOMAIN_ANGLE_HPP
