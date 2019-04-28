#pragma once
#include "iterator.hpp"

namespace zh {

template <class T, class E>
inline T& graph<T, E>::iterator::dereference() const noexcept {
	return (*this->base_reference())->value();
}

template <class T, class E>
inline graph<T, E>::iterator::iterator(typename graph<T, E>::node_iterator other) noexcept :
	base_t(other.base()) {
}

template <class T, class E>
inline const T& graph<T, E>::const_iterator::dereference() const noexcept {
	return (*this->base_reference())->value();
}

template <class T, class E>
inline graph<T, E>::const_iterator::const_iterator(typename graph<T, E>::iterator other) noexcept :
	base_t(other.base()) {
}

template <class T, class E>
inline graph<T, E>::const_iterator::const_iterator(typename graph<T, E>::node_iterator other) noexcept :
	base_t(other.base()) {
}

template <class T, class E>
inline graph<T, E>::const_iterator::const_iterator(typename graph<T, E>::const_node_iterator other) noexcept :
	base_t(other.base()) {
}

} // namespace zh