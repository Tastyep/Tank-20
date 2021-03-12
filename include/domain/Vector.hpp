#ifndef DOMAIN_VECTOR_HPP
#define DOMAIN_VECTOR_HPP

namespace Domain {

template <typename T>
struct Vector2 {
  T x;
  T y;
};

using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;
using Vector2f = Vector2<float>;

template <typename T>
inline Vector2<T> operator-(const Vector2<T> &right) {
  return Vector2<T>(-right.x, -right.y);
}

template <typename T>
inline Vector2<T> &operator+=(Vector2<T> &left, const Vector2<T> &right) {
  left.x += right.x;
  left.y += right.y;

  return left;
}

template <typename T>
inline Vector2<T> &operator-=(Vector2<T> &left, const Vector2<T> &right) {
  left.x -= right.x;
  left.y -= right.y;

  return left;
}

template <typename T>
inline Vector2<T> operator+(const Vector2<T> &left, const Vector2<T> &right) {
  return Vector2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
inline Vector2<T> operator-(const Vector2<T> &left, const Vector2<T> &right) {
  return Vector2<T>(left.x - right.x, left.y - right.y);
}

template <typename T>
inline Vector2<T> operator*(const Vector2<T> &left, T right) {
  return Vector2<T>(left.x * right, left.y * right);
}

template <typename T>
inline Vector2<T> operator*(T left, const Vector2<T> &right) {
  return Vector2<T>(right.x * left, right.y * left);
}

template <typename T>
inline Vector2<T> &operator*=(Vector2<T> &left, T right) {
  left.x *= right;
  left.y *= right;

  return left;
}

template <typename T>
inline Vector2<T> operator/(const Vector2<T> &left, T right) {
  return Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
inline Vector2<T> &operator/=(Vector2<T> &left, T right) {
  left.x /= right;
  left.y /= right;

  return left;
}

} // namespace Domain

#endif // DOMAIN_VECTOR_HPP
