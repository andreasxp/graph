#pragma once
#include <iterator>
#include "fprism.hpp"

namespace zh {

// Member functions ===========================================================
// Iterators ------------------------------------------------------------------
template<class C, class It, class CIt, class IArgs>
constexpr It fprism<C, It, CIt, IArgs>::begin() noexcept {
	using std::make_from_tuple;
	using std::make_tuple;
	using std::tuple_cat;

	return make_from_tuple<It>(
		tuple_cat(make_tuple(this->m_data.begin()), this->args()));
}

template<class C, class It, class CIt, class IArgs>
constexpr It fprism<C, It, CIt, IArgs>::end() noexcept {
	using std::make_from_tuple;
	using std::make_tuple;
	using std::tuple_cat;

	return make_from_tuple<It>(
		tuple_cat(make_tuple(this->m_data.end()), this->args()));
}

// Element access -------------------------------------------------------------
template<class C, class It, class CIt, class IArgs>
constexpr decltype(auto) fprism<C, It, CIt, IArgs>::front() {
	return *begin();
}

template<class C, class It, class CIt, class IArgs>
constexpr decltype(auto) fprism<C, It, CIt, IArgs>::back() {
	return *std::prev(end());
}

template<class C, class It, class CIt, class IArgs>
constexpr decltype(auto) fprism<C, It, CIt, IArgs>::operator[](difference_type offset) {
	return begin()[offset];
}

} // namespace zh