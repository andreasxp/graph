#pragma once
#include <variant>
#include "deps/zh/manual_ptr.hpp"
#include "../node/node_fwd.hpp"

namespace zh {

// Connection represents a "connection" one node has to another.
// This is not an edge, because an edge holds information about both source
// and target nodes, while a connection is a "pointer with extra data".
// Connection is sometimes responsible for deleting E (value) (see 
// manual_ptr.hpp), and never responsible for deleting nodes it's pointing to.
template <class T, class E>
struct connection {
	node<T, E>*   ptr;
	manual_ptr<E> value;
};

template <class T>
struct connection<T, void> {
	node<T, void>* ptr;
};

template<class T, class E> inline bool operator==(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator!=(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator< (const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator> (const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator<=(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator>=(const connection<T, E>& lhs, const connection<T, E>& rhs);

} // namespace zh

namespace std {

template <class T, class E>
struct hash<zh::connection<T, E>>;

}

#include "connection.inl"