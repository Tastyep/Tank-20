#include "interface/controller/EventController.hpp"
#include "domain/Action.hpp"
#include "interface/Keyboard.hpp"
#include <iostream>
#include <unordered_map>
#include <variant>

namespace Interface::Controller {

using KeyCode = Keyboard::KeyCode;
const std::unordered_map<KeyCode, Domain::ActionCode> keyMapping{
    {KeyCode::W, Domain::ActionCode::Forward},
    {KeyCode::S, Domain::ActionCode::Backward},
    {KeyCode::A, Domain::ActionCode::RotateLeft},
    {KeyCode::D, Domain::ActionCode::RotateRight},
    {KeyCode::Space, Domain::ActionCode::Use},
};

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
  const auto actionCode = keyMapping.find(e.source.code);
  if (actionCode != keyMapping.end()) {
    _actionAttrs[enum_cast<Domain::ActionCode, size_t>(actionCode->second)]
        .state = true;
  }
}

void EventController::process(const Event::Released<Event::Key> &e) {
  const auto actionCode = keyMapping.find(e.source.code);
  if (actionCode != keyMapping.end()) {
    _actionAttrs[enum_cast<Domain::ActionCode, size_t>(actionCode->second)]
        .state = false;
  }
}

} // namespace Interface::Controller
