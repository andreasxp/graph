#pragma once
#include "connection.hpp"
#include "../node/node.hpp"

namespace zh {

// Non-member functions =======================================================
template<class T, class E>
inline bool operator==(const connection<T, E>& lhs, const connection<T, E>& rhs) {
	if constexpr (std::is_same_v<E, void>) {
		return lhs.ptr == rhs.ptr;
	}
	else {
		return lhs.ptr == rhs.ptr && *(lhs.value) == *(rhs.value);
	}
}

template<class T, class E>
inline bool operator!=(const connection<T, E>& lhs, const connection<T, E>& rhs) {
	return !(lhs == rhs);
}

template<class T, class E>
inline bool operator< (const connection<T, E>& lhs, const connection<T, E>& rhs) {
	if constexpr (std::is_same_v<E, void>) {
		return lhs.ptr < rhs.ptr;
	}
	else {
		return
			(lhs.ptr < rhs.ptr) ||
			(lhs.ptr == rhs.ptr && *(lhs.value) < *(rhs.value));
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
			return ptr_hash(con.ptr);
		}
		else {
			return ptr_hash(con.ptr) xor std::hash<E>()(*(con.value));
		}
	}
};

}