#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <zh/graph.hpp>

TEST_CASE("Unit.DefaultCtor") {
	zh::graph<int, char> g;
}