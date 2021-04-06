#ifndef INTERFACE_TILE_HPP
#define INTERFACE_TILE_HPP

#include "domain/Vector.hpp"
#include "domain/entity/Identity.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Interface {

struct Tile {
  std::shared_ptr<sf::Texture> texture;
  sf::IntRect                  textureRect;
};

class TileManager {
public:
  bool load(const std::string &path, const Domain::Vector2u &tileSize,
            unsigned int tileCount, unsigned int columnCount);

  const Tile &getTile(size_t id) const;

private:
  std::vector<Tile> _tiles;
};

} // namespace Interface

#endif // INTERFACE_TILE_HPP
