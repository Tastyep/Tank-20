#include "domain/Angle.hpp"
#include <cmath>
#include <numbers>

namespace Domain {

constexpr auto piDeg = 180.F;

Angle::Angle(float x, float y)
    : degree(std::atan2(y, x) * piDeg / static_cast<float>(std::numbers::pi)) {}

float Angle::toRad() const {
  return static_cast<float>(std::numbers::pi) * this->degree / piDeg;
}

Vector2f Angle::toVec() const {
  const auto rad = this->toRad();
  return {std::cos(rad), std::sin(rad)};
}

} // namespace Domain
