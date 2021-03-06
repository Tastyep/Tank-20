#include "domain/Action.hpp"
#include "Utility.hpp"
#include <array>
#include <string_view>

namespace Domain {
namespace {

const std::array<ActionV, static_cast<size_t>(ActionCode::Count)> kMapping = {
    Action<ActionCode::Forward>{},    Action<ActionCode::Backward>{},
    Action<ActionCode::RotateLeft>{}, Action<ActionCode::RotateRight>{},
    Action<ActionCode::Use>{},
};

const std::array<std::string_view, static_cast<size_t>(ActionCode::Count)>
    kActionNames = {
        "Forward", "Backward", "RotateLeft", "RotateRight", "Use",
};

} // namespace

std::string_view actionName(ActionCode code) {
  return kActionNames[static_cast<size_t>(code)];
}

Domain::ActionV actionFromCode(ActionCode code) {
  return kMapping[static_cast<size_t>(code)];
}

} // namespace Domain
