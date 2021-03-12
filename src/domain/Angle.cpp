#include "domain/Angle.hpp"
#include <cmath>
#include <numbers>

namespace Domain {

float Angle::toRad() const {
  return static_cast<float>(std::numbers::pi) * this->degree / 180.F;
}

Vector2f Angle::toVec() const {
  const auto rad = this->toRad();
  return {std::cos(rad), std::sin(rad)};
}

} // namespace Domain
