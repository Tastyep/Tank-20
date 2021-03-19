#ifndef INTERFACE_EVENT_CONTROLLER_HPP
#define INTERFACE_EVENT_CONTROLLER_HPP

#include "Utility.hpp"
#include "domain/Action.hpp"
#include "interface/Event.hpp"
#include "interface/service/ControllerMapper.hpp"
#include <array>
#include <memory>
#include <vector>

namespace Interface::Controller {

class EventController {
private:
  struct ActionAttr {
    bool state{false};
  };

public:
  explicit EventController(
      std::shared_ptr<Service::ControllerMapper> controllerMapper);

  void                         processEvent(Event::Type event);
  std::vector<Domain::ActionV> actions();

private:
  void process(const Event::Pressed<Event::Key> &e);
  void process(const Event::Released<Event::Key> &e);
  void process(const auto & /* e */){};

  std::shared_ptr<Service::ControllerMapper> _controllerMapper;
  std::array<ActionAttr, enum_cast(Domain::ActionCode::Count)> _actionAttrs;
};

} // namespace Interface::Controller

#endif // INTERFACE_EVENT_CONTROLLER_HPP
