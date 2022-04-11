#ifndef PARSE_ARGS_DEF
#define PARSE_ARGS_DEF

#include <map>
#include <string>
#include <utility>

#include <docopt/docopt.h>

namespace parse_args {

using ArgMap = std::map<std::string, docopt::value>;
using Int_p = std::pair<bool, int>;
using Two_int_p = std::tuple<bool, int, int>;

[[nodiscard]] Int_p getInt(const std::string &sVal);

[[nodiscard]] Two_int_p getTwoInts(const ArgMap &args);

} // namespace parse_args

#endif
