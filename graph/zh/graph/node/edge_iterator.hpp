#pragma once
#include <boost/iterator/iterator_adaptor.hpp>
#include "node.hpp"
#include "../edge/edge_fwd.hpp"

namespace zh {

template <class T, class E>
class node<T, E>::edge_iterator
	: public boost::iterator_adaptor<
	typename node<T, E>::edge_iterator,
	typename node<T, E>::container::iterator,
	edge<T, E>,
	boost::iterators::use_default,
	edge<T, E>> {

private:
	using base = boost::iterator_adaptor<
		typename node<T, E>::edge_iterator,
		typename node<T, E>::container::iterator,
		edge<T, E>,
		boost::iterators::use_default,
		edge<T, E>>;
	friend class boost::iterator_core_access;

	node<T, E>& m_source;

	edge<T, E> dereference() const noexcept;

public:
	edge_iterator(typename container::iterator iter, node<T, E>& source);
};

template <class T, class E>
class node<T, E>::const_edge_iterator
	: public boost::iterator_adaptor<
	typename node<T, E>::const_edge_iterator,
	typename node<T, E>::container::const_iterator,
	const_edge<T, E>,
	boost::iterators::use_default,
	const_edge<T, E>> {

private:
	using base = boost::iterator_adaptor<
		typename node<T, E>::const_edge_iterator,
		typename node<T, E>::container::const_iterator,
		const_edge<T, E>,
		boost::iterators::use_default,
		const_edge<T, E>>;
	friend class boost::iterator_core_access;

	const node<T, E>& m_source;

	const_edge<T, E> dereference() const noexcept;

public:
	const_edge_iterator(typename container::const_iterator iter, const node<T, E>& source);
	const_edge_iterator(const node<T, E>::edge_iterator& other);
};

} // namespace zh

#include "edge_iterator.inl"