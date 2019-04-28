#pragma once
#include <variant>
#include <cstdint>
#include <type_traits>
#include "deps/ska/flat_hash_map.hpp"
#include "../connection/connection.hpp"
#include "../connection/connection_functors.hpp"
#include "node_fwd.hpp"
#include "../graph_fwd.hpp"
#include "functors.hpp"

#include <unordered_set>

namespace zh {

template <class T, class E>
class node {
public:
	// A node has a set of connections.
	// Connections are responsible for holding and deleting edge values, and
	// only a single connection is allowed to another node.
	using container = std::unordered_set< //ska::flat_hash_set<
		connection<T, E>,
		connection_node_hash<T, E>,
		connection_node_equal<T, E, node_id_equal>>;

	container m_connections;
	T m_value;

public:
	// Member types ===========================================================
	// Every node has an unique ID of this type.
	// Nodes are not copyable nor movable, and
	// never change the ID.
	using value_type = T;
	using id_type = std::uintptr_t;

	class node_iterator;
	class const_node_iterator;

	class nodes_view;
	class const_nodes_view;

	class edge_iterator;
	class const_edge_iterator;

	class edges_view;
	class const_edges_view;

	// Friends ================================================================
	template <class T_, class E_>
	friend class graph;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	template <class... Args>
	node(Args&&... value_args); // Construct internal value from these args

	node()                       = delete;
	node(const node&)            = delete;
	node(node&&)                 = delete;

	node& operator=(const node&) = delete;
	node& operator=(node&&)      = delete;

	// Disconnecting edges is not the node's responsibility.
	// Graph does that when erasing the node.
	~node() = default;

	// Iterators ---------------------------------------------------------------
	nodes_view adjacent_nodes() noexcept;
	const_nodes_view adjacent_nodes() const noexcept;

	edges_view edges() noexcept;
	const_edges_view edges() const noexcept;

	// Observers ---------------------------------------------------------------
	id_type id() const noexcept;

	// Member access -----------------------------------------------------------
	T& value() noexcept;
	const T& value() const noexcept;

private:
	// Connecting --------------------------------------------------------------
	template <class... Args>
	void connect(node& n, Args&&... edge_args);
	void disconnect(node& n);
};

} // namespace zh

namespace std {

template<class T, class E>
struct hash<zh::node<T, E>>;

}

#include "node_void_E.hpp"

#include "node_iterator.hpp"
#include "edge_iterator.hpp"

#include "nodes_view.hpp"
#include "edges_view.hpp"

#include "node.inl"