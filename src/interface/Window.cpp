#include "interface/Window.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <chrono>
#include <imgui-SFML.h>
#include <imgui.h>

namespace Interface {

Window::Window(unsigned int width, unsigned int height, std::string_view name)
    : _window(sf::VideoMode(width, height), std::string(name)) {
  //_window.setVerticalSyncEnabled(true);
  ImGui::SFML::Init(_window);
}

void Window::close() {
  _window.close();
  ImGui::SFML::Shutdown();
}

Event::Type Window::nextEvent() {
  if (sf::Event event{}; _window.pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);

    return Event::Converter::fromSFML(event);
  }

  return std::monostate{};

  // ImGui::Begin("Sample window"); // begin window

  //// Window title text edit
  // ImGui::InputText("Window title", windowTitle, 255);

  // if (ImGui::Button("Update window title")) {
  //// this code gets if user clicks on the button
  //// yes, you could have written if(ImGui::InputText(...))
  //// but I do this to show how buttons work :)
  //_window.setTitle(windowTitle);
  //}
  // ImGui::End(); // end _window
}

void Window::addView(std::shared_ptr<View::View> view) {
  _views.push_back(std::move(view));
}

void Window::render(std::chrono::nanoseconds elapsed) {
  ImGui::SFML::Update(
      _window,
      sf::microseconds(
          std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)
              .count()));
  _window.clear(sf::Color{0xFF, 0xFF, 0xFF});
  for (auto &view : _views) {
    view->render(_window);
  }

  ImGui::SFML::Render(_window);
  _window.display();
}

} // namespace Interface
