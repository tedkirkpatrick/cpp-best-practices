#include <fmt/format.h>
#include <cstddef>

#include "ops.hpp"

// Fuzzer that attempts to invoke undefined behavior for signed integer overflow
// cppcheck-suppress unusedFunction symbolName=LLVMFuzzerTestOneInput
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, std::size_t Size)
{
  for (std::size_t next = 0; next < Size - Size % sizeof(int); next += 2 * sizeof(int)) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast,cppcoreguidelines-pro-bounds-pointer-arithmetic)
    auto lhs = * reinterpret_cast<const int*>(Data + next);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast,cppcoreguidelines-pro-bounds-pointer-arithmetic)
    auto rhs = * reinterpret_cast<const int*>(Data + next + sizeof(int));
    (void) ops::add(lhs, rhs);
  }
  return 0;
}
