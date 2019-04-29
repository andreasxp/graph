#pragma once
#include <cassert>
#include "edge.hpp"

namespace zh {

template<class T, class E>
inline edge<T, E>::edge(node<T, E>& first, node<T, E>& second, E& value) :
	m_first_ptr(&first),
	m_second_ptr(&second),
	m_value_ptr(&value) {
}

template<class T>
inline edge<T, void>::edge(node<T, void>& first, node<T, void>& second) :
	m_first_ptr(&first),
	m_second_ptr(&second) {
}

template<class T, class E>
inline node<T, E>& edge<T, E>::first() noexcept {
	return *m_first_ptr;
}

template<class T, class E>
inline const node<T, E>& edge<T, E>::first() const noexcept {
	return *m_first_ptr;
}

template<class T, class E>
inline node<T, E>& edge<T, E>::second() noexcept {
	return *m_second_ptr;
}

template<class T, class E>
inline const node<T, E>& edge<T, E>::second() const noexcept {
	return *m_second_ptr;
}

template<class T, class E>
inline E& edge<T, E>::value() noexcept {
	return *m_value_ptr;
}

template<class T, class E>
inline const E& edge<T, E>::value() const noexcept {
	return *m_value_ptr;
}

template<class T, class E>
inline const_edge<T, E>::const_edge(const node<T, E>& first, const node<T, E>& second, const E& value) :
	m_first_ptr(&first),
	m_second_ptr(&second),
	m_value_ptr(&value) {
}

template<class T>
inline const_edge<T, void>::const_edge(const node<T, void>& first, const node<T, void>& second) :
	m_first_ptr(&first),
	m_second_ptr(&second) {
}

template<class T, class E>
inline const_edge<T, E>::const_edge(const edge<T, E>& other) noexcept :
	m_first_ptr(&other.first()),
	m_second_ptr(&other.second()),
	m_value_ptr(&other.value()) {
}

template<class T>
inline const_edge<T, void>::const_edge(const edge<T, void>& other) noexcept :
	m_first_ptr(&other.first()),
	m_second_ptr(&other.second()) {
}

template<class T, class E>
inline const node<T, E>& const_edge<T, E>::first() const noexcept {
	return *m_first_ptr;
}

template<class T, class E>
inline const node<T, E>& const_edge<T, E>::second() const noexcept {
	return *m_second_ptr;
}

template<class T, class E>
inline const E& const_edge<T, E>::value() const noexcept {
	return *m_value_ptr;
}

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

} // namespace zh