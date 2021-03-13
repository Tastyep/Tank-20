#include "domain/Action.hpp"
#include "Utility.hpp"
#include <array>

namespace Domain {
namespace {

const std::array<ActionV, static_cast<size_t>(ActionCode::Count)> kMapping = {
    Action<ActionCode::Forward>{},    Action<ActionCode::Backward>{},
    Action<ActionCode::RotateLeft>{}, Action<ActionCode::RotateRight>{},
    Action<ActionCode::Use>{},
};

}

Domain::ActionV actionFromCode(ActionCode code) {
  return kMapping[static_cast<size_t>(code)];
}

} // namespace Domain
