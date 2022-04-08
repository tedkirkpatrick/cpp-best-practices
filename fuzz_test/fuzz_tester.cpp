#include <fmt/format.h>
#include <cstddef>
#include <iterator>
#include <span>

#include "ops.hpp"

// Fuzzer that attempts to invoke undefined behavior for signed integer overflow
// cppcheck-suppress unusedFunction symbolName=LLVMFuzzerTestOneInput
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, std::size_t Size)
{
  auto sz = 2 * (Size / (2 * sizeof(int)));
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  auto vals = std::span<const int> (reinterpret_cast<const int*>(Data), sz);
  for (auto it = vals.begin(); it < vals.end(); it += 2) {
    fmt::print("{}\n", ops::add(*it, *(it + 1)));
  }
  return 0;
}
