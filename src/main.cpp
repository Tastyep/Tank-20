#include "Utility.hpp"
#include "app/ActionController.hpp"
#include "app/GameState.hpp"
#include "domain/Action.hpp"
#include "domain/Concept.hpp"
#include "domain/Sprite.hpp"
#include "domain/Timer.hpp"
#include "domain/entity/Factory.hpp"
#include "interface/Event.hpp"
#include "interface/Keyboard.hpp"
#include "interface/Map.hpp"
#include "interface/Tile.hpp"
#include "interface/Window.hpp"
#include "interface/view/Fps.hpp"
#include "interface/view/GameView.hpp"

#include <spdlog/spdlog.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <thread>
#include <variant>

std::optional<Domain::ActionV>
eventToAction(const Interface::Event::Type event) {
  namespace Event = Interface::Event;
  using KeyCode = Interface::Keyboard::KeyCode;
  using Act = Domain::ActionCode;

  return std::visit(
      Overloaded{
          [&](const Event::Pressed<Event::Key> &e)
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
  Interface::Window window(1400, 800, "My window");
  // App::GameState                    gs{};
  App::Controller::ActionController actionController{};
  const auto                        fps = 60;
  const auto    renderDelta = std::chrono::milliseconds(1000) / fps;
  Domain::Timer timer;

  auto tileManager = std::make_shared<Interface::TileManager>();
  auto registry = std::make_shared<entt::registry>();
  Domain::Entity::Factory entFactory(registry);
  auto                    map = std::make_shared<Interface::Map>(tileManager);
  map->load("../asset/map.tmx");

  window.addView(map);
  window.addView(
      std::make_unique<Interface::View::GameView>(registry, tileManager));
  window.addView(
      std::make_unique<Interface::View::Fps>(std::chrono::milliseconds(250)));

  namespace Event = Interface::Event;
  while (window.isOpen()) {
    timer.restart();
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

    const auto elapsed = timer.elapsed();
    window.render(elapsed);
    if (elapsed < renderDelta) {
      std::this_thread::sleep_for(renderDelta - elapsed);
    }
  }
}
