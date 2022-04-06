#include <catch2/catch.hpp>

#include "../src/ops.hpp"

TEST_CASE("Addition", "[ops]")
{
  REQUIRE(ops::add(1,2) == 3);
  REQUIRE(ops::add(3, -4) == -1);
}
