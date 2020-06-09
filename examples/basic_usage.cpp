#include <iostream>
#include <zh/graph.hpp>

int main() {
	zh::graph<int, char> g;
	g.reserve(4);
	
	auto i1 = g.emplace(1);
	auto i2 = g.emplace(2);
	auto i3 = g.emplace(3);
	auto i4 = g.emplace(4);

	g.connect(i1, i2, 'a');
	g.connect(i1, i3, 'b');
	g.connect(i2, i3, 'c');
	g.connect(i3, i4, 'd');

	std::cout << g << "\n\n";
	//std::cout << zh::line_graph(g) << "\n\n";
}