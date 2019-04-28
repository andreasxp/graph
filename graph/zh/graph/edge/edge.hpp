#pragma once
#include "../node/node_fwd.hpp"
#include "edge_fwd.hpp"

namespace zh {

// Although called edge, this is more like an edge-reference.
// Due to implementation details, graph does not hold actual edges as objects,
// only nodes and connections. This is an interface for the user to interact
// with the graph in the edges paradigm.
//
// An edge does not care if the graph is oriented or not. If the graph is
// oriented, it constructs edges in such a way that first() always returns
// the source node, and second() - the target node.
template <class T, class E>
class edge {
private:
	node<T, E>* m_first_ptr;
	node<T, E>* m_second_ptr;
	E*          m_value_ptr;

public:
	edge(node<T, E>* first_ptr, node<T, E>* second_ptr, E* value_ptr);

	// Member types ===========================================================
	using value_type = E;
	using node_type = node<T, E>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	// Edges are not publicly constructible, only copyable and movable
	edge()                       = delete;
	edge(const edge&)            = default;
	edge(edge&&)                 = default;

	edge& operator=(const edge&) = default;
	edge& operator=(edge&&)      = default;

	// Data access ------------------------------------------------------------
	// Access first node
	node<T, E>& first() noexcept;
	const node<T, E>& first() const noexcept;

	// Access second node
	node<T, E>& second() noexcept;
	const node<T, E>& second() const noexcept;

	// Access edge value
	E& value() noexcept;
	const E& value() const noexcept;
};

template <class T>
class edge<T, void> {
private:
	node<T, void>* m_first_ptr;
	node<T, void>* m_second_ptr;

	edge(node<T, void>* first_ptr, node<T, void>* second_ptr);
public:
	// Member types ===========================================================
	using value_type = void;
	using node_type = node<T, void>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	// Edges are not publicly constructible, only copyable and movable
	edge()                       = delete;
	edge(const edge&)            = default;
	edge(edge&&)                 = default;

	edge& operator=(const edge&) = default;
	edge& operator=(edge&&)      = default;

	// Data access ------------------------------------------------------------
	// Access first node
	node<T, void>& first() noexcept;
	const node<T, void>& first() const noexcept;

	// Access second node
	node<T, void>& second() noexcept;
	const node<T, void>& second() const noexcept;
};

template <class T, class E>
class const_edge {
private:
	const node<T, E>* m_first_ptr;
	const node<T, E>* m_second_ptr;
	const E*          m_value_ptr;

	const_edge(const node<T, E>* first, const node<T, E>* second, const E* value);
public:
	// Member types ===========================================================
	using value_type = E;
	using node_type = node<T, E>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	// Edges are not publicly constructible, only copyable and movable
	const_edge(const edge<T, E>& other) noexcept;

	const_edge() = delete;
	const_edge(const const_edge&) = default;
	const_edge(const_edge&&) = default;

	const_edge& operator=(const const_edge&) = default;
	const_edge& operator=(const_edge&&) = default;

	// Data access ------------------------------------------------------------
	// Access first node
	const node<T, E>& first() const noexcept;

	// Access second node
	const node<T, E>& second() const noexcept;

	// Access edge value
	const E& value() const noexcept;
};

template <class T>
class const_edge<T, void> {
private:
	const node<T, void>* m_first_ptr;
	const node<T, void>* m_second_ptr;

	const_edge(const node<T, void>* first, const node<T, void>* second);
public:
	// Member types ===========================================================
	using value_type = void;
	using node_type = node<T, void>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	// Edges are not publicly constructible, only copyable and movable
	const_edge(const edge<T, void>& other) noexcept;

	const_edge() = delete;
	const_edge(const const_edge&) = default;
	const_edge(const_edge&&) = default;

	const_edge& operator=(const const_edge&) = default;
	const_edge& operator=(const_edge&&) = default;

	// Data access ------------------------------------------------------------
	// Access first node
	const node<T, void>& first() const noexcept;

	// Access second node
	const node<T, void>& second() const noexcept;
};

} // namespace zh

#include "edge.inl"