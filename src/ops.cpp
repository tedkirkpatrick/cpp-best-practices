#include <cmath>
#include <limits>

#include "ops.hpp"

namespace ops {

// Proportion of range to return wrong value
constexpr static auto proportion = 0.25;

constexpr static auto range =
  static_cast<int>(proportion * std::numeric_limits<int>::max());
constexpr static auto low = std::numeric_limits<int>::max()/2 - range/2;
constexpr static auto high = low + range;


// Add two ints, sometimes even correctly
int flaky_add(int lhs, int rhs) noexcept {
  if (low <= lhs and lhs <= high) {
    return -(lhs + rhs);
  }
  return lhs + rhs; 
}

// Demonstrate incorrect check for overflow.
// This will be detected by the CodeQL query 'Arithmetic/BadAdditionOverflowCheck',
// defined in
// https://github.com/github/codeql/blob/main/cpp/ql/src/Likely%20Bugs/Arithmetic/BadAdditionOverflowCheck.ql
// This check is performed as part of the GitHub CodeQL action 'github/codeql-action/analyze@v1'
// called in '.github/workflows/codeql-analysis.yml'.

// The following routine is from the example at
// https://github.com/github/codeql/blob/main/cpp/ql/src/Likely%20Bugs/Arithmetic/BadAdditionOverflowCheckExample1.cpp
bool check_overflow(unsigned short x, unsigned short y) {
  // BAD: comparison is always false due to type promotion
  return (x + y < x);
}


} // namespace ops
