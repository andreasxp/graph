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

	g.connect(i1, i2, 0.5);

	using namespace ranges;

	auto edges =
		view::for_each(g.m_nodes, [] (auto& node_ptr) {
			auto& nd = *node_ptr;

			return view::for_each(nd.m_connections, [&nd] (auto& cnc) {
				auto& nd2 = *cnc.ptr;

				return yield_if(nd.id() < nd2.id(), std::tie(nd, nd2));
			});
		});

	auto edges2 =
		view::for_each(g.nodes(), [] (auto& nd1) {
			return view::for_each(nd.m_connections, [&nd1] (auto & cnc) {
				auto& nd2 = *cnc.ptr;

				return yield_if(nd.id() < nd2.id(), std::tie(nd, nd2));
			});
		});

	for (auto e : edges) {
		std::cout << std::get<0>(e).value() << ", " << std::get<1>(e).value() << std::endl;
	}

	/*for (auto&& i : g) {
		std::cout << i;
	}*/

	for (auto&& n : g.nodes()) {
		std::cout << n.value();
	}
}