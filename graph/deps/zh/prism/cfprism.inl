#pragma once
#include <iterator>
#include "cfprism.hpp"

namespace zh {

// Member functions ===========================================================
// Private --------------------------------------------------------------------
template<class C, class CIt, class IArgs>
inline IArgs& cfprism<C, CIt, IArgs>::args() noexcept {
	return static_cast<IArgs&>(*this);
}

template<class C, class CIt, class IArgs>
inline const IArgs& cfprism<C, CIt, IArgs>::args() const noexcept {
	return static_cast<const IArgs&>(*this);
}

// Constructors ---------------------------------------------------------------
template<class C, class CIt, class IArgs>
inline constexpr cfprism<C, CIt, IArgs>::cfprism(C& container, const IArgs& iargs) :
	IArgs(iargs),
	m_data(container) {
}

// Iterators ------------------------------------------------------------------
template<class C, class CIt, class IArgs>
constexpr CIt cfprism<C, CIt, IArgs>::begin() const noexcept {
	using std::make_from_tuple;
	using std::make_tuple;
	using std::tuple_cat;

	// Make CIt from m_data.begin() and additional args()
	return make_from_tuple<CIt>(
		tuple_cat(make_tuple(m_data.begin()), args()));
}

template<class C, class CIt, class IArgs>
constexpr CIt cfprism<C, CIt, IArgs>::cbegin() const noexcept {
	using std::make_from_tuple;
	using std::make_tuple;
	using std::tuple_cat;

	return make_from_tuple<CIt>(
		tuple_cat(make_tuple(m_data.cbegin()), args()));
}

template<class C, class CIt, class IArgs>
constexpr CIt cfprism<C, CIt, IArgs>::end() const noexcept {
	using std::make_from_tuple;
	using std::make_tuple;
	using std::tuple_cat;

	return make_from_tuple<CIt>(
		tuple_cat(make_tuple(m_data.end()), args()));
}

template<class C, class CIt, class IArgs>
constexpr CIt cfprism<C, CIt, IArgs>::cend() const noexcept {
	using std::make_from_tuple;
	using std::make_tuple;
	using std::tuple_cat;

	return make_from_tuple<CIt>(
		tuple_cat(make_tuple(m_data.cend()), args()));
}

// Element access -------------------------------------------------------------
template<class C, class CIt, class IArgs>
constexpr decltype(auto) cfprism<C, CIt, IArgs>::front() const {
	return *begin();
}

template<class C, class CIt, class IArgs>
constexpr decltype(auto) cfprism<C, CIt, IArgs>::back() const {
	return *std::prev(end());
}

template<class C, class CIt, class IArgs>
constexpr decltype(auto) cfprism<C, CIt, IArgs>::operator[](difference_type offset) const {
	return begin()[offset];
}

// Capacity -------------------------------------------------------------------
template<class C, class CIt, class IArgs>
constexpr std::size_t cfprism<C, CIt, IArgs>::size() const noexcept {
	return std::size(m_data);
}

template<class C, class CIt, class IArgs>
constexpr bool cfprism<C, CIt, IArgs>::empty() const noexcept {
	return std::empty(m_data);
}

} // namespace zh