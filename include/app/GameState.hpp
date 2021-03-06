#ifndef APP_GAME_STATE
#define APP_GAME_STATE

#include <chrono>

namespace App {

struct GameState {
  using Clock = std::chrono::steady_clock;
  using TimePoint = std::chrono::time_point<Clock>;

  TimePoint lastTick{Clock::now()};
  TimePoint lastRender{Clock::now()};
};

} // namespace App

#endif /* end of include guard: APP_GAME_STATE */
