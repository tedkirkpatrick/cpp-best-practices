#include <string_view>

#include <catch2/catch.hpp>
#include <fmt/format.h>

#include "parse_args.hpp"

TEST_CASE("get 15", "[parse_args]")
{
  REQUIRE(parse_args::getInt("15") == parse_args::Int_p{true, 15});
}

TEST_CASE("trailing non-digit", "[parse_args]")
{
  REQUIRE(parse_args::getInt("15h") == parse_args::Int_p{false, 0});
}

TEST_CASE("non-number", "[parse_args]")
{
  REQUIRE(parse_args::getInt("hello") == parse_args::Int_p{false, 0});
}

TEST_CASE("out of range", "[parse_args]")
{
  REQUIRE(parse_args::getInt("2147483648") == parse_args::Int_p{false, 0});
}

static auto build_args(const std::string &lhs, const std::string &rhs) {
  return parse_args::ArgMap {
    std::pair{"<int_a>", docopt::value(lhs)},
    std::pair{"<int_b>", docopt::value(rhs)}
  };
}

TEST_CASE("two good args", "[parse_args]")
{
  auto [b, l, r] = parse_args::getTwoInts(build_args("4", "5"));
  fmt::print("{}, {}, {}\n", b, l, r);
  REQUIRE(parse_args::getTwoInts(build_args("4", "5")) ==
	  parse_args::Two_int_p{true, 4, 5});
}


TEST_CASE("lhs bad", "[parse_args]")
{
  REQUIRE(parse_args::getTwoInts(build_args("hello", "5")) ==
	  parse_args::Two_int_p{false, 0, 0});
}

TEST_CASE("rhs bad", "[parse_args]")
{
  REQUIRE(parse_args::getTwoInts(build_args("4", "goodbye")) ==
	  parse_args::Two_int_p{false, 0, 0});
}
