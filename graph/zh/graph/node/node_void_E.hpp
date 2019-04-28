#pragma once
#include "node.hpp"

namespace zh {

template <class E>
class node<void, E> {
	// Node specialization that holds no internal value
private:
	// A node has a set of connections.
	// Connections are responsible for holding and deleting edge values, and
	// only a single connection is allowed to another node.
	using container = ska::flat_hash_set<
		connection<void, E>,
		connection_node_hash<void, E>,
		connection_node_equal<void, E, node_id_equal>>;

public:
	// Member types ===========================================================
	// Every node has an unique ID of this type.
	// Nodes are not copyable nor movable, and
	// never change the ID.
	using value_type = void;
	using id_type = std::uintptr_t;

	class node_iterator;
	class const_node_iterator;

	class nodes_view;
	class const_nodes_view;

	class edge_iterator;
	class const_edge_iterator;

	class edges_view;
	class const_edges_view;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	node() = default;
	node(const node&) = delete;
	node(node&&) = delete;

	node& operator=(const node&) = delete;
	node& operator=(node&&) = delete;

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

private:
	// Connecting --------------------------------------------------------------
	template <class... Args>
	void connect(node& n, Args&&... edge_args);
	void disconnect(node& n);
};

} // namespace zh