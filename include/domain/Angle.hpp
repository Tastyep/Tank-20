#ifndef DOMAIN_ANGLE_HPP
#define DOMAIN_ANGLE_HPP

#include "domain/Vector.hpp"

namespace Domain {

struct Angle {
  Angle(float x, float y);

  float    toRad() const;
  Vector2f toVec() const;

  float degree;
};

} // namespace Domain

#endif // DOMAIN_ANGLE_HPP
