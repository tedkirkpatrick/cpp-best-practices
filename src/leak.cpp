#include "leak.hpp"

namespace leak {

static constexpr auto length = 400;

// Deliberately allocate memory and never free
void leak_memory () {
  /*
    NOLINT suppresses clang-tidy warnings
    cppcheck-suppress suppresses cppcheck warnings
  */
  // cppcheck-suppress unreadVariable
  // cppcheck-suppress unusedAllocatedMemory
  [[maybe_unused]] auto *leak = new char[length]; // NOLINT(cppcoreguidelines-owning-memory)
  leak[length+5] = 'h'; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  // cppcheck-suppress memleak
  leak = nullptr; // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)
  // cppcheck-suppress memleak
} // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)

} // namespace leak
