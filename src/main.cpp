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
#include "interface/Tile.hpp"
#include "interface/Window.hpp"
#include "interface/view/Fps.hpp"
#include "interface/view/GameView.hpp"

#include <chrono>
#include <spdlog/spdlog.h>
#include <thread>

#include <fstream>
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

void loadMap(Domain::Entity::Factory &entFactory, std::string_view path) {
  std::ifstream file(path.data());

  if (!file.is_open()) {
    // throw exception
    return;
  }
  std::string              lineData;
  std::vector<std::string> content;
  while (getline(file, lineData)) {
    content.push_back(std::move(lineData));
  }

  for (size_t y = 0; y < content.size(); ++y) {
    const auto &line = content[y];
    for (size_t x = 0; x < line.size(); ++x) {
      const Domain::Vector2i pos{static_cast<int>(x) * 32,
                                 static_cast<int>(y) * 32};
      switch (line[x]) {
      case '-':
        entFactory.wall(pos, Domain::Sprite::ID::RLWall);
        break;
      case '|':
        entFactory.wall(pos, Domain::Sprite::ID::UDWall);
        break;
      case 'T':
        entFactory.tank(pos, Domain::Sprite::ID::Tank);
        break;
      default:
        break;
      }
    }
  }
  file.close();
}

int main() {
  Interface::Window window(1400, 800, "My window");
  // App::GameState                    gs{};
  App::Controller::ActionController actionController{};
  const auto                        fps = 60;
  const auto    renderDelta = std::chrono::milliseconds(1000) / fps;
  Domain::Timer timer;

  auto tileManager = std::make_shared<Interface::TileManager>();
  tileManager->load("../asset/asset.png", {0, 0, 384, 64}, 32);

  auto                    registry = std::make_shared<entt::registry>();
  Domain::Entity::Factory entFactory(registry);
  loadMap(entFactory, "../asset/map.txt");

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

    window.render();
    const auto elapsed = timer.elapsed();
    if (elapsed < renderDelta) {
      std::this_thread::sleep_for(renderDelta - elapsed);
    }
  }
}
