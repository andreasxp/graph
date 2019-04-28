#pragma once
#include "edge_iterator.hpp"

namespace zh {

template <class T, class E>
inline node<T, E>::edge_iterator::edge_iterator(typename container::iterator iter, node<T, E>& source) :
	base(iter),
	m_source(source) {
}

template <class T, class E>
inline edge<T, E> node<T, E>::edge_iterator::dereference() const noexcept {
	if constexpr (std::is_same_v<E, void>) {
		return edge<T, E>(&m_source, this->base_reference()->ptr); // no value
	}
	else {
		return edge<T, E>(&m_source, this->base_reference()->ptr, this->base_reference()->value.get());
	}
}

template <class T, class E>
inline node<T, E>::const_edge_iterator::const_edge_iterator(typename container::const_iterator iter, const node<T, E>& source) :
	base(iter),
	m_source(source) {
}

template <class T, class E>
inline const_edge<T, E> node<T, E>::const_edge_iterator::dereference() const noexcept {
	if constexpr (std::is_same_v<E, void>) {
		return const_edge<T, E>(&m_source, this->base_reference()->ptr); // no value
	}
	else {
		return const_edge<T, E>(&m_source, this->base_reference()->ptr, this->base_reference()->value.get());
	}
}

template <class T, class E>
inline node<T, E>::const_edge_iterator::const_edge_iterator(const node<T, E>::edge_iterator& other) :
	const_edge_iterator(other.base(), other.m_source) {
}

} // namespace zh