#include <iostream>
#include <zh/graph.hpp>

int main() {
	auto g = zh::graph<std::string>::from_adjlist("examples/data/fb.adjlist");
	
	std::cout << g << '\n';
	std::cout << "nodes: " << g.nodes().size() << '\n';
	std::cout << "edges: " << g.edges().size() << '\n';
}