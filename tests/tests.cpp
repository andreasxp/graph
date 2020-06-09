#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <zh/graph.hpp>
#include <iostream>

TEST_CASE("Unit.DefaultCtor") {
	zh::graph<int, char> g;
}

TEST_CASE("Unit.FromAdjlist") {
	auto g = zh::graph<int>::from_adjlist("tests/data/test.adjlist");

	CHECK(g.size() == 4);
	CHECK(g.edges().size() == 4);
	CHECK(std::set(g.begin(), g.end()) == std::set({1, 2, 3, 4}));
}

TEST_CASE("Unit.CompleteGraphCtorValue") {
	auto g1 = zh::graph<int>::k(5);

	CHECK(g1.size() == 5);
	CHECK(g1.edges().size() == 10);
	CHECK(std::set(g1.begin(), g1.end()) == std::set({0, 0, 0, 0, 0}));

	auto g2 = zh::graph<int>::k(10, 17);
	CHECK(g2.size() == 10);
	CHECK(g2.edges().size() == 45);
	CHECK(std::set(g2.begin(), g2.end()) == std::set({17, 17, 17, 17, 17, 17, 17, 17, 17, 17}));
}

TEST_CASE("Unit.CompleteGraphCtorGenerator") {
	auto g = zh::graph<int>::k_gen(5, []() {
		static int value = 0;
		return value++;
	});

	CHECK(g.size() == 5);
	CHECK(g.edges().size() == 10);
	CHECK(std::set(g.begin(), g.end()) == std::set({0, 1, 2, 3, 4}));
}