#ifndef DOMAIN_ACTION_HPP
#define DOMAIN_ACTION_HPP

#include <variant>

namespace Domain {

enum class ActionCode {
  Forward = 0,
  Backward,
  RotateLeft,
  RotateRight,
  Use,
  Count, // The number of action code
};

template <ActionCode c>
struct Action {
  constexpr static ActionCode code = c;

  [[nodiscard]] consteval static bool isMovement() {
    return c == ActionCode::Forward || c == ActionCode::Backward;
  }
  [[nodiscard]] consteval static bool isRotation() {
    return c == ActionCode::RotateLeft || c == ActionCode::RotateRight;
  }
};

using ActionV =
    std::variant<Action<ActionCode::Forward>, Action<ActionCode::Backward>,
                 Action<ActionCode::RotateLeft>,
                 Action<ActionCode::RotateRight>, Action<ActionCode::Use>>;

ActionV actionFromCode(ActionCode code);

} // namespace Domain

#endif // DOMAIN_ACTION_HPP
