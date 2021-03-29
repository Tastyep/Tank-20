#ifndef INTERFACE_TILE_HPP
#define INTERFACE_TILE_HPP

#include "domain/Vector.hpp"
#include "domain/entity/Identity.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include <vector>

namespace Interface {

class TileManager {
public:
  bool load(const std::string &path, const Domain::Vector2u &tileSize,
            unsigned int tileCount, unsigned int columnCount);

  const sf::Sprite &get(Domain::Entity::ID spriteId) const;

private:
  std::vector<sf::Sprite>                   _sprites;
  std::vector<std::unique_ptr<sf::Texture>> _textures{};
};

} // namespace Interface

#endif // INTERFACE_TILE_HPP
