#pragma once
#include <range/v3/all.hpp>
#include "graph.hpp"
#include "edge/edge.hpp"

namespace zh {

// Constructors ===============================================================
template<class T, class E>
inline graph<T, E>::graph(const graph& other) {
	m_nodes.reserve(other.size());

	// Convert other node's ptr to new ptr
	ska::flat_hash_map<const node<T, E>*, node<T, E>*> ptr_match;

	// Emplacing all nodes without connecting ---------------------------------
	for (auto& n : other.nodes()) {
		// Emplace nodes and add them to the converter
		if constexpr (std::is_same_v<T, void>) {
			ptr_match[&n] = *emplace();
		}
		else {
			ptr_match[&n] = *emplace(n.value());
		}
	}

	// Connecting all nodes ---------------------------------------------------
	for (auto& e : other.edges()) {
		if (e.first().id() < e.second().id()) {
			connect(*ptr_match[&e.first()], *ptr_match[&e.second()]);
		}
	}
}

template<class T, class E>
inline graph<T, E>::graph(graph&& other) noexcept {
	swap(*this, other);
}

template<class T, class E>
inline graph<T, E>& graph<T, E>::operator=(graph rhs) {
	swap(*this, rhs);
	return *this;
}

template<class T, class E>
inline void swap(graph<T, E>& lhs, graph<T, E>& rhs) noexcept {
	// enable ADL
	using std::swap;

	swap(lhs.m_nodes, rhs.m_nodes);
}

// Iterators ==================================================================
template<class T, class E>
inline typename graph<T, E>::iterator graph<T, E>::begin() noexcept {
	return iterator(m_nodes.begin());
}

template<class T, class E>
inline typename graph<T, E>::const_iterator graph<T, E>::begin() const noexcept {
	return const_iterator(m_nodes.begin());
}

template<class T, class E>
inline typename graph<T, E>::const_iterator graph<T, E>::cbegin() const noexcept {
	return const_iterator(m_nodes.cbegin());
}

template<class T, class E>
inline typename graph<T, E>::iterator graph<T, E>::end() noexcept {
	return iterator(m_nodes.end());
}

template<class T, class E>
inline typename graph<T, E>::const_iterator graph<T, E>::end() const noexcept {
	return const_iterator(m_nodes.end());
}

template<class T, class E>
inline typename graph<T, E>::const_iterator graph<T, E>::cend() const noexcept {
	return const_iterator(m_nodes.cend());
}

template<class T, class E>
inline typename graph<T, E>::nodes_view graph<T, E>::nodes() noexcept {
	return nodes_view(m_nodes);
}

template<class T, class E>
inline typename graph<T, E>::const_nodes_view graph<T, E>::nodes() const noexcept {
	return const_nodes_view(m_nodes);
}

template<class T, class E>
inline auto graph<T, E>::edges() noexcept {
	return ranges::view::for_each(m_nodes, [] (auto & node_ptr) {
		auto& nd1 = *node_ptr;

		return ranges::view::for_each(nd1.m_connections, [&nd1] (auto & con) {
			auto& nd2 = *con;

			if constexpr (std::is_same_v<E, void>) {
				return ranges::yield_if(nd1.id() < nd2.id(), edge<T, void>(nd1, nd2));
			}
			else {
				return ranges::yield_if(nd1.id() < nd2.id(), edge<T, E>(nd1, nd2, con.value()));
			}
		});
	});
}

template<class T, class E>
inline auto graph<T, E>::edges() const noexcept {
	return ranges::view::for_each(m_nodes, [] (auto& node_ptr) {
		auto& nd1 = *node_ptr;

		return ranges::view::for_each(nd1.m_connections, [&nd1] (auto& con) {
			auto& nd2 = *con;

			if constexpr (std::is_same_v<E, void>) {
				return ranges::yield_if(nd1.id() < nd2.id(), edge<T, void>(nd1, nd2));
			}
			else {
				return ranges::yield_if(nd1.id() < nd2.id(), edge<T, E>(nd1, nd2, con.value()));
			}
		});
	});
}

// Connecting =================================================================
template<class T, class E>
template<class ...Args>
inline void graph<T, E>::connect(node<T, E>& n1, node<T, E>& n2, Args&&... edge_args) {
	if constexpr (std::is_same_v<E, void>) {
		static_assert(sizeof...(Args) == 0,
			"graph::connect: cannot construct edge value from provided args: graph has no edge values");
	}
	else {
		static_assert(std::is_constructible_v<E, Args&&...>,
			"graph::connect: cannot construct edge value from provided args");
	}

	n1.connect(n2, std::forward<Args>(edge_args)...);
}

template<class T, class E>
template<class ...Args>
inline void graph<T, E>::connect(iterator it1, iterator it2, Args&&... edge_args) {
	connect(node_iterator(it1), node_iterator(it2), std::forward<Args>(edge_args)...);
}

template<class T, class E>
template<class ...Args>
inline void graph<T, E>::connect(node_iterator it1, node_iterator it2, Args&&... edge_args) {
	connect(*it1, *it2, std::forward<Args>(edge_args)...);
}

template<class T, class E>
inline void graph<T, E>::disconnect(node<T, E>& n1, node<T, E>& n2) {
	n1.disconnect(n2);
}

template<class T, class E>
inline void graph<T, E>::disconnect(iterator it1, iterator it2) {
	disconnect(node_iterator(it1), node_iterator(it2));
}

template<class T, class E>
inline void graph<T, E>::disconnect(node_iterator it1, node_iterator it2) {
	disconnect(*it1, *it2);
}

// Modifiers ==================================================================
template<class T, class E>
template<class ...Args>
inline typename graph<T, E>::node_iterator graph<T, E>::emplace(Args&& ...args) {
	m_nodes.emplace_back(
		std::make_unique<node<T, E>>(std::forward<Args>(args)...));

	return std::prev(nodes().end());
}

} // namespace zh