#include <catch2/catch.hpp>

#include "ops.hpp"

TEST_CASE("Operations are computed with constexpr", "[ops]")
{
  STATIC_REQUIRE(ops::add(4, 5) == 9);
  STATIC_REQUIRE(ops::mult(4, 5) == 20);
}

/*
// Uncomment this test to demonstrate constexpr evaluation
// locating undefined behaviour (signed int overflow).
TEST_CASE("Constexpr test locating undefined behaviour", "[ops]")
{
  STATIC_REQUIRE(ops::mult(46341, 46341) == -2147479015);
}
*/
