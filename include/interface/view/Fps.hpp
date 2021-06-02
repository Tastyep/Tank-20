#ifndef INTERFACE_VIEW_FPS_HPP
#define INTERFACE_VIEW_FPS_HPP

#include "domain/Concept.hpp"
#include "interface/view/View.hpp"
#include <chrono>

namespace Interface::View {

class Fps final : public View {
public:
  explicit Fps(std::chrono::milliseconds refreshRate);
  ~Fps() override = default;

  Fps(const Fps &) = delete;
  Fps(Fps &&) = default;
  Fps &operator=(const Fps &) = delete;
  Fps &operator=(Fps &&) = default;

  void render(sf::RenderWindow &window) override;

private:
  std::chrono::milliseconds _refreshRate;
  Domain::TimePoint         _lastRefresh;
  unsigned int              _frameCount{0};
  unsigned int              _frameRate{0};
};

} // namespace Interface::View

#endif // INTERFACE_VIEW_FPS_HPP
