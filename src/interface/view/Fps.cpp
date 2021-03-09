#include "interface/view/Fps.hpp"
#include <imgui.h>

#include <iostream>

namespace Interface::View {

Fps::Fps(std::chrono::milliseconds refreshRate)
    : _refreshRate(refreshRate), _lastRefresh(Domain::Clock::now()) {}

void Fps::render(sf::RenderWindow & /* window */) {
  const auto now = Domain::Clock::now();
  const auto delta = now - _lastRefresh;
  if (delta > _refreshRate) {
    _lastRefresh = now;
    _frameRate =
        _frameCount *
        static_cast<unsigned int>(
            1'000'000 /
            std::chrono::duration_cast<std::chrono::milliseconds>(delta)
                .count()) /
        1000;
    _frameCount = 0;
  } else {
    ++_frameCount;
  }

  ImGui::Begin("HUD");
  ImGui::Text("FPS: %d", _frameRate);
  ImGui::End();
}

} // namespace Interface::View
