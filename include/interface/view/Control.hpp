#ifndef INTERFACE_VIEW_CONTROL_HPP
#define INTERFACE_VIEW_CONTROL_HPP

#include "Utility.hpp"
#include "interface/service/ControllerMapper.hpp"
#include "interface/view/View.hpp"
#include <memory>

namespace Interface::View {

class Control final : public View {
public:
  explicit Control(std::shared_ptr<Service::ControllerMapper> controllerMapper);
  ~Control() override = default;

  Control(const Control &) = delete;
  Control(Control &&) = default;
  Control &operator=(const Control &) = delete;
  Control &operator=(Control &&) = default;

  void render(sf::RenderWindow &window) override;

private:
  void _refreshKeyBuffers();

private:
  std::shared_ptr<Service::ControllerMapper> _controllerMapper;
  std::array<std::string, enum_cast(Domain::ActionCode::Count)> _keyBuffers;
};

} // namespace Interface::View

#endif // INTERFACE_VIEW_CONTROL_HPP
