#include <cmath>
#include <limits>

#include "ops.hpp"

namespace ops {

// Proportion of range to return wrong value
constexpr static auto proportion = 0.25;

constexpr static auto range = static_cast<int>(
  proportion * std::numeric_limits<int>::max());
constexpr static auto low = range / 2;
constexpr static auto high = low + range;


// Add two ints, sometimes even correctly
int flaky_add(int lhs, int rhs) noexcept {
  if (low <= lhs and lhs <= high) {
    return -(lhs + rhs);
  }
  return lhs + rhs; 
}

} // namespace ops
