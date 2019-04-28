#pragma once
#include "edge_iterator.hpp"

#include <iostream>

namespace zh {

// edge_iterator ==============================================================
template <class T, class E>
inline graph<T, E>::edge_iterator::edge_iterator(
	typename graph<T, E>::node_iterator primary_iterator, 
	typename node<T, E>::edge_iterator secondary_iterator) :
	base_t(primary_iterator),
	m_secondary(secondary_iterator) {
}

template <class T, class E>
inline typename graph<T, E>::node_iterator& 
graph<T, E>::edge_iterator::primary() noexcept {
	return this->base_reference();
}

template <class T, class E>
inline const typename graph<T, E>::node_iterator&
graph<T, E>::edge_iterator::primary() const noexcept {
	return this->base_reference();
}

template <class T, class E>
inline typename node<T, E>::edge_iterator&
graph<T, E>::edge_iterator::secondary() noexcept {
	return m_secondary;
}

template <class T, class E>
inline const typename node<T, E>::edge_iterator& 
graph<T, E>::edge_iterator::secondary() const noexcept {
	return m_secondary;
}

template <class T, class E>
inline bool graph<T, E>::edge_iterator::is_valid() const noexcept {
	return secondary()->first().id() < secondary()->second().id();
}

template <class T, class E>
inline void graph<T, E>::edge_iterator::increment() noexcept {
	++secondary();

	// If secondary reached end(), advance primary and reset secondary to begin
	if (secondary() == primary()->edges().end()) {
		++primary();
		secondary() = primary()->edges().begin();
	}
}

template <class T, class E>
inline void graph<T, E>::edge_iterator::decrement() noexcept {
	// If secondary is at begin, decrement primary first
	if (secondary() == primary()->edges().begin()) {
		--primary();
		secondary() = primary()->edges().end();
	}
	
	--secondary();
}

template <class T, class E>
inline edge<T, E> graph<T, E>::edge_iterator::dereference() const noexcept {
	return *secondary();
}

// const_edge_iterator ========================================================
template <class T, class E>
inline graph<T, E>::const_edge_iterator::const_edge_iterator(
	typename graph<T, E>::const_node_iterator primary_iterator,
	typename node<T, E>::const_edge_iterator secondary_iterator) :
	base_t(primary_iterator),
	m_secondary(secondary_iterator) {
}

template <class T, class E>
inline typename graph<T, E>::const_node_iterator&
graph<T, E>::const_edge_iterator::primary() noexcept {
	return this->base_reference();
}

template <class T, class E>
inline const typename graph<T, E>::const_node_iterator&
graph<T, E>::const_edge_iterator::primary() const noexcept {
	return this->base_reference();
}

template <class T, class E>
inline typename node<T, E>::const_edge_iterator&
graph<T, E>::const_edge_iterator::secondary() noexcept {
	return m_secondary;
}

template <class T, class E>
inline const typename node<T, E>::const_edge_iterator&
graph<T, E>::const_edge_iterator::secondary() const noexcept {
	return m_secondary;
}

template <class T, class E>
inline bool graph<T, E>::const_edge_iterator::is_valid() const noexcept {
	return secondary()->first().id() < secondary()->second().id();
}

template <class T, class E>
inline void graph<T, E>::const_edge_iterator::increment() noexcept {
	++secondary();

	// If secondary reached end(), advance primary and reset secondary to begin
	if (secondary() == primary()->edges().end()) {
		++primary();
		secondary() = primary()->edges().begin();
	}
}

template <class T, class E>
inline void graph<T, E>::const_edge_iterator::decrement() noexcept {
	// If secondary is at begin, decrement primary first
	if (secondary() == primary()->edges().begin()) {
		--primary();
		secondary() = primary()->edges().end();
	}

	--secondary();
}

template <class T, class E>
inline const_edge<T, E> graph<T, E>::const_edge_iterator::dereference() const noexcept {
	return *secondary();
}

} // namespace zh