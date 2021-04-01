#ifndef DOMAIN_COMPONENT_PHYSIC_HPP
#define DOMAIN_COMPONENT_PHYSIC_HPP

#include <PlayRho/Dynamics/BodyID.hpp>
#include <PlayRho/Dynamics/FixtureID.hpp>

namespace Domain::Component {

struct Body {
  playrho::BodyID    id;
  playrho::FixtureID fixtureId;
};

} // namespace Domain::Component

#endif // DOMAIN_COMPONENT_PHYSIC_HPP
