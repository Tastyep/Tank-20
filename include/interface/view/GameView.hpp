#ifndef INTERFACE_VIEW_GAME_VIEW_HPP
#define INTERFACE_VIEW_GAME_VIEW_HPP

#include "interface/Tile.hpp"
#include "interface/view/View.hpp"
#include <entt/entity/registry.hpp>
#include <memory>

namespace Interface::View {

class GameView final : public View {
public:
  GameView(std::shared_ptr<entt::registry> registry,
           std::shared_ptr<TileManager>    tileManager);
  ~GameView() override = default;

  GameView(const GameView &) = delete;
  GameView(GameView &&) = default;
  GameView &operator=(const GameView &) = delete;
  GameView &operator=(GameView &&) = default;

  void render(sf::RenderWindow &window) override;

private:
  std::shared_ptr<entt::registry> _registry;
  std::shared_ptr<TileManager>    _tileManager;
};

} // namespace Interface::View

#endif // INTERFACE_VIEW_GAME_VIEW_HPP
