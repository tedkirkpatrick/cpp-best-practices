#include <spdlog/spdlog.h>

#include "parse_args.hpp"

namespace parse_args {

[[nodiscard]] Int_p getInt(const std::string &sVal) {
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

[[nodiscard]] Two_int_p getTwoInts(const ArgMap &args) {
  auto logger = spdlog::get("logger");
  const auto [a_valid, a] = getInt(args.at("<int_a>").asString());
  if (not a_valid) {
    if (logger) {logger->error("'{}' is not an integer or out of range", args.at("<int_a>").asString());}
  }
  const auto [b_valid, b] = getInt(args.at("<int_b>").asString());
  if (not b_valid) {
    if (logger) {logger->error("'{}' is not an integer or out of range", args.at("<int_a>").asString());}
  }
  if (not a_valid or not b_valid) {
    return std::tuple{false, 0, 0};
  }
  return std::tuple{true, a, b};
}

} // namespace parse_args
