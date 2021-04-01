#ifndef INTERFACE_VIEW_BOUNDING_BOX_HPP
#define INTERFACE_VIEW_BOUNDING_BOX_HPP

#include "interface/Tile.hpp"
#include "interface/view/View.hpp"

#include <PlayRho/Collision/Shapes/DiskShapeConf.hpp>
#include <PlayRho/Dynamics/World.hpp>
#include <entt/entity/registry.hpp>

#include <memory>

namespace playrho::d2 {

class DiskShapeConf;

} // namespace playrho::d2

namespace Interface::View {

class BoundingBox final : public View {
public:
  BoundingBox(std::shared_ptr<entt::registry>     registry,
              std::shared_ptr<playrho::d2::World> world);
  ~BoundingBox() override = default;

  BoundingBox(const BoundingBox &) = delete;
  BoundingBox(BoundingBox &&) = default;
  BoundingBox &operator=(const BoundingBox &) = delete;
  BoundingBox &operator=(BoundingBox &&) = default;

  void render(sf::RenderWindow &window) override;

private:
  void drawPolygon(sf::RenderWindow &                 window,
                   const playrho::d2::DistanceProxy & polygon,
                   const playrho::d2::Transformation &xfm);
  void drawCircle(sf::RenderWindow &                 window,
                  const playrho::d2::DiskShapeConf & shape,
                  const playrho::d2::Transformation &xfm);

private:
  std::shared_ptr<entt::registry>     _registry;
  std::shared_ptr<playrho::d2::World> _world;
};

} // namespace Interface::View

#endif // INTERFACE_VIEW_BOUNDING_BOX_HPP
