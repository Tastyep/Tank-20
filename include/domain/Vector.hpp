#ifndef DOMAIN_VECTOR_HPP
#define DOMAIN_VECTOR_HPP

namespace Domain {

template <typename T>
struct Vector2D {
  T x;
  T y;
};

using Vector2i = Vector2D<int>;

} // namespace Domain

#endif // DOMAIN_VECTOR_HPP
