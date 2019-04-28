#pragma once
#include <tuple>
#include "node.hpp"
#include "edge_iterator.hpp"
#include "deps/zh/prism.hpp"

namespace zh {

template <class T, class E>
class node<T, E>::edges_view
	: public zh::fprism<
	node<T, E>::container,
	node<T, E>::edge_iterator,
	node<T, E>::const_edge_iterator,
	std::tuple<node<T, E>&>> {
private:
	using base = zh::fprism<
		node<T, E>::container,
		node<T, E>::edge_iterator,
		node<T, E>::const_edge_iterator,
		std::tuple<node<T, E>&>>;

	friend class node<T, E>::const_nodes_view;
public:
	edges_view(typename node<T, E>::container& data, node<T, E>& value) :
		base(data, std::tie(value)) {
	}
};

template <class T, class E>
class node<T, E>::const_edges_view
	: public zh::cfprism<
	node<T, E>::container,
	node<T, E>::const_edge_iterator,
	std::tuple<const node<T, E>&>> {
private:
	using base = zh::cfprism<
		node<T, E>::container,
		node<T, E>::const_edge_iterator,
		std::tuple<const node<T, E>&>>;

public:
	const_edges_view(typename node<T, E>::container& data, node<T, E>& value) :
		base(data, std::tuple(value)) {
	}
	
	const_edges_view(const node<T, E>::edges_view& other) :
		base(other.m_data) {
	}
};

} // namespace zh