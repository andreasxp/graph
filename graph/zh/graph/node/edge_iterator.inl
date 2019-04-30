#pragma once
#include "edge_iterator.hpp"

namespace zh {

template <class T, class E>
node_edge_iterator<T, E>::node_edge_iterator(typename detail::node_container<T, E>::iterator iter, node<T, E>& source) :
	base_type(iter),
	m_source(source) {
}

template <class T, class E>
edge<T, E> node_edge_iterator<T, E>::dereference() const noexcept {
	if constexpr (std::is_same_v<E, void>) {
		return edge<T, E>(&m_source, this->base_reference()->ptr); // no value
	}
	else {
		return edge<T, E>(&m_source, this->base_reference()->ptr, this->base_reference()->value.get());
	}
}

template <class T, class E>
node_const_edge_iterator<T, E>::node_const_edge_iterator(typename detail::node_container<T, E>::const_iterator iter, const node<T, E>& source) :
	base_type(iter),
	m_source(source) {
}

template <class T, class E>
const_edge<T, E> node_const_edge_iterator<T, E>::dereference() const noexcept {
	if constexpr (std::is_same_v<E, void>) {
		return const_edge<T, E>(&m_source, this->base_reference()->ptr); // no value
	}
	else {
		return const_edge<T, E>(&m_source, this->base_reference()->ptr, this->base_reference()->value.get());
	}
}

template <class T, class E>
node_const_edge_iterator<T, E>::node_const_edge_iterator(const node_edge_iterator<T, E>& other) :
	node_const_edge_iterator(other.base(), other.m_source) {
}

} // namespace zh