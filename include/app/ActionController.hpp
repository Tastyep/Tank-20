#ifndef APP_ACTION_CONTROLLER_HPP
#define APP_ACTION_CONTROLLER_HPP

#include "domain/Action.hpp"
#include <iostream>

namespace App::Controller {

class ActionController {
public:
  template <Domain::ActionCode code>
  void handle(const Domain::Action<code> &) requires(
      Domain::Action<code>::isMovement()) {
    std::cout << "Movement action " << static_cast<int>(code) << '\n';
  }

  template <Domain::ActionCode code>
  void handle(const Domain::Action<code> &) {
    std::cout << "Non Movement action " << static_cast<int>(code) << '\n';
  }
};

} // namespace App::Controller

#endif // APP_ACTION_CONTROLLER_HPP
