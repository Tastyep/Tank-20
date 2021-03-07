#include "Utility.hpp"
#include "app/ActionController.hpp"
#include "app/GameState.hpp"
#include "domain/Action.hpp"
#include "interface/Event.hpp"
#include "interface/Keyboard.hpp"
#include "interface/Window.hpp"

#include <chrono>
#include <spdlog/spdlog.h>

#include <iostream>
#include <optional>
#include <string>
#include <variant>

std::optional<Domain::ActionV>
eventToAction(const Interface::Event::Type event) {
  namespace Event = Interface::Event;
  using KeyCode = Interface::Keyboard::KeyCode;
  using Act = Domain::ActionCode;
  return std::visit(
      Overloaded{
          [](const Event::Pressed<Event::Key> &e)
              -> std::optional<Domain::ActionV> {
            switch (e.source.code) {
            case KeyCode::W:
              return Domain::Action<Act::Forward>{};
            case KeyCode::S:
              return Domain::Action<Act::Backward>{};
            case KeyCode::A:
              return Domain::Action<Act::Left>{};
            case KeyCode::D:
              return Domain::Action<Act::Right>{};
            case KeyCode::Space:
              return Domain::Action<Act::Use>{};
            default:
              return std::nullopt;
            }
          },
          [](const auto & /* unused */) -> std::optional<Domain::ActionV> {
            return std::nullopt;
          },
      },
      event);
}

int main() {
  using Clock = App::GameState::Clock;

  Interface::Window                 window(1400, 800, "My window");
  App::GameState                    gs{};
  App::Controller::ActionController actionController{};
  const auto                        fps = 60;
  const auto renderDelta = std::chrono::milliseconds(1000) / fps;

  namespace Event = Interface::Event;
  while (window.isOpen()) {
    const auto event = window.nextEvent();

    if (!isEmptyVariant(event)) {
      const auto action = eventToAction(event);

      if (action) {
        const auto handler = [&actionController](const auto &act) {
          actionController.handle(act);
        };
        std::visit(handler, *action);
      }

      std::visit(
          Overloaded{
              [&](const Event::WindowClosed & /* unused */) { window.close(); },
              [](const auto & /* unused */) {},
          },
          event);
    }
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
