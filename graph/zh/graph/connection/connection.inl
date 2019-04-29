#pragma once
#include "connection.hpp"
#include "../node/node.hpp"

namespace zh {

template <class T, class E, class... Args>
std::pair<connection<T, E>, connection<T, E>>
make_connections(node<T, E>& first, node<T, E>& second, Args&&... value_args) {
	if constexpr (std::is_same_v<E, void>) {
		static_assert(sizeof...(Args) == 0, 
			"make_connections: arguments for constructing value_type were provided, but value_type is void");

		return std::make_pair(
			connection<T, void>(second),
			connection<T, void>(first)
		);
	}
	else {
		static_assert(std::is_constructible_v<E, Args&&...>, 
			"make_connections: cannot constuct value_type from these arguments");

		manual_ptr<E> value_ptr_1 = make_manual<E>(std::forward<Args>(value_args)...);
		manual_ptr<E> value_ptr_2 = value_ptr_1;

		return std::make_pair(
			connection<T, E>(&second, std::move(value_ptr_1)),
			connection<T, E>(&first,  std::move(value_ptr_2))
		);
	}
}

template<class T, class E>
inline connection<T, E>::connection(node<T, E>* node_ptr, manual_ptr<E>&& value_ptr) :
	m_node_ptr(node_ptr),
	m_value_ptr(std::move(value_ptr)) {
}

template<class T, class E>
inline connection<T, E> connection<T, E>::valueless(node<T, E>& where) {
	return connection(&where, nullptr);
}

template<class T, class E>
inline connection<T, E> connection<T, E>::blank() {
	return connection(nullptr, nullptr);
}

template<class T, class E>
inline node<T, E>& connection<T, E>::operator*() const noexcept {
	return *m_node_ptr;
}

template<class T, class E>
inline node<T, E>* connection<T, E>::get() const noexcept {
	return m_node_ptr;
}

template<class T, class E>
inline node<T, E>* connection<T, E>::operator->() const noexcept {
	return m_node_ptr;
}

template<class T, class E>
inline E& connection<T, E>::value() const noexcept {
	return *m_value_ptr;
}

template<class T, class E>
inline manual_ptr<E>& connection<T, E>::value_ptr() noexcept {
	return m_value_ptr;
}

template<class T, class E>
inline const manual_ptr<E>& connection<T, E>::value_ptr() const noexcept {
	return m_value_ptr;
}

template<class T, class E>
template<class ...Args>
inline connection<T, E>::connection(node<T, E>& where, Args&& ...value_args) :
	m_node_ptr(&where),
	m_value_ptr(make_manual<E>(std::forward<Args>(value_args)...)) {
	static_assert(std::is_constructible_v<E, Args &&...>,
		"connection::connection: cannot construct value_type from these args");
}

template<class T>
inline connection<T, void>::connection(node<T, void>* node_ptr) :
	m_node_ptr(&node_ptr) {
}

// Non-member functions =======================================================
template<class T, class E>
inline bool operator==(const connection<T, E>& lhs, const connection<T, E>& rhs) {
	if constexpr (std::is_same_v<E, void>) {
		return lhs.get() == rhs.get();
	}
	else {
		return lhs.get() == rhs.get() && lhs.value() == rhs.value();
	}
}

template<class T, class E>
inline bool operator!=(const connection<T, E>& lhs, const connection<T, E>& rhs) {
	return !(lhs == rhs);
}

template<class T, class E>
inline bool operator< (const connection<T, E>& lhs, const connection<T, E>& rhs) {
	if constexpr (std::is_same_v<E, void>) {
		return lhs.get() < rhs.get();
	}
	else {
		return
			(lhs.get() < rhs.get()) ||
			(lhs.get() == rhs.get() && lhs.value() < rhs.value());
	}
}

template<class T, class E>
inline bool operator> (const connection<T, E>& lhs, const connection<T, E>& rhs) {
	return rhs < lhs;
}

template<class T, class E>
inline bool operator<=(const connection<T, E>& lhs, const connection<T, E>& rhs) {
	return !(lhs > rhs);
}

template<class T, class E>
inline bool operator>=(const connection<T, E>& lhs, const connection<T, E>& rhs) {
	return !(lhs < rhs);
}

} // namespace zh

namespace std {

template <class T, class E>
struct hash<zh::connection<T, E>> {
	std::size_t operator()(const zh::connection<T, E>& con) const noexcept {
		auto ptr_hash = std::hash<const zh::node<T, void>*>();

		if constexpr (std::is_same_v<E, void>) {
			return ptr_hash(con.get());
		}
		else {
			return ptr_hash(con.get()) xor std::hash<E>()(con.value());
		}
	}
};

}