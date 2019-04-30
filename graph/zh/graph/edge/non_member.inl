#pragma once
#include "non_member.hpp"
#include "edge.hpp"

namespace zh {

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const edge<T, E>& e) {
	os << "{#" << e.first().id() << " - #" << e.second().id();

	if constexpr (!std::is_same_v<E, void>) {
		os << " (value: " << e.value() << ")";
	}

	os << "}";

	return os;
}

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const const_edge<T, E>& e) {
	os << "{#" << e.first().id() << " - #" << e.second().id();

	if constexpr (!std::is_same_v<E, void>) {
		os << " (value: " << e.value() << ")";
	}

	os << "}";

	return os;
}

}