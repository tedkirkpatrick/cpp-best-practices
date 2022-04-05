#include <functional>
#include <iostream>
#include <string>

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
    return docopt::value(val);
  }
  catch(const std::invalid_argument &e) {
    return docopt::value();
  }
  catch (const std::out_of_range &e) {
    return docopt::value();
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
      auto a = getInt(args["<int_a>"]);
      int av {};
      if (isEmpty(a)) {
	fmt::print("'{}' is not an integer or out of range\n", args["<int_a>"].asString());
      }
      else {
        av = static_cast<int>(a.asLong());
      }
      auto b = getInt(args["<int_b>"]);
      int bv {};
      if (isEmpty(b)) {
	fmt::print("'{}' is not an integer or out of range\n", args["<int_b>"].asString());
      }
      else {
        bv = static_cast<int>(b.asLong());
      }
      if (not isEmpty(a) and not isEmpty(b)) {
	fmt::print("{} + {} = {}\n",
		   av,
		   bv,
		   add(av, bv));
      }
    }

    // Use the default logger (stdout, multi-threaded, colored)
    spdlog::info("Hello, {}!", "World");

  } catch (const std::exception &e) {
    fmt::print("Unhandled exception in main: {}\n", e.what());
  }
}
