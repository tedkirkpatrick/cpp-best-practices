
#include <exception>
#include <fmt/format.h>
#include <cstddef>
#include <span>

#include "ops.hpp"

// Fuzzer that attempts to invoke undefined behavior for signed integer overflow
// cppcheck-suppress unusedFunction symbolName=LLVMFuzzerTestOneInput
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, std::size_t Size)
{
  auto sz = 2 * (Size / (2 * sizeof(int)));
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  auto vals = std::span<const int> (reinterpret_cast<const int*>(Data), sz);
  if (not vals.empty()) {
    // cppcheck-suppress unreadVariable
    [[maybe_unused]] auto v = 1 / vals[0];
    /*
    // cppcheck-suppress unreadVariable
    [[maybe_unused]] auto v = ops::add(*vals.begin(), *(std::next(vals.begin())));
    */
  }
  /*
  for (auto it = vals.begin(); it < vals.end(); it += 2) {
    fmt::print("{}\n", ops::add(*it, *(it + 1)));
    //[[maybe_unused]] auto v = ops::add(*it, *(it + 1));
    // cppcheck-suppress unreadVariable
    [[maybe_unused]] auto v = ops::add(2147483647, 1); // NOLINT [cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers]
    [[maybe_unused]] auto s = Data[Size]; // NOLINT [cppcoreguidelines-pro-bounds-pointer-arithmetic]
  }
  */
  return 0;
}
