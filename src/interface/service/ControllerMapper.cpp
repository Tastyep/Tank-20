#include "interface/service/ControllerMapper.hpp"
#include "domain/Action.hpp"
#include "interface/Keyboard.hpp"

#include <algorithm>
#include <optional>

namespace Interface::Service {

using Keyboard::KeyCode;
ControllerMapper::ControllerMapper() {
  _keyMapping = {
      {KeyCode::W, Domain::ActionCode::Forward},
      {KeyCode::S, Domain::ActionCode::Backward},
      {KeyCode::A, Domain::ActionCode::RotateLeft},
      {KeyCode::D, Domain::ActionCode::RotateRight},
      {KeyCode::Space, Domain::ActionCode::Use},
  };

  for (const auto &[key, action] : _keyMapping) {
    _actionMappings[action] = key;
  }
}

std::optional<Domain::ActionCode>
ControllerMapper::operator[](Keyboard::KeyCode key) const {
  if (!_keyMapping.contains(key)) {
    return {};
  }
  return _keyMapping.at(key);
}

std::optional<Keyboard::KeyCode>
ControllerMapper::operator[](Domain::ActionCode code) const {
  if (!_actionMappings.contains(code)) {
    return {};
  }
  return _actionMappings.at(code);
}

void ControllerMapper::map(Keyboard::KeyCode key, Domain::ActionCode action) {
  const auto mappedKey = (*this)[action];
  const auto mappedAction = (*this)[key];
  if (mappedKey && mappedAction && *mappedKey == key &&
      *mappedAction == action) {
    return;
  }

  // Unbind the key from the previous action
  if (mappedAction) {
    _actionMappings.erase(*mappedAction);
  }

  // Unbind the previous key from the action
  if (mappedKey) {
    _keyMapping.erase(*mappedKey);
  }

  _keyMapping[key] = action;
  _actionMappings[action] = key;
}

} // namespace Interface::Service
