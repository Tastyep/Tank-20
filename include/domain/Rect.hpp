#ifndef DOMAIN_SHAPE_HPP
#define DOMAIN_SHAPE_HPP

namespace Domain {

template <typename T>
struct Rect {
public:
  Rect() = default;
  Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight)
      : left(rectLeft), top(rectTop), width(rectWidth), height(rectHeight){};

  T left;
  T top;
  T width;
  T height;
};

using IntRect = Rect<int>;

} // namespace Domain

#endif // DOMAIN_SHAPE_HPP
