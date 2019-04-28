#pragma once
#include "graph.hpp"
#include <boost/iterator/iterator_adaptor.hpp>

namespace zh {

template <class T, class E>
class graph<T, E>::iterator
	: public boost::iterator_adaptor<
	typename graph<T, E>::iterator,
	typename graph<T, E>::container::iterator,
	T,
	boost::iterators::use_default,
	T&> {

private:
	using base_t = boost::iterator_adaptor<
		typename graph<T, E>::iterator,
		typename graph<T, E>::container::iterator,
		T,
		boost::iterators::use_default,
		T&>;
	friend class boost::iterator_core_access;

	T& dereference() const noexcept;

public:
	using base_t::base_t;
	iterator(typename graph<T, E>::node_iterator other) noexcept;
};

template <class T, class E>
class graph<T, E>::const_iterator
	: public boost::iterator_adaptor<
	typename graph<T, E>::const_iterator,
	typename graph<T, E>::container::const_iterator,
	T,
	boost::iterators::use_default,
	const T&> {

private:
	using base_t = boost::iterator_adaptor<
		typename graph<T, E>::const_iterator,
		typename graph<T, E>::container::const_iterator,
		T,
		boost::iterators::use_default,
		const T&>;
	friend class boost::iterator_core_access;

	const T& dereference() const noexcept;

public:
	using base_t::base_t;
	const_iterator(typename graph<T, E>::iterator other) noexcept;
	const_iterator(typename graph<T, E>::node_iterator other) noexcept;
	const_iterator(typename graph<T, E>::const_node_iterator other) noexcept;
};

} // namespace zh

#include "iterator.inl"