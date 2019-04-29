#include <iostream>
#include <range/v3/all.hpp>
#include "zh/graph/graph.hpp"

int main() {
	zh::graph<int, double> g;
	g.emplace(1);
	g.emplace(2);
	g.emplace(3);
	g.emplace(4);

	auto i1 = g.begin();
	auto i2 = ++g.begin();
	auto i3 = ++++g.begin();

	g.connect(i1, i2, 0.5);
	g.connect(i2, i3, 1.5);
	g.connect(i1, i3, 3.5);

	for (auto&& i : g.edges()) {
		std::cout << i << std::endl;
	}

	for (auto&& n : g.nodes()) {
		std::cout << n.value() << " ";
	}
}