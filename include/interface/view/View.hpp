#ifndef INTERFACE_VIEW_VIEW_HPP
#define INTERFACE_VIEW_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

namespace Interface::View {

class View {
public:
  virtual ~View() = default;

  virtual void render(sf::RenderWindow &window) = 0;
};

} // namespace Interface::View

#endif // INTERFACE_VIEW_VIEW_HPP
