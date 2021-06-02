#include "interface/Tile.hpp"
#include "domain/Vector.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace Interface {

bool TileManager::load(const std::string &     path,
                       const Domain::Vector2u &tileSize, unsigned int tileCount,
                       unsigned int columnCount) {
  auto texture = std::make_shared<sf::Texture>();

  if (!texture->loadFromFile(path)) {
    return false;
  }

  const auto rowCount = tileCount / columnCount;
  for (unsigned int y = 0; y < rowCount; ++y) {
    for (unsigned int x = 0; x < columnCount; ++x) {
      _tiles.emplace_back(texture, sf::IntRect{
                                       static_cast<int>(x * tileSize.x),
                                       static_cast<int>(y * tileSize.y),
                                       static_cast<int>(tileSize.x),
                                       static_cast<int>(tileSize.y),
                                   });
    }
  }

  return true;
}

const Tile &TileManager::getTile(size_t id) const { return _tiles.at(id); }

} // namespace Interface
