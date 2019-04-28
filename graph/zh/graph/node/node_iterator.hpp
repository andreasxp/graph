#pragma once
#include <boost/iterator/indirect_iterator.hpp>
#include "node.hpp"

namespace zh {

template <class T, class E>
class node<T, E>::node_iterator 
	: public boost::indirect_iterator<typename node<T, E>::container::iterator> {
private:
	using base = boost::indirect_iterator<typename node<T, E>::container::iterator>;

public:
	using base::base;
};

template <class T, class E>
class node<T, E>::const_node_iterator
	: public boost::indirect_iterator<
		typename node<T, E>::container::const_iterator,
		boost::iterators::use_default,
		boost::iterators::use_default,
		const node<T, E>&> {
private:
	using base = boost::indirect_iterator<
		typename node<T, E>::container::const_iterator,
		boost::iterators::use_default,
		boost::iterators::use_default,
		const node<T, E>&>;

public:
	using base::base;
	const_node_iterator(typename node<T, E>::node_iterator other) :
		base(other.base()) {}
};

} // namespace zh