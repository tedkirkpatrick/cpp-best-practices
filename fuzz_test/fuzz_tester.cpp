#include <fmt/format.h>

#include "ops.hpp"

// Fuzzer that attempts to invoke undefined behavior for signed integer overflow
// cppcheck-suppress unusedFunction symbolName=LLVMFuzzerTestOneInput
extern "C" int LLVMFuzzerTestOneInput(int lhs, int rhs)
{
  fmt::print("Value sum: {}\n", ops::add(lhs, rhs));
  return 0;
}
