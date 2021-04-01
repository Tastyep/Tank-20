#ifndef DOMAIN_DOORDINATE_HPP
#define DOMAIN_DOORDINATE_HPP

#include "domain/Vector.hpp"

namespace Domain::Coordinate {

constexpr auto kMeterSize = 32U;

template <typename T>
constexpr Vector2f toMeter(const Vector2<T> &pixel) {
  return {static_cast<float>(pixel.x) / kMeterSize,
          static_cast<float>(pixel.y) / kMeterSize};
}

template <typename T = int>
constexpr Vector2<T> toPixel(const Vector2f &meter) {
  return {static_cast<T>(meter.x) * kMeterSize,
          static_cast<T>(meter.y) * kMeterSize};
}

} // namespace Domain::Coordinate

#endif // DOMAIN_DOORDINATE_HPP
