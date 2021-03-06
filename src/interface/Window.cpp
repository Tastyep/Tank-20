#include "interface/Window.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
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

void Window::render() {
  ImGui::SFML::Update(_window, sf::milliseconds(10));
  ImGui::SFML::Render(_window);
  _window.display();
}

} // namespace Interface
