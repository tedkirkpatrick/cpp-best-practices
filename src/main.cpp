#include <functional>
#include <iostream>
#include <string>
#include <utility>

#include <docopt/docopt.h>
#include <spdlog/spdlog.h>

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `cpp_best_practices`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <internal_use_only/config.hpp>

static constexpr auto USAGE =
  R"(Demonstrate C++ build and test.

    Usage:
          intro add <int_a> <int_b>
          intro mult <int_a> <int_b>
          intro (-h | --help)
          intro --version
 Options:
          -h --help     Show this screen.
          --version     Show version.
)";

[[nodiscard]] auto add(int left, int right) {
  return left + right;
}

[[nodiscard]] auto getInt(const docopt::value &arg) {
  try {
    auto sVal = arg.asString();
    std::size_t count {};
    auto val = std::stoi(sVal, &count);
    if (count != sVal.size()) {
      throw std::invalid_argument(fmt::format("'{}' is not an integer", sVal));
    }
    return std::pair{true, val};
  }
  catch(const std::invalid_argument &e) {
    return std::pair{false, 0};
  }
  catch (const std::out_of_range &e) {
    return std::pair{false, 0};
  }
}

[[nodiscard]] bool isEmpty(const docopt::value &v) noexcept {
  return v.kind() == docopt::Kind::Empty;
}

int main(int argc, const char **argv)
{
  try {
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
      { std::next(argv), std::next(argv, argc) },
      true,// show help if requested
      fmt::format("{} {}",
        cpp_best_practices::cmake::project_name,
        cpp_best_practices::cmake::project_version));// version string, acquired from config.hpp via CMake

    if (args["add"]) {
      auto [a_valid, a] = getInt(args["<int_a>"]);
      if (not a_valid) {
	fmt::print("'{}' is not an integer or out of range\n", args["<int_a>"].asString());
      }
      auto [b_valid, b] = getInt(args["<int_b>"]);
      if (not b_valid) {
	fmt::print("'{}' is not an integer or out of range\n", args["<int_b>"].asString());
      }
      if (a_valid and b_valid) {
	fmt::print("{} + {} = {}\n",
		   a,
		   b,
		   add(a, b));
      }
    }

    // Use the default logger (stdout, multi-threaded, colored)
    spdlog::info("Hello, {}!", "World");

  } catch (const std::exception &e) {
    fmt::print("Unhandled exception in main: {}\n", e.what());
  }
}
