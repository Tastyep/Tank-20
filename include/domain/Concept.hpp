#ifndef DOMAIN_CONCEPT_HPP
#define DOMAIN_CONCEPT_HPP

#include <chrono>

namespace Domain {

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;

} // namespace Domain

#endif // DOMAIN_CONCEPT_HPP
