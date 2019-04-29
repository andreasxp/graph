#pragma once
#include "deps/zh/prism.hpp"
#include "graph.hpp"
#include "node_iterator.hpp"

namespace zh {

template <class T, class E>
class graph<T, E>::nodes_view
	: public zh::fprism<
		graph<T, E>::container,
		graph<T, E>::node_iterator,
		graph<T, E>::const_node_iterator> {
private:
	using base = zh::fprism<
		graph<T, E>::container,
		graph<T, E>::node_iterator,
		graph<T, E>::const_node_iterator>;

public:
	using base::base;
};

template <class T, class E>
class graph<T, E>::const_nodes_view
	: public zh::cfprism<
		const graph<T, E>::container,
		graph<T, E>::const_node_iterator> {
private:
	using base = zh::cfprism<
		const graph<T, E>::container,
		graph<T, E>::const_node_iterator>;

public:
	using base::base;
	const_nodes_view(const nodes_view& other) :
		base(other.m_data) {
	}
};

} // namespace zh