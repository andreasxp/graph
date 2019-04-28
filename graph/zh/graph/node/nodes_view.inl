#pragma once
#include "nodes_view.hpp"

namespace zh {

template<class T, class E>
inline typename node<T, E>::nodes_view::iterator
node<T, E>::nodes_view::find(const node<T, E>& n) {
	return this->m_data.find(connection<T, E>(&n, manual_ptr<E>(nullptr)));
}

template<class T, class E>
inline typename node<T, E>::nodes_view::const_iterator
node<T, E>::nodes_view::find(const node<T, E>& n) const {
	return this->m_data.find(connection<T, E>(&n, manual_ptr<E>(nullptr)));
}

template<class T, class E>
inline bool node<T, E>::nodes_view::contains(const node<T, E>& n) const {
	return find(n) != this->end();
}

template<class T, class E>
inline typename node<T, E>::const_nodes_view::const_iterator
node<T, E>::const_nodes_view::find(const node<T, E>& n) const {
	return this->m_data.find(connection<T, E>(&n, manual_ptr<E>(nullptr)));
}

template <class T, class E>
inline node<T, E>::const_nodes_view::const_nodes_view(const node<T, E>::nodes_view& other) :
	base(static_cast<typename node<T, E>::nodes_view::base const&>(other)) {
}

template<class T, class E>
inline bool node<T, E>::const_nodes_view::contains(const node<T, E>& n) const {
	return find(n) != this->end();
}

} // namespace zh