#include "Utility.hpp"
#include "app/ActionController.hpp"
#include "app/GameState.hpp"
#include "domain/Action.hpp"
#include "domain/Concept.hpp"
#include "domain/Timer.hpp"
#include "domain/entity/Factory.hpp"
#include "domain/entity/Identity.hpp"
#include "domain/physic/ShapeConfManager.hpp"
#include "interface/Event.hpp"
#include "interface/Keyboard.hpp"
#include "interface/Map.hpp"
#include "interface/Tile.hpp"
#include "interface/Window.hpp"
#include "interface/controller/EventController.hpp"
#include "interface/service/ControllerMapper.hpp"
#include "interface/view/BoundingBox.hpp"
#include "interface/view/Control.hpp"
#include "interface/view/Fps.hpp"
#include "interface/view/GameView.hpp"

#include <PlayRho/Dynamics/StepConf.hpp>
#include <memory>
#include <spdlog/spdlog.h>

#include <PlayRho/PlayRho.hpp>

#include <chrono>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <variant>

int main() {
  Interface::Window window(1400, 800, "My window");

  // world definition
  auto world = std::make_shared<playrho::d2::World>();

  const auto stepDelta = 60;
  const auto timestep = std::chrono::milliseconds(1000) / stepDelta;
  const auto stepConf = playrho::StepConf{.deltaTime = 1.f / stepDelta};
  std::chrono::nanoseconds acc{0};
  Domain::Timer            timer;

  // App::GameState                    gs{};
  auto registry = std::make_shared<entt::registry>();
  App::Controller::ActionController actionController(registry, world);

  // Graphical resource loading
  auto tileManager = std::make_shared<Interface::TileManager>();
  auto shapeConfManager = std::make_shared<Domain::Physic::ShapeConfManager>();
  Domain::Entity::Factory entFactory(registry, world, shapeConfManager);
  auto                    map = std::make_shared<Interface::Map>(tileManager);
  map->load("../asset/map.tmx", shapeConfManager);
  entFactory.tank({1, 1});

  // Controller mapping
  namespace Event = Interface::Event;
  auto controllerMapper =
      std::make_shared<Interface::Service::ControllerMapper>();
  Interface::Controller::EventController eventCtrler(controllerMapper);

  // Views
  window.addView(map);
  window.addView(std::make_unique<Interface::View::GameView>(registry, world,
                                                             tileManager));
  window.addView(
      std::make_unique<Interface::View::Fps>(std::chrono::milliseconds(250)));
  window.addView(std::make_unique<Interface::View::Control>(controllerMapper));
  window.addView(
      std::make_unique<Interface::View::BoundingBox>(registry, world));

  // Game loop
  while (window.isOpen()) {
    auto        elapsed = timer.restart();
    Event::Type event{};

    acc += elapsed;
    while (acc >= timestep) {
      for (event = window.nextEvent(); !isEmptyVariant(event);
           event = window.nextEvent()) {
        eventCtrler.processEvent(event);

        if (std::holds_alternative<Event::WindowClosed>(event)) {
          window.close();
          return 0;
        }
      }

      for (const auto &action : eventCtrler.actions()) {
        const auto handler = [&actionController](const auto &act) {
          actionController.handle(act);
        };
        std::visit(handler, action);
      }

      playrho::d2::Step(*world, stepConf);

      acc -= timestep;
    }

    window.render(elapsed);
  }
}
