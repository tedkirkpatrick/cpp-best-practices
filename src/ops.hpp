#ifndef OPS_HPP
#define OPS_HPP

#include <concepts>

namespace ops {

[[nodiscard]] constexpr auto add(std::integral auto lhs, std::integral auto rhs) noexcept {
  return lhs + rhs;
}

[[nodiscard]] constexpr auto mult(std::integral auto lhs, std::integral auto rhs) noexcept {
  return lhs * rhs;
}

[[nodiscard]] int flaky_add(int lhs, int rhs) noexcept;

[[nodiscard]] bool check_overflow(unsigned short lhs, unsigned short rhs);

} // namespace ops

#endif
