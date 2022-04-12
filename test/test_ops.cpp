#include <catch2/catch.hpp>

#include "ops.hpp"

TEST_CASE("add", "[ops]")
{
  REQUIRE(ops::add(1, 2) == 3);
  REQUIRE(ops::add(3, -4) == -1);
}

TEST_CASE("mult", "[ops]")
{
  REQUIRE(ops::mult(4, 5) == 20);
  REQUIRE(ops::mult(-3, 4) == -12);
}

TEST_CASE("flaky_add", "[ops]")
{
  REQUIRE(ops::flaky_add(4, 5) == 9);
  REQUIRE(ops::flaky_add(1073741823, 1) == -1073741824);
}
