#include "ops.hpp"

namespace ops {

[[nodiscard]] int add(int lhs, int rhs) noexcept {
  return lhs + rhs;
}

[[nodiscard]] int mult(int lhs, int rhs) noexcept {
  return lhs * rhs;
}

} // namespace ops
