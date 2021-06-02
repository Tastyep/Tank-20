#ifndef DOMAIN_PHYSIC_SHAPE_HPP
#define DOMAIN_PHYSIC_SHAPE_HPP

namespace Domain::Physic {

enum class Shape {
  ConvexPolygon = 0,
  MultiConvexPolygon,
  Disk,
};

} // namespace Domain::Physic

#endif // DOMAIN_PHYSIC_SHAPE_HPP
