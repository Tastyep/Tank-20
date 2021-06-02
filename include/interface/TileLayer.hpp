#ifndef INTERFACE_TILE_LAYER_HPP
#define INTERFACE_TILE_LAYER_HPP

#include "domain/Vector.hpp"
#include "interface/Tile.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <memory>

namespace Interface {

class TileLayer : public sf::Drawable {
public:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void addTile(const Tile &tile, const Domain::Vector2u &pos);

private:
  using TextureLayer =
      std::unordered_map<std::shared_ptr<sf::Texture>, sf::VertexArray>;

  TextureLayer _layers;
};

} // namespace Interface

#endif // INTERFACE_TILE_LAYER_HPP
