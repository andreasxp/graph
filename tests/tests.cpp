#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <variant>

#include <doctest/doctest.h>
#include <range/v3/all.hpp>

#include <zh/graph.hpp>
//#include "zh/graph/io/id_format.hpp"

namespace std {

std::ostream& operator<<(std::ostream& os, const std::monostate&) {
	os << "{}";
	return os;
}

}

TEST_CASE("Unit.BasicUsage") {
	zh::graph<std::monostate, char> g;
	g.emplace(std::monostate());
	g.emplace(std::monostate());
	g.emplace(std::monostate());
	g.emplace(std::monostate());

	auto i1 = g.nodes().begin();
	auto i2 = ++g.nodes().begin();
	auto i3 = ++++g.nodes().begin();
	auto i4 = ++++++g.nodes().begin();

	//g.connect(i1, i2, 'a');
	//g.connect(i1, i3, 'b');
	//g.connect(i2, i3, 'c');
	//g.connect(i3, i4, 'd');

	//std::cout << g << "\n\n";
	//std::cout << zh::line_graph(g) << "\n\n";
}