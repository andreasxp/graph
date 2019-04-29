#pragma once
#include "node.hpp"

namespace zh {

template<class T, class E>
template<class ...Args>
inline node<T, E>::node(Args&&... value_args) :
	m_value(std::forward<Args>(value_args)...) {
	static_assert(std::is_constructible_v<T, Args&&...>, "node's value (T) cannot be constructed from these arguments");
}

template<class T, class E>
inline typename node<T, E>::nodes_view 
node<T, E>::adjacent_nodes() noexcept {
	return nodes_view(m_connections);
}

template<class T, class E>
inline typename node<T, E>::const_nodes_view 
node<T, E>::adjacent_nodes() const noexcept {
	return const_nodes_view(m_connections);
}

template<class T, class E>
inline typename node<T, E>::edges_view 
node<T, E>::edges() noexcept {
	return edges_view(m_connections, *this);
}

template<class T, class E>
inline typename node<T, E>::const_edges_view 
node<T, E>::edges() const noexcept {
	return const_edges_view(m_connections, *this);
}

template<class T, class E>
inline typename node<T, E>::id_type 
node<T, E>::id() const noexcept {
	return reinterpret_cast<id_type>(this);
}

template<class T, class E>
inline T& node<T, E>::value() noexcept {
	return m_value;
}

template<class T, class E>
inline const T& node<T, E>::value() const noexcept {
	return m_value;
}

template<class T, class E>
template<class ...Args>
inline void node<T, E>::connect(node& n, Args&&... edge_args) {
	if constexpr (std::is_same_v<E, void>) {
		static_assert(sizeof...(Args) == 0, "can't construct edge value from provided Args, edge has no value");
	}
	else {
		static_assert(std::is_constructible_v<E, Args&&...>, "edge's value (E) cannot be constructed from these arguments");
		auto edge_ptr = make_manual<E>(std::forward<Args>(edge_args)...);

		// Make connections
		auto [con1, con2] = make_connections(*this, n, std::forward<Args>(edge_args)...);

		// Create and get a ref to connection 1
		auto& con = *m_connections.insert(std::move(con1)).first;
		// Create connection 2
		n.m_connections.insert(std::move(con2));

		assert(con.value_ptr().has_deleter()); // Connection 1 should hold the deleter to the value that is shared between connections
	}
}

template<class T, class E>
inline void node<T, E>::disconnect(node& n) {
	  m_connections.erase(connection<T, E>::valueless(n));
	n.m_connections.erase(connection<T, E>::valueless(*this));
}

} // namespace zh

namespace std {

template<class T, class E>
struct hash<zh::node<T, E>> {
	hash() = default;

	size_t operator()(zh::node<T, E> const& n) const noexcept {
		return std::hash<const zh::node<T, E>*>()(&n);
	}
};

}