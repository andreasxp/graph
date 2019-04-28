#pragma once
#include "node_iterator.hpp"

namespace zh {

template <class T, class E>
inline graph<T, E>::node_iterator::node_iterator(typename graph<T, E>::iterator other) noexcept :
	base_t(other.base()) {
}

template <class T, class E>
inline graph<T, E>::const_node_iterator::const_node_iterator(typename graph<T, E>::node_iterator other) noexcept :
	base_t(other.base()) {
}

template <class T, class E>
inline graph<T, E>::const_node_iterator::const_node_iterator(typename graph<T, E>::iterator other) noexcept :
	base_t(other.base()) {
}

template <class T, class E>
inline graph<T, E>::const_node_iterator::const_node_iterator(typename graph<T, E>::const_iterator other) noexcept :
	base_t(other.base()) {
}

}