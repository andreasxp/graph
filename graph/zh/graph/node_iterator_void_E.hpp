#pragma once
#include "graph.hpp"
#include "node_iterator.hpp"
#include <boost/iterator/indirect_iterator.hpp>

namespace zh {

template <class E>
class graph<void, E>::node_iterator
	: public boost::indirect_iterator<typename graph<void, E>::container::iterator> {
private:
	using base_t = boost::indirect_iterator<typename graph<void, E>::container::iterator>;

public:
	using base_t::base_t;
};

template <class E>
class graph<void, E>::const_node_iterator
	: public boost::indirect_iterator<
	typename graph<void, E>::container::const_iterator,
	boost::iterators::use_default,
	boost::iterators::use_default,
	const node<void, E>&> {
private:
	using base_t = boost::indirect_iterator<
		typename graph<void, E>::container::const_iterator,
		boost::iterators::use_default,
		boost::iterators::use_default,
		const node<void, E>&>;

public:
	using base_t::base_t;
	const_node_iterator(typename graph<void, E>::node_iterator other) noexcept;
};

// Definitions are shared with generic node_iterator in node_iterator.inl

} // namespace zh