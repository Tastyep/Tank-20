#include "interface/view/GameView.hpp"
#include "domain/component/Graphic.hpp"
#include "domain/component/Physic.hpp"
#include <utility>

namespace Interface::View {

GameView::GameView(std::shared_ptr<entt::registry> registry,
                   std::shared_ptr<TileManager>    tileManager)
    : _registry(std::move(registry)), _tileManager(std::move(tileManager)) {}

void GameView::render(sf::RenderWindow &window) {
  namespace Component = Domain::Component;
  const auto view =
      _registry->view<const Component::Position, const Component::Kinematic,
                      const Component::Sprite>();

  for (const auto &[entity, pos, kinematic, sprite] : view.each()) {
    auto       tile = _tileManager->get(sprite.id);
    const auto bound = tile.getLocalBounds();

    tile.setOrigin(bound.width / 2.F, bound.height / 2.F);
    tile.setPosition(pos.value.x + bound.width / 2.F,
                     pos.value.y + bound.height / 2.F);
    tile.setRotation(kinematic.angle.degree);
    window.draw(tile);
  }
}

} // namespace Interface::View
