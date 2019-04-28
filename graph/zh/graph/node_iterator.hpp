#pragma once
#include "graph.hpp"
#include <boost/iterator/indirect_iterator.hpp>

namespace zh {

template <class T, class E>
class graph<T, E>::node_iterator
	: public boost::indirect_iterator<typename graph<T, E>::container::iterator> {
private:
	using base_t = boost::indirect_iterator<typename graph<T, E>::container::iterator>;

public:
	using base_t::base_t;
	node_iterator(typename graph<T, E>::iterator other) noexcept;
};

template <class T, class E>
class graph<T, E>::const_node_iterator
	: public boost::indirect_iterator<
		typename graph<T, E>::container::const_iterator,
		boost::iterators::use_default,
		boost::iterators::use_default,
		const node<T, E>&> {
private:
	using base_t = boost::indirect_iterator<
		typename graph<T, E>::container::const_iterator,
		boost::iterators::use_default,
		boost::iterators::use_default,
		const node<T, E>&>;

public:
	using base_t::base_t;
	const_node_iterator(typename graph<T, E>::node_iterator other) noexcept;
	const_node_iterator(typename graph<T, E>::iterator other) noexcept;
	const_node_iterator(typename graph<T, E>::const_iterator other) noexcept;
};

} // namespace zh

#include "node_iterator_void_E.hpp"

#include "node_iterator.inl"