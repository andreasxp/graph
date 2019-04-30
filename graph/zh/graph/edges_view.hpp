#pragma once
#include "graph_helpers.hpp"
#include "graph.hpp"

namespace zh {
namespace detail {

template <class T, class E>
auto make_edges_view(graph_container<T, E>& c) {
	return ranges::view::for_each(c, [] (auto & node_ptr) {
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

template <class T, class E>
auto make_edges_view(const graph_container<T, E>& c) {
	return ranges::view::for_each(c, [] (auto & node_ptr) {
		auto& nd1 = *node_ptr;

		return ranges::view::for_each(nd1.m_connections, [&nd1] (auto & con) {
			auto& nd2 = *con;

			if constexpr (std::is_same_v<E, void>) {
				return ranges::yield_if(nd1.id() < nd2.id(), const_edge<T, void>(nd1, nd2));
			}
			else {
				return ranges::yield_if(nd1.id() < nd2.id(), const_edge<T, E>(nd1, nd2, con.value()));
			}
			});
		});
}

template <class T, class E>
using graph_edges_view_raw
	= decltype(make_edges_view(std::declval<graph_container<T, E>&>()));
template <class T, class E>
using graph_const_edges_view_raw
	= decltype(make_edges_view(std::declval<const graph_container<T, E>&>()));

} // namespace detail

template <class T, class E>
class graph_edges_view : public detail::graph_edges_view_raw<T, E> {
private:
	using base = detail::graph_edges_view_raw<T, E>;

	detail::graph_container<T, E>& m_data;

public:
	// Member types ===========================================================
	using value_type      = edge<T, E>;

	using size_type       = std::size_t;
	using difference_type = std::ptrdiff_t;

	using iterator        = decltype(std::declval<base>().begin());

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	graph_edges_view(detail::graph_container<T, E>& c);

	// Operations -------------------------------------------------------------
	std::size_t size() const noexcept;
	bool empty() const noexcept;

	// Friends ================================================================
	template <class T_, class E_>
	friend class graph_const_edges_view;
};

template <class T, class E>
class graph_const_edges_view : public detail::graph_const_edges_view_raw<T, E> {
private:
	using base = detail::graph_const_edges_view_raw<T, E>;

	const detail::graph_container<T, E>& m_data;

public:
	// Member types ===========================================================
	using value_type      = const_edge<T, E>;

	using size_type       = std::size_t;
	using difference_type = std::ptrdiff_t;

	using iterator        = decltype(std::declval<base>().begin());

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	graph_const_edges_view(const detail::graph_container<T, E>& c);
	graph_const_edges_view(const graph_edges_view<T, E>& view);

	// Operations -------------------------------------------------------------
	std::size_t size() const noexcept;
	bool empty() const noexcept;
};

} // namespace zh

#include "edges_view.inl"