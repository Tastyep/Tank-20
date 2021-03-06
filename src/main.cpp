#include "Utility.hpp"
#include "app/GameState.hpp"
#include "interface/Event.hpp"
#include "interface/Window.hpp"

#include <chrono>
#include <spdlog/spdlog.h>

#include <iostream>
#include <string>
#include <variant>

int main() {
  using Clock = App::GameState::Clock;

  Interface::Window window(1400, 800, "My window");
  App::GameState    gs{};
  const auto        fps = 60;
  const auto        renderDelta = std::chrono::milliseconds(1000) / fps;

  namespace Event = Interface::Event;
  while (window.isOpen()) {
    const auto event = window.nextEvent();
    std::visit(
        Overloaded{
            [&](const Event::WindowClosed & /* unused */) { window.close(); },
            [&](const Event::Pressed<Event::Key> &e) {
              spdlog::info("Pressed key {}", e.source.code);
            },
            [](const auto & /* unused */) {},
        },
        event);
    if (!window.isOpen()) {
      return 0;
    }

    const auto cuTime = Clock::now();
    if (cuTime - gs.lastRender < renderDelta) {
      continue;
    }
    gs.lastRender = cuTime;
    window.render();
  }
}
