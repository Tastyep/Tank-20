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
#include "interface/controller/EventController.hpp"
#include "interface/service/ControllerMapper.hpp"
#include "interface/view/Control.hpp"
#include "interface/view/Fps.hpp"
#include "interface/view/GameView.hpp"

#include <spdlog/spdlog.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <variant>

int main() {
  Interface::Window window(1400, 800, "My window");
  // App::GameState                    gs{};
  auto registry = std::make_shared<entt::registry>();
  App::Controller::ActionController actionController(registry);
  const auto                        stepDelta = 30;
  const auto timestep = std::chrono::milliseconds(1000) / stepDelta;
  std::chrono::nanoseconds acc{0};
  Domain::Timer            timer;

  auto tileManager = std::make_shared<Interface::TileManager>();
  Domain::Entity::Factory entFactory(registry);
  auto                    map = std::make_shared<Interface::Map>(tileManager);
  map->load("../asset/map.tmx");
  entFactory.tank({32, 32});

  namespace Event = Interface::Event;
  auto controllerMapper =
      std::make_shared<Interface::Service::ControllerMapper>();
  Interface::Controller::EventController eventCtrler(controllerMapper);

  window.addView(map);
  window.addView(
      std::make_unique<Interface::View::GameView>(registry, tileManager));
  window.addView(
      std::make_unique<Interface::View::Fps>(std::chrono::milliseconds(250)));
  window.addView(std::make_unique<Interface::View::Control>(controllerMapper));

  while (window.isOpen()) {
    auto        elapsed = timer.restart();
    Event::Type event{};

    acc += elapsed;
    while (acc >= timestep) {
      for (event = window.nextEvent(); !isEmptyVariant(event);
           event = window.nextEvent()) {
        eventCtrler.processEvent(event);

        std::visit(Overloaded{
                       [&](const Event::WindowClosed & /* unused */) {
                         window.close();
                       },
                       [](const auto & /* unused */) {},
                   },
                   event);
      }

      for (const auto &action : eventCtrler.actions()) {
        const auto handler = [&actionController](const auto &act) {
          actionController.handle(act);
        };
        std::visit(handler, action);
      }

      acc -= timestep;

      if (!window.isOpen()) {
        return 0;
      }
    }

    window.render(elapsed);
  }
}
