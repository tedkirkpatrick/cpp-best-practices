#include <array>

#include "sandemo.hpp"

/*
    The code in this file deliberately invokes undefined behaviour
    to demonstrate the runtime sanitizers in action. To pass
    the compilation step, we must turn off checks from all
    three static checkers: clang-tidy, cppcheck, and the compiler
    itself.

    For the first two, we suppress checks using inline pseudocomments.
    For the compiler, we add '-Wnoerror=' options in the 'CMakeLists.txt'
    file in this directory.

    cppcheck-suppress suppresses cppcheck warnings. cppcheck checks are
    reported and denoted by camelCase names.

    NOLINT suppresses clang-tidy warnings. clang-tidy checks are reported
    and denoted by hyphenated-names.
*/


namespace sandemo {

static constexpr auto length = 400;

// Deliberately allocate memory and never free
void leak_memory () {
  // cppcheck-suppress unreadVariable
  // cppcheck-suppress unusedAllocatedMemory
  [[maybe_unused]] auto *leak = new char[length]; // NOLINT(cppcoreguidelines-owning-memory)
  // cppcheck-suppress memleak
} // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)

// Deliberately access outside bounds
void bound() {
  std::array<char, length> a {};
  // cppcheck-suppress unreadVariable
  // cppcheck-suppress containerOutOfBoundsIndexExpression
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
  a[a.size()] = 'h'; 
}

} // namespace sandemo
