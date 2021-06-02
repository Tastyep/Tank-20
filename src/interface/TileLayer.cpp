#include "interface/TileLayer.hpp"
#include "domain/Vector.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Interface {

void TileLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (const auto &[texture, vertices] : _layers) {
    states.texture = texture.get();
    target.draw(vertices, states);
  }
}

void TileLayer::addTile(const Tile &tile, const Domain::Vector2u &pos) {
  auto &      vertices = _layers[tile.texture];
  const auto  vertexCount = vertices.getVertexCount();
  const auto &rect = tile.textureRect;

  vertices.setPrimitiveType(sf::Quads);
  vertices.resize(vertexCount + 4);
  sf::Vertex *quad = &vertices[vertexCount];

  quad[0].position =
      sf::Vector2f(sf::Vector2u{pos.x * static_cast<unsigned>(rect.width),
                                pos.y * static_cast<unsigned>(rect.height)});
  quad[1].position =
      sf::Vector2f(sf::Vector2u{(pos.x + 1) * static_cast<unsigned>(rect.width),
                                pos.y * static_cast<unsigned>(rect.height)});
  quad[2].position = sf::Vector2f(
      sf::Vector2u{(pos.x + 1) * static_cast<unsigned>(rect.width),
                   (pos.y + 1) * static_cast<unsigned>(rect.height)});
  quad[3].position = sf::Vector2f(
      sf::Vector2u{pos.x * static_cast<unsigned>(rect.width),
                   (pos.y + 1) * static_cast<unsigned>(rect.height)});

  quad[0].texCoords = sf::Vector2f(sf::Vector2i{rect.left, rect.top});
  quad[1].texCoords =
      sf::Vector2f(sf::Vector2i{rect.left + rect.width, rect.top});
  quad[2].texCoords = sf::Vector2f(
      sf::Vector2i{rect.left + rect.width, rect.top + rect.height});
  quad[3].texCoords =
      sf::Vector2f(sf::Vector2i{rect.left, rect.top + rect.height});
}

} // namespace Interface
