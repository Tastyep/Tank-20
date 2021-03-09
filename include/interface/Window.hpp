#ifndef INTERFACE_WINDOW_HPP
#define INTERFACE_WINDOW_HPP

#include "interface/Event.hpp"
#include "interface/view/View.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string_view>
#include <vector>

namespace Interface {

class Window final {
public:
  Window(unsigned int width, unsigned int height, std::string_view name);

  void        close();
  inline bool isOpen() { return _window.isOpen(); }

  Event::Type nextEvent();

  void addView(std::unique_ptr<View::View> view);
  void render();

private:
  sf::RenderWindow                         _window;
  std::vector<std::unique_ptr<View::View>> _views;
};

} // namespace Interface

#endif // INTERFACE_WINDOW_HPP
