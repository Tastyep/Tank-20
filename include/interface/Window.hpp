#ifndef INTERFACE_WINDOW_HPP
#define INTERFACE_WINDOW_HPP

#include "interface/Event.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string_view>

namespace Interface {

class Window final {
public:
  Window(unsigned int width, unsigned int height, std::string_view name);

  void close();
  Event::Type nextEvent();
  void render();
  inline bool isOpen() { return _window.isOpen(); }

private:
  sf::RenderWindow _window;
};

} // namespace Interface

#endif // INTERFACE_WINDOW_HPP
