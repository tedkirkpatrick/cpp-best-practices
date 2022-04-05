#include <functional>
#include <iostream>
#include <string>
#include <utility>

#include <docopt/docopt.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "ops.hpp"


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

[[nodiscard]] auto getInt(const std::string &sVal) {
  try {
    std::size_t count {};
    auto val = std::stoi(sVal, &count);
    if (count != sVal.size()) {
      // There were trailing non-digits
      return std::pair{false, 0};
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

using ArgMap = std::map<std::string, docopt::value>;

[[nodiscard]] auto getTwoInts(const ArgMap &args) {
  auto logger = spdlog::get("logger");
  const auto [a_valid, a] = getInt(args.at("<int_a>").asString());
  if (not a_valid) {
    fmt::print("'{}' is not an integer or out of range\n", args.at("<int_a>").asString());
    logger->error("'{}' is not an integer or out of range", args.at("<int_a>").asString());
  }
  const auto [b_valid, b] = getInt(args.at("<int_b>").asString());
  if (not b_valid) {
    fmt::print("'{}' is not an integer or out of range\n", args.at("<int_b>").asString());
    logger->error("'{}' is not an integer or out of range", args.at("<int_a>").asString());
  }
  if (not a_valid or not b_valid) {
    return std::tuple{false, 0, 0};
  }
  return std::tuple{true, a, b};
}

int main(int argc, const char **argv)
{
  try {
    auto logger = spdlog::basic_logger_st("logger", "logs/basic-log.txt");

    ArgMap args = docopt::docopt(USAGE,
      { std::next(argv), std::next(argv, argc) },
      true,// show help if requested
      fmt::format("{} {}",
        cpp_best_practices::cmake::project_name,
        cpp_best_practices::cmake::project_version));// version string, acquired from config.hpp via CMake

    if (args.at("add").asBool()) {
      auto [valid, a, b] = getTwoInts(args);
      if (valid) {
	fmt::print("{} + {} = {}\n",
		   a,
		   b,
		   ops::add(a, b));
      }
    }
    else if (args.at("mult").asBool()) {
      auto [valid, a, b] = getTwoInts(args);
      if (valid) {
	fmt::print("{} * {} = {}\n",
		   a,
		   b,
		   ops::mult(a, b));
      }
    }
  } catch (const std::exception &e) {
    fmt::print("Unhandled exception in main: {}\n", e.what());
  }
}
