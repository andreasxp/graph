#pragma once
#include <cstdint>
#include <memory>
#include <iostream>

#include "deps/ska/unordered_map.hpp"
#include "deps/nlohmann/json.hpp"
using json = nlohmann::json;

#include "graph_fwd.hpp"
#include "node/node.hpp"
#include "node/functors.hpp"

namespace zh {

template <class E>
class graph<void, E> {
private:
	using container = std::vector<std::unique_ptr<node<void, E>>>;
	container m_nodes;

public:
	// Member types ============================================================
	using value_type = void;
	using node_type  = node<void, E>;

	using size_type       = typename container::size_type;
	using difference_type = typename container::difference_type;

	using reference       = void;
	using const_reference = void;

	using pointer         = void;
	using const_pointer   = void;

	// The following iterators and views are implemented as nested classes for
	// these reasons:
	// 1. More straightforward casting between iterators
	// 2. Can't forward-declare using directives
	// 3. Clearer error messages without using directives

	// Iterate over nodes
	class node_iterator;
	class const_node_iterator;

	// Iterate over edges
	class edge_iterator;
	class const_edge_iterator;

	// nodes_view is a prism - a lightweight struct that provides a
	// way to access elements inside via begin and end. Since there are several
	// ways to iterate over a graph (values, nodes, edges), graph provides
	// nodes_view, edges_view, as well as plain begin/end for values.
	class nodes_view;
	class const_nodes_view;

	class edges_view;
	class const_edges_view;

	// Member functions ========================================================
	// Constructors ------------------------------------------------------------
	constexpr graph() = default;
	graph(const graph& other);
	graph(graph&& other) noexcept;
	~graph() = default;

	graph& operator=(graph rhs);

	template <class T_, class E_>
	friend inline void swap(graph<T_, E_>& first, graph<T_, E_>& second) noexcept;

	// Iterators ---------------------------------------------------------------
	// No iterators in graph<void>

	// Node iterators ----------------------------------------------------------
	nodes_view       nodes() noexcept;
	const_nodes_view nodes() const noexcept;

	// Edge iterators ----------------------------------------------------------
	edges_view       edges() noexcept;
	const_edges_view edges() const noexcept;

	// Connecting --------------------------------------------------------------
	template <class... Args, class = std::enable_if_t<
		std::is_constructible_v<E, Args&&...> ||
		(std::is_same_v<E, void> && sizeof...(Args) == 0)>>
	void connect(node<void, E>& n1, node<void, E>& n2, Args&&... args);
	template <class... Args, class = std::enable_if_t<
		std::is_constructible_v<E, Args&&...> ||
		(std::is_same_v<E, void> && sizeof...(Args) == 0)>>
	void connect(node_iterator it1, node_iterator it2, Args&&... args);

	void disconnect(node<void, E>& n1, node<void, E>& n2);
	void disconnect(node_iterator it1, node_iterator it2);

	// Element access ----------------------------------------------------------
	// No element access in graph<void>

	// Modifiers ---------------------------------------------------------------
	node_iterator insert();
	node_iterator emplace();

	// Erase nodes
	node_iterator erase(node_iterator it);

	// Erase edges
	edge_iterator erase(edge_iterator it);
	void erase(edge<void, E> e);

	void clear() noexcept;

	void reserve(size_type new_size);

	// Observers --------------------------------------------------------------
	bool empty() const noexcept;
	std::size_t size() const noexcept;

	std::size_t count_edges() const noexcept;
	double ratio() const noexcept;
};

} // namespace zh

#include "node_iterator_void_E.hpp"
#include "edge_iterator.hpp"

#include "nodes_view.hpp"
#include "edges_view.hpp"