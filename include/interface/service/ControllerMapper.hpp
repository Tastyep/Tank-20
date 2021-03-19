#ifndef INTERFACE_SERVICE_CONTROLLER_MAPPER_HPP
#define INTERFACE_SERVICE_CONTROLLER_MAPPER_HPP

#include "domain/Action.hpp"
#include "interface/Keyboard.hpp"

#include <optional>
#include <unordered_map>

namespace Interface::Service {

class ControllerMapper {
public:
  ControllerMapper();

  std::optional<Domain::ActionCode> operator[](Keyboard::KeyCode key) const;
  std::optional<Keyboard::KeyCode>  operator[](Domain::ActionCode code) const;
  void map(Keyboard::KeyCode key, Domain::ActionCode action);

private:
  std::unordered_map<Keyboard::KeyCode, Domain::ActionCode> _keyMapping;
  std::unordered_map<Domain::ActionCode, Keyboard::KeyCode> _actionMappings;
};

} // namespace Interface::Service

#endif // INTERFACE_SERVICE_CONTROLLER_MAPPER_HPP
