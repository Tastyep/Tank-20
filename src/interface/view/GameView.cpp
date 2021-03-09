#include "interface/view/GameView.hpp"
#include "domain/component/Position.hpp"
#include "domain/component/Sprite.hpp"
#include <utility>

namespace Interface::View {

GameView::GameView(std::shared_ptr<entt::registry> registry,
                   std::shared_ptr<TileManager>    tileManager)
    : _registry(std::move(registry)), _tileManager(std::move(tileManager)) {}

void GameView::render(sf::RenderWindow &window) {
  namespace Component = Domain::Component;
  const auto view = _registry->view<Component::Position, Component::Sprite>();

  for (const auto &[entity, pos, sprite] : view.each()) {
    auto tile = _tileManager->get(sprite.id);
    tile.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
    window.draw(tile);
  }
}

} // namespace Interface::View
