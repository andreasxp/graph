#pragma once
#include "deps/zh/prism.hpp"
#include "graph.hpp"
#include "edge_iterator.hpp"

namespace zh {

template <class T, class E>
class graph<T, E>::edges_view {
private:
	using container = typename graph<T, E>::container;
	container& m_data;

public:
	// Member types ===========================================================
	using iterator        = typename graph<T, E>::edge_iterator;
	using const_iterator  = typename graph<T, E>::const_edge_iterator;

	using value_type      = typename std::iterator_traits<iterator>::value_type;
	using reference       = typename std::iterator_traits<iterator>::reference;
	using const_reference = typename std::iterator_traits<const_iterator>::reference;
	using pointer         = typename std::iterator_traits<iterator>::pointer;
	using const_pointer   = typename std::iterator_traits<const_iterator>::pointer;

	using size_type       = std::size_t;
	using difference_type = typename std::iterator_traits<iterator>::difference_type;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	constexpr edges_view(container& data);

	// Iterators --------------------------------------------------------------
	constexpr iterator begin() noexcept;
	constexpr const_iterator begin() const noexcept;
	constexpr const_iterator cbegin() const noexcept;

	constexpr iterator end() noexcept;
	constexpr const_iterator end() const noexcept;
	constexpr const_iterator cend() const noexcept;

	// Element access ---------------------------------------------------------
	constexpr decltype(auto) front();
	constexpr decltype(auto) front() const;
	constexpr decltype(auto) back();
	constexpr decltype(auto) back() const;

	// Capacity ---------------------------------------------------------------
	constexpr std::size_t size() const noexcept;
	constexpr bool empty() const noexcept;
};

template <class T, class E>
class graph<T, E>::const_edges_view {
private:
	using container = const typename graph<T, E>::container;
	container& m_data;

public:
	// Member types ===========================================================
	using iterator        = typename graph<T, E>::const_edge_iterator;
	using const_iterator  = typename graph<T, E>::const_edge_iterator;

	using value_type      = typename std::iterator_traits<const_iterator>::value_type;
	using reference       = typename std::iterator_traits<const_iterator>::reference;
	using const_reference = typename std::iterator_traits<const_iterator>::reference;
	using pointer         = typename std::iterator_traits<const_iterator>::pointer;
	using const_pointer   = typename std::iterator_traits<const_iterator>::pointer;

	using size_type       = std::size_t;
	using difference_type = typename std::iterator_traits<const_iterator>::difference_type;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	constexpr const_edges_view(container& data);
	constexpr const_edges_view(const edges_view& other);

	// Iterators --------------------------------------------------------------
	constexpr const_iterator begin() const noexcept;
	constexpr const_iterator cbegin() const noexcept;

	constexpr const_iterator end() const noexcept;
	constexpr const_iterator cend() const noexcept;

	// Element access ---------------------------------------------------------
	constexpr decltype(auto) front() const;
	constexpr decltype(auto) back() const;

	// Capacity ---------------------------------------------------------------
	constexpr std::size_t size() const noexcept;
	constexpr bool empty() const noexcept;
};

} // namespace zh