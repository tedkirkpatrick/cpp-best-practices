#include <array>
#include <limits>

#include <spdlog/spdlog.h>

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
    denoted by camelCase names.

    NOLINT suppresses clang-tidy warnings. clang-tidy checks are denoted
    by hyphenated-lowercase names.
*/


namespace sandemo {

static constexpr auto length = 400;

// Deliberately allocate memory and never free
void leak_memory () {
  auto logger = spdlog::get("logger");
  if (logger) {logger->error("An allocated object will not be freed upon this program's end");}
  // cppcheck-suppress unreadVariable
  // cppcheck-suppress unusedAllocatedMemory
  [[maybe_unused]] auto *leak = new char[length]; // NOLINT(cppcoreguidelines-owning-memory)
  // cppcheck-suppress memleak
} // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)

// Deliberately access outside bounds
void bound() {
  auto logger = spdlog::get("logger");
  std::array<char, length> a {};
  if (logger) {logger->critical("A reference is about to be made outside an array boundary");}
  // cppcheck-suppress unreadVariable
  // cppcheck-suppress containerOutOfBoundsIndexExpression
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
  a[a.size()] = 'h'; 
}

// Deliberately perform a signed overflow whenever passed i >= 1
int signed_overflow(int i) {
  return std::numeric_limits<int>::max() + i; // NOLINT clang-diagnostic-integer-overflow
}

} // namespace sandemo
