#ifndef APP_GAME_STATE
#define APP_GAME_STATE

#include "domain/Concept.hpp"

namespace App {

struct GameState {
  Domain::TimePoint lastTick{Domain::Clock::now()};
  Domain::TimePoint lastRender{Domain::Clock::now()};
};

} // namespace App

#endif /* end of include guard: APP_GAME_STATE */
