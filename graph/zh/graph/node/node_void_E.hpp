#pragma once
#include <cstdint>
#include "node_fwd.hpp"
#include "detail.hpp"
#include "../graph_fwd.hpp"
#include "functors.hpp"

#include "nodes_view.hpp"
#include "edges_view.hpp"

namespace zh {

template <class E>
class node<void, E> {
	// Specialization of node that holds no internal value
private:
	// A node has a set of connections.
	// Connections are responsible for holding and deleting edge values, and
	// only a single connection is allowed to another node.
	using container = detail::node_container<void, E>;

	container m_connections;

public:
	// Member types ===========================================================
	// Every node has an unique ID of this type.
	// Nodes are not copyable nor movable, and
	// never change the ID.
	using value_type = void;
	using edge_value_type = E;
	using id_type = std::uintptr_t;

	using nodes_view       = node_nodes_view<void, E>;
	using const_nodes_view = node_const_nodes_view<void, E>;

	using edges_view       = node_edges_view<void, E>;
	using const_edges_view = node_const_edges_view<void, E>;

	using node_iterator       = typename       nodes_view::iterator;
	using const_node_iterator = typename const_nodes_view::iterator;

	using edge_iterator       = typename       edges_view::iterator;
	using const_edge_iterator = typename const_edges_view::iterator;

	// Friends ================================================================
	template <class T_, class E_>
	friend class graph;
	
	template <class T_, class E_>
	friend auto detail::make_edges_view(detail::graph_container<T_, E_>& c);
	
	template <class T_, class E_>
	friend auto detail::make_edges_view(const detail::graph_container<T_, E_>& c);

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	explicit node()              = default;
	node(const node&)            = delete;
	node(node&&)                 = delete;

	node& operator=(const node&) = delete;
	node& operator=(node&&)      = delete;

	// Disconnecting edges is not the node's responsibility.
	// Graph does that when erasing the node.
	~node() = default;

	// Iterators ---------------------------------------------------------------
	nodes_view       adjacent_nodes() noexcept;
	const_nodes_view adjacent_nodes() const noexcept;

	edges_view       edges() noexcept;
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

#include "node_void_E.inl"