#ifndef INTERFACE_EVENT_HPP
#define INTERFACE_EVENT_HPP

#include "Utility.hpp"
#include "interface/Keyboard.hpp"
#include <SFML/Window/Event.hpp>
#include <variant>

namespace Interface::Event {

template <typename Source>
struct Pressed {
  Source source;
};

struct Key {
  Keyboard::KeyCode code;
  bool              alt;
  bool              control;
  bool              shift;
  bool              system;
};

struct WindowClosed {};

using Type = std::variant<std::monostate, WindowClosed, Pressed<Key>>;

struct Converter {
  static Type fromSFML(const sf::Event &e) {
    switch (e.type) {
    case sf::Event::Closed:
      return WindowClosed{};
    case sf::Event::KeyPressed:
      return Pressed<Key>{
          .source = {.code = Keyboard::KeyCode{enum_cast(e.key.code)},
                     .alt = e.key.alt,
                     .control = e.key.control,
                     .shift = e.key.shift,
                     .system = e.key.system}};
    default:
      return std::monostate{};
    }
  }
};
} // namespace Interface::Event

#endif // INTERFACE_EVENT_HPP
