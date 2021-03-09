#include "interface/Tile.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace Interface {

void TileManager::load(const std::string &    path,
                       const Domain::IntRect &textureRect, int tileSize) {
  auto texture = std::make_unique<sf::Texture>();

  if (!texture->loadFromFile(path, {textureRect.left, textureRect.top,
                                    textureRect.width, textureRect.height})) {
    // Throw exception
  }

  for (int y = 0; y < textureRect.height; y += tileSize) {
    for (int x = 0; x < textureRect.width; x += tileSize) {
      _sprites.emplace_back(*texture, sf::IntRect{x, y, tileSize, tileSize});
    }
  }

  _textures.push_back(std::move(texture));
}

const sf::Sprite &TileManager::get(Domain::Sprite::ID spriteId) const {
  return _sprites[static_cast<size_t>(spriteId)];
}

} // namespace Interface
