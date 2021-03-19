#include "interface/controller/EventController.hpp"
#include <unordered_map>
#include <variant>

namespace Interface::Controller {

EventController::EventController(
    std::shared_ptr<Service::ControllerMapper> controllerMapper)
    : _controllerMapper(std::move(controllerMapper)) {}

void EventController::processEvent(const Event::Type event) {
  return std::visit([this](const auto &e) { this->process(e); }, event);
}

std::vector<Domain::ActionV> EventController::actions() {
  std::vector<Domain::ActionV> actions;
  for (size_t i = 0; i < _actionAttrs.size(); ++i) {
    if (_actionAttrs[i].state) {
      actions.emplace_back(
          Domain::actionFromCode(Domain::ActionCode{static_cast<int>(i)}));
    }
  }

  return actions;
}

void EventController::process(const Event::Pressed<Event::Key> &e) {
  const auto actionCode = (*_controllerMapper)[e.source.code];
  if (actionCode) {
    _actionAttrs[enum_cast<Domain::ActionCode, size_t>(actionCode.value())]
        .state = true;
  }
}

void EventController::process(const Event::Released<Event::Key> &e) {
  const auto actionCode = (*_controllerMapper)[e.source.code];
  if (actionCode) {
    _actionAttrs[enum_cast<Domain::ActionCode, size_t>(actionCode.value())]
        .state = false;
  }
}

} // namespace Interface::Controller
