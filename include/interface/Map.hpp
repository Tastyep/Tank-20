#ifndef INTERFACE_MAP_HPP
#define INTERFACE_MAP_HPP

#include "domain/Vector.hpp"
#include "domain/physic/ShapeConfManager.hpp"
#include "interface/Tile.hpp"
#include "interface/view/View.hpp"

#include <tmxlite/Map.hpp>

#include <string>
#include <utility>
#include <vector>

namespace Interface {

class Map : public View::View {
public:
  explicit Map(std::shared_ptr<TileManager> tileManager);

  void render(sf::RenderWindow &window) override;
  bool load(const std::string &                               path,
            std::shared_ptr<Domain::Physic::ShapeConfManager> shapeConfManager);

private:
  std::pair<Domain::Vector2f, float> parseEllipse(const tmx::Object &object);
  std::vector<Domain::Vector2f>      parsePolygon(const tmx::Object &object);
  std::vector<Domain::Vector2f>      parseRectangle(const tmx::Object &object);
  std::vector<std::vector<Domain::Vector2f>>
  parseMultiPolygon(const std::vector<tmx::Object> &objects);

private:
  tmx::Map                     _map{};
  std::shared_ptr<TileManager> _tileManager;
};

} // namespace Interface

#endif // INTERFACE_MAP_HPP
