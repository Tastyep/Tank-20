#ifndef UTILITY_HPP_K3Q5SMAP
#define UTILITY_HPP_K3Q5SMAP

#include <type_traits>

template <class... Ts>
struct Overloaded : Ts... {
  using Ts::operator()...;
};

template <class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

template <typename Enum, typename U = std::underlying_type_t<Enum>>
U enum_cast(Enum e) {
  return static_cast<U>(e);
}

#endif // UTILITY_HPP_K3Q5SMAP
