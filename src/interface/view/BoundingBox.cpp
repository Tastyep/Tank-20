#include "interface/view/BoundingBox.hpp"
#include "domain/Angle.hpp"
#include "domain/Coordinate.hpp"
#include "domain/component/Graphic.hpp"
#include "domain/component/Physic.hpp"

#include <PlayRho/Collision/Shapes/DiskShapeConf.hpp>
#include <PlayRho/Collision/Shapes/MultiShapeConf.hpp>
#include <PlayRho/Collision/Shapes/PolygonShapeConf.hpp>
#include <PlayRho/Collision/Shapes/Shape.hpp>
#include <PlayRho/Common/Math.hpp>
#include <PlayRho/Common/Transformation.hpp>
#include <PlayRho/Common/TypeInfo.hpp>
#include <PlayRho/Dynamics/Body.hpp>
#include <PlayRho/Dynamics/BodyConf.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/VertexArray.hpp>
#include <memory>
#include <utility>

namespace Interface::View {

BoundingBox::BoundingBox(std::shared_ptr<entt::registry>     registry,
                         std::shared_ptr<playrho::d2::World> world)
    : _registry(std::move(registry)), //
      _world(std::move(world)) {}

void BoundingBox::render(sf::RenderWindow &window) {
  namespace Component = Domain::Component;
  const auto view = _registry->view<const Component::Body>();

  for (const auto &[entity, bodyComp] : view.each()) {
    const auto &body = _world->GetBody(bodyComp.id);
    const auto &fixtures = _world->GetFixtures(bodyComp.id);
    const auto &transformation = body.GetTransformation();

    for (const auto &fixtureId : fixtures) {
      const auto &fixture = _world->GetFixture(fixtureId);
      const auto &shape = fixture.shape;
      const auto  type = playrho::d2::GetType(shape);
      if (type == playrho::GetTypeID<playrho::d2::MultiShapeConf>()) {
        auto conf =
            playrho::d2::TypeCast<const playrho::d2::MultiShapeConf>(shape);
        const auto hullCount = playrho::d2::GetChildCount(conf);
        for (auto i = decltype(hullCount){0}; i < hullCount; ++i) {
          this->drawPolygon(window, playrho::d2::GetChild(conf, i),
                            transformation);
        }
      } else if (type == playrho::GetTypeID<playrho::d2::PolygonShapeConf>()) {
        auto conf =
            playrho::d2::TypeCast<const playrho::d2::PolygonShapeConf>(shape);
        this->drawPolygon(window, playrho::d2::GetChild(conf, 0),
                          transformation);
      } else if (type == playrho::GetTypeID<playrho::d2::DiskShapeConf>()) {
        auto conf =
            playrho::d2::TypeCast<const playrho::d2::DiskShapeConf>(shape);
        this->drawCircle(window, conf, transformation);
      }
    }
  }
}

void BoundingBox::drawPolygon(sf::RenderWindow &                 window,
                              const playrho::d2::DistanceProxy & polygon,
                              const playrho::d2::Transformation &xfm) {
  const auto      vertexCount = polygon.GetVertexCount();
  sf::VertexArray lines(sf::LineStrip, vertexCount + 1);

  for (auto i = decltype(vertexCount){0}; i < vertexCount; ++i) {
    const auto vertex = playrho::d2::Transform(polygon.GetVertex(i), xfm);
    const auto pixelCoor =
        Domain::Coordinate::toPixel<float>({vertex[0], vertex[1]});
    lines[i].position = {pixelCoor.x, pixelCoor.y};
  }
  lines[vertexCount].position = lines[0].position;

  window.draw(lines);
}

void BoundingBox::drawCircle(sf::RenderWindow &                 window,
                             const playrho::d2::DiskShapeConf & shape,
                             const playrho::d2::Transformation &xfm) {
  const auto center = playrho::d2::Transform(shape.GetLocation(), xfm);
  const auto pixelCoor =
      Domain::Coordinate::toPixel<float>({center[0], center[1]});
  const auto radius = shape.GetRadius();

  sf::CircleShape circle(radius);
  circle.setPosition({pixelCoor.x - radius, pixelCoor.y - radius});
  circle.setOutlineThickness(1);
  circle.setFillColor({0, 0, 0, 0});
  circle.setOutlineColor({0xFF, 0xFF, 0xFF, 0xFF});
  window.draw(circle);
}

} // namespace Interface::View
