#pragma once
#include "edges_view.hpp"
#include "node_iterator.hpp"

namespace zh {

template <class T, class E>
constexpr graph<T, E>::edges_view::edges_view(container& data) :
	m_data(data) {
}

template <class T, class E>
constexpr typename graph<T, E>::edges_view::iterator
graph<T, E>::edges_view::begin() noexcept {
	auto primary = graph<T, E>::node_iterator(m_data.begin());
	return iterator(primary, primary->edges.begin());
}

template <class T, class E>
constexpr typename graph<T, E>::edges_view::const_iterator
graph<T, E>::edges_view::begin() const noexcept {
	auto primary = graph<T, E>::const_node_iterator(m_data.begin());
	return const_iterator(primary, primary->edges.begin());
}

template <class T, class E>
constexpr typename graph<T, E>::edges_view::const_iterator graph<T, E>::edges_view::cbegin() const noexcept {
	return const_iterator();
}

template <class T, class E>
constexpr typename graph<T, E>::edges_view::iterator graph<T, E>::edges_view::end() noexcept {
	return iterator();
}

template <class T, class E>
constexpr typename graph<T, E>::edges_view::const_iterator graph<T, E>::edges_view::end() const noexcept {
	return const_iterator();
}

template <class T, class E>
constexpr typename graph<T, E>::edges_view::const_iterator graph<T, E>::edges_view::cend() const noexcept {
	return const_iterator();
}

template <class T, class E>
constexpr decltype(auto) graph<T, E>::edges_view::front() {
}

template <class T, class E>
constexpr decltype(auto) graph<T, E>::edges_view::front() const {
}

template <class T, class E>
constexpr decltype(auto) graph<T, E>::edges_view::back() {
}

template <class T, class E>
constexpr decltype(auto) graph<T, E>::edges_view::back() const {
}

template <class T, class E>
constexpr bool graph<T, E>::edges_view::empty() const noexcept {
	return false;
}

template <class T, class E>
constexpr typename graph<T, E>::const_edges_view::const_iterator graph<T, E>::const_edges_view::begin() const noexcept {
	return const_iterator();
}

template <class T, class E>
constexpr typename graph<T, E>::const_edges_view::const_iterator graph<T, E>::const_edges_view::cbegin() const noexcept {
	return const_iterator();
}

template <class T, class E>
constexpr typename graph<T, E>::const_edges_view::const_iterator graph<T, E>::const_edges_view::end() const noexcept {
	return const_iterator();
}

template <class T, class E>
constexpr typename graph<T, E>::const_edges_view::const_iterator graph<T, E>::const_edges_view::cend() const noexcept {
	return const_iterator();
}

template <class T, class E>
constexpr decltype(auto) graph<T, E>::const_edges_view::front() const {
}

template <class T, class E>
constexpr decltype(auto) graph<T, E>::const_edges_view::back() const {
}

template <class T, class E>
constexpr std::size_t graph<T, E>::const_edges_view::size() const noexcept {
	return std::size_t();
}

template <class T, class E>
constexpr bool graph<T, E>::const_edges_view::empty() const noexcept {
	return false;
}

} // namespace zh