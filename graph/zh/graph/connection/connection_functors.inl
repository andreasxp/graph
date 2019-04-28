#pragma once
#include "connection_functors.hpp"
#include "connection.hpp"

namespace zh {

template <class T, class E, class NodeHash>
struct connection_node_hash : private NodeHash {
	std::size_t operator()(const connection<T, E>& con) const noexcept(
		noexcept(std::declval<NodeHash>()(*con.ptr))) {
		return NodeHash::operator()(*con.ptr);
	}
};

template <class T, class E, class NodeEqual>
struct connection_node_equal : private NodeEqual {
	bool operator()(const connection<T, E>& lhs, const connection<T, E>& rhs) const noexcept(
		noexcept(std::declval<NodeEqual>()(*lhs.ptr, *rhs.ptr))) {
		return NodeEqual::operator()(*lhs.ptr, *rhs.ptr);
	}
};

} // namespace zh