#ifndef INTERFACE_EVENT_CONTROLLER_HPP
#define INTERFACE_EVENT_CONTROLLER_HPP

#include "Utility.hpp"
#include "domain/Action.hpp"
#include "interface/Event.hpp"
#include <array>
#include <vector>

namespace Interface::Controller {

class EventController {
private:
  struct ActionAttr {
    bool state{false};
  };

public:
  void                         processEvent(Event::Type event);
  std::vector<Domain::ActionV> actions();

private:
  void process(const Event::Pressed<Event::Key> &e);
  void process(const Event::Released<Event::Key> &e);
  void process(const auto & /* e */){};

  std::array<ActionAttr, enum_cast(Domain::ActionCode::Count)> _actionAttrs;
};

} // namespace Interface::Controller

#endif // INTERFACE_EVENT_CONTROLLER_HPP
