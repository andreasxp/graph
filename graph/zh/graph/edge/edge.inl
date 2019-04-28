#pragma once
#include <cassert>
#include "edge.hpp"

namespace zh {

template<class T, class E>
inline edge<T, E>::edge(node<T, E>* first_ptr, node<T, E>* second_ptr, E* value_ptr) :
	m_first_ptr(first_ptr),
	m_second_ptr(second_ptr),
	m_value_ptr(value_ptr) {
	assert(first_ptr && second_ptr && value_ptr);
}

template<class T>
inline edge<T, void>::edge(node<T, void>* first_ptr, node<T, void>* second_ptr) :
	m_first_ptr(first_ptr),
	m_second_ptr(second_ptr) {
	assert(first_ptr && second_ptr);
}

template<class T, class E>
inline node<T, E>& edge<T, E>::first() noexcept {
	assert(m_first_ptr);
	return *m_first_ptr;
}

template<class T, class E>
inline const node<T, E>& edge<T, E>::first() const noexcept {
	assert(m_first_ptr);
	return *m_first_ptr;
}

template<class T, class E>
inline node<T, E>& edge<T, E>::second() noexcept {
	assert(m_second_ptr);
	return *m_second_ptr;
}

template<class T, class E>
inline const node<T, E>& edge<T, E>::second() const noexcept {
	assert(m_second_ptr);
	return *m_second_ptr;
}

template<class T, class E>
inline E& edge<T, E>::value() noexcept {
	assert(m_value_ptr);
	return *m_value_ptr;
}

template<class T, class E>
inline const E& edge<T, E>::value() const noexcept {
	assert(m_value_ptr);
	return *m_value_ptr;
}

template<class T, class E>
inline const_edge<T, E>::const_edge(const node<T, E>* first_ptr, const node<T, E>* second_ptr, const E* value_ptr) :
	m_first_ptr(first_ptr),
	m_second_ptr(second_ptr),
	m_value_ptr(value_ptr) {
}

template<class T>
inline const_edge<T, void>::const_edge(const node<T, void>* first_ptr, const node<T, void>* second_ptr) :
	m_first_ptr(first_ptr),
	m_second_ptr(second_ptr) {
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
	assert(m_first_ptr);
	return *m_first_ptr;
}

template<class T, class E>
inline const node<T, E>& const_edge<T, E>::second() const noexcept {
	assert(m_second_ptr);
	return *m_second_ptr;
}

template<class T, class E>
inline const E& const_edge<T, E>::value() const noexcept {
	assert(m_value_ptr);
	return *m_value_ptr;
}

} // namespace zh