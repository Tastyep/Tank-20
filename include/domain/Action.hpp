#ifndef DOMAIN_ACTION_HPP
#define DOMAIN_ACTION_HPP

#include <variant>

namespace Domain {

enum class ActionCode {
  Forward = 0,
  Backward,
  Left,
  Right,
  Use,
};

template <ActionCode c>
struct Action {
  constexpr static Action code = c;

  [[nodiscard]] consteval static bool isMovement() {
    return c >= ActionCode::Forward && c <= ActionCode::Right;
  }
};

using ActionV =
    std::variant<Action<ActionCode::Forward>, Action<ActionCode::Backward>,
                 Action<ActionCode::Left>, Action<ActionCode::Right>,
                 Action<ActionCode::Use>>;

} // namespace Domain

#endif // DOMAIN_ACTION_HPP
