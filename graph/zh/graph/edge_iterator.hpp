#pragma once
#include <iterator>
#include <optional>
#include <boost/iterator/iterator_adaptor.hpp>
#include "graph.hpp"
#include "edge/edge.hpp"

namespace zh {

// TODO: Add comparison operators
template <class T, class E>
class graph<T, E>::edge_iterator
	: public boost::iterator_adaptor<
	typename graph<T, E>::edge_iterator,
	typename graph<T, E>::node_iterator,
	edge<T, E>,
	std::bidirectional_iterator_tag,
	edge<T, E>> {

private:
	using base_t = boost::iterator_adaptor<
		typename graph<T, E>::edge_iterator,
		typename graph<T, E>::node_iterator,
		edge<T, E>,
		std::bidirectional_iterator_tag,
		edge<T, E>>;

	friend class boost::iterator_core_access;
	friend class const_edge_iterator;

	// Members ================================================================
	// Edge iterator iterates over nodes, and for each node iterates over
	// their edges using m_second_iter.
	typename node<T, E>::edge_iterator m_secondary;

public:
	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	edge_iterator(
		typename graph<T, E>::node_iterator primary_iterator,
		typename node<T, E>::edge_iterator secondary_iterator);

private:
	// Access functions =======================================================
	typename graph<T, E>::node_iterator& primary() noexcept;
	const typename graph<T, E>::node_iterator& primary() const noexcept;
	typename node<T, E>::edge_iterator& secondary() noexcept;
	const typename node<T, E>::edge_iterator& secondary() const noexcept;

	bool is_valid() const noexcept;

	// Iterator functions -----------------------------------------------------
	void increment() noexcept;
	void decrement() noexcept;
	edge<T, E> dereference() const noexcept;
};

template <class T, class E>
class graph<T, E>::const_edge_iterator
	: public boost::iterator_adaptor<
	typename graph<T, E>::const_edge_iterator,
	typename graph<T, E>::const_node_iterator,
	const_edge<T, E>,
	std::bidirectional_iterator_tag,
	const_edge<T, E>> {

private:
	using base_t = boost::iterator_adaptor<
		typename graph<T, E>::const_edge_iterator,
		typename graph<T, E>::const_node_iterator,
		const_edge<T, E>,
		std::bidirectional_iterator_tag,
		const_edge<T, E>>;

	friend class boost::iterator_core_access;

	// Members ================================================================
	// Edge iterator iterates over nodes, and for each node iterates over
	// their edges using m_second_iter.
	typename node<T, E>::const_edge_iterator m_secondary;

public:
	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	const_edge_iterator(
		typename graph<T, E>::const_node_iterator primary_iterator,
		typename node<T, E>::const_edge_iterator secondary_iterator);
	const_edge_iterator(const edge_iterator& other);

private:
	// Access functions =======================================================
	typename graph<T, E>::const_node_iterator& primary() noexcept;
	const typename graph<T, E>::const_node_iterator& primary() const noexcept;
	typename node<T, E>::const_edge_iterator& secondary() noexcept;
	const typename node<T, E>::const_edge_iterator& secondary() const noexcept;

	bool is_valid() const noexcept;

	// Iterator functions -----------------------------------------------------
	void increment() noexcept;
	void decrement() noexcept;
	const_edge<T, E> dereference() const noexcept;
};

} // namespace zh

#include "edge_iterator.inl"