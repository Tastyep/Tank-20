#ifndef INTERFACE_MAP_HPP
#define INTERFACE_MAP_HPP

#include "interface/Tile.hpp"
#include "interface/view/View.hpp"
#include <string>
#include <tmxlite/Map.hpp>

namespace Interface {

class Map : public View::View {
public:
  explicit Map(std::shared_ptr<TileManager> tileManager);

  bool load(const std::string &path);
  void render(sf::RenderWindow &window) override;

private:
  tmx::Map                     _map{};
  std::shared_ptr<TileManager> _tileManager;
};

} // namespace Interface

#endif // INTERFACE_MAP_HPP
