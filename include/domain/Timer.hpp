#ifndef DOMAIN_TIMER_HPP
#define DOMAIN_TIMER_HPP

#include "domain/Concept.hpp"
#include <chrono>

namespace Domain {

class Timer {
public:
  std::chrono::nanoseconds elapsed() const;
  std::chrono::nanoseconds restart();

private:
  TimePoint _startTime{Clock::now()};
};

} // namespace Domain

#endif // DOMAIN_TIMER_HPP
