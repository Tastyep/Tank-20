#include "domain/Timer.hpp"
#include <chrono>

namespace Domain {

std::chrono::nanoseconds Timer::elapsed() const {
  return Clock::now() - _startTime;
}

std::chrono::nanoseconds Timer::restart() {
  const auto elapsed = this->elapsed();
  _startTime += elapsed;
  return elapsed;
}

} // namespace Domain
