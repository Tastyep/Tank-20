#ifndef INTERFACE_TILE_HPP
#define INTERFACE_TILE_HPP

#include "domain/Shape.hpp"
#include "domain/Sprite.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include <vector>

namespace Interface {

class TileManager {
public:
  void load(const std::string &path, const Domain::IntRect &textureRect,
            int tileSize);

  const sf::Sprite &get(Domain::Sprite::ID spriteId) const;

private:
  std::vector<sf::Sprite>                   _sprites;
  std::vector<std::unique_ptr<sf::Texture>> _textures{};
};

} // namespace Interface

#endif // INTERFACE_TILE_HPP
