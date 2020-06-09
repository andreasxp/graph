#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <zh/graph.hpp>
#include <iostream>

TEST_CASE("Unit.DefaultCtor") {
	zh::graph<int, char> g;
}

TEST_CASE("Unit.FromAdjlist") {
	auto g = zh::graph<int>::from_adjlist("tests/data/test.adjlist");

	//std::cout << g;

	CHECK(g.size() == 4);
	CHECK(std::set(g.begin(), g.end()) == std::set({1, 2, 3, 4}));
	CHECK(g.edges().size() == 4);
}