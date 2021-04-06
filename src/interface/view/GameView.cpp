#include "interface/view/GameView.hpp"
#include "domain/Angle.hpp"
#include "domain/Coordinate.hpp"
#include "domain/component/Graphic.hpp"
#include "domain/component/Physic.hpp"

#include <PlayRho/Dynamics/Body.hpp>
#include <PlayRho/Dynamics/BodyConf.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <utility>

namespace Interface::View {

GameView::GameView(std::shared_ptr<entt::registry>     registry,
                   std::shared_ptr<playrho::d2::World> world,
                   std::shared_ptr<TileManager>        tileManager)
    : _registry(std::move(registry)), //
      _world(std::move(world)),       //
      _tileManager(std::move(tileManager)) {}

void GameView::render(sf::RenderWindow &window) {
  namespace Component = Domain::Component;
  const auto view =
      _registry->view<const Component::Body, const Component::Sprite>();

  for (const auto &[entity, bodyComp, spriteComp] : view.each()) {
    const auto &tile =
        _tileManager->getTile(static_cast<size_t>(spriteComp.id));
    auto sprite = sf::Sprite(*tile.texture, tile.textureRect);
    // const auto bound = sprite.getLocalBounds();

    const auto &body = _world->GetBody(bodyComp.id);
    const auto &transformation = body.GetTransformation();
    const auto &pos = transformation.p;
    const auto &dir = transformation.q;
    const auto  pixelPos = Domain::Coordinate::toPixel<float>({pos[0], pos[1]});

    // sprite.setOrigin(bound.width / 2.F, bound.height / 2.F);
    sprite.setPosition(pixelPos.x, pixelPos.y);
    sprite.setRotation(Domain::Angle(dir[0], dir[1]).degree);

    window.draw(sprite);
  }
}

} // namespace Interface::View
