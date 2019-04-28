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

template <class T, class E>
class graph {
public:
	using container = std::vector<std::unique_ptr<node<T, E>>>;
	container m_nodes;

public:
	// Member types ============================================================
	using value_type      = T;
	using edge_value_type = E;
	using edge_type       = edge<T, E>;
	using node_type       = node<T, E>;

	using size_type       = typename container::size_type;
	using difference_type = typename container::difference_type;

	using reference       = T&;
	using const_reference = const T&;

	using pointer         = T*;
	using const_pointer   = const T*;

	// The following iterators and views are implemented as nested classes for
	// these reasons:
	// 1. More straightforward casting between iterators
	// 2. Can't forward-declare using directives
	// 3. Clearer error messages without using directives

	// Iterate over values
	class iterator;
	class const_iterator;

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
	iterator       begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;

	iterator       end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;

	// Node iterators ----------------------------------------------------------
	nodes_view       nodes() noexcept;
	const_nodes_view nodes() const noexcept;

	// Edge iterators ----------------------------------------------------------
	edges_view       edges() noexcept;
	const_edges_view edges() const noexcept;

	// Connecting --------------------------------------------------------------
	// These are all static because it doesn't actually matter, graph just
	// relays the connect request to nodes themselves.
	template <class... Args>
	static void connect(node<T, E>& n1, node<T, E>& n2, Args&&... args);
	template <class... Args>
	static void connect(iterator it1, iterator it2, Args&&... args);
	template <class... Args>
	static void connect(node_iterator it1, node_iterator it2, Args&&... args);

	static void disconnect(node<T, E>& n1, node<T, E>& n2);
	static void disconnect(iterator it1, iterator it2);
	static void disconnect(node_iterator it1, node_iterator it2);

	// Element access ----------------------------------------------------------

	// "Every container has to have a front() and back(). Except maybe 
	//  forward_list, but don't use forward_list"
	//     - andreasxp 2018
	T&       front();
	const T& front() const;
	T&       back();
	const T& back() const;

	// Modifiers ---------------------------------------------------------------
	node_iterator insert(const T& val);
	node_iterator insert(T&& val);

	template <class InputIt>
	void insert(InputIt first, InputIt last);
	void insert(std::initializer_list<value_type> ilist);

	template <class... Args>
	node_iterator emplace(Args&&... args);

	// Erase nodes
	iterator erase(iterator it);
	node_iterator erase(node_iterator it);
	
	// Erase edges
	edge_iterator erase(edge_iterator it);
	void erase(edge<T, E> e);

	void clear() noexcept;

	void reserve(size_type new_size);

	// Observers --------------------------------------------------------------
	bool empty() const noexcept;
	std::size_t size() const noexcept;

	std::size_t count_edges() const noexcept;
	double ratio() const noexcept;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const graph<T>& obj);

template <class T>
void to_json(json& j, const graph<T>& obj);

template <class T>
void from_json(const json& j, graph<T>& obj);

template<class T, class E>
inline void swap(graph<T, E>& lhs, graph<T, E>& rhs) noexcept;

} // namespace zh

#include "graph_void_E.hpp"

#include "iterator.hpp"
#include "node_iterator.hpp"
#include "edge_iterator.hpp"

#include "nodes_view.hpp"
#include "edges_view.hpp"

#include "graph.inl"