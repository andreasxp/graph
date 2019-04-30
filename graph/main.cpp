#include <iostream>
#include <range/v3/all.hpp>
#include "zh/graph/graph.hpp"

int main() {
	zh::graph<void, int> g;
	g.emplace();
	g.emplace();
	g.emplace();
	g.emplace();

	auto i1 = g.nodes().begin();
	auto i2 = ++g.nodes().begin();
	auto i3 = ++++g.nodes().begin();

	g.connect(i1, i2, 1);
	g.connect(i2, i3, 2);
	g.connect(i1, i3, 3);

	std::cout << g << std::endl;
	std::cout << g.edges().size();
}