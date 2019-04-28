#pragma once
#include <cstdint>
#include "cfprism.hpp"

namespace zh {

template <
	class C,
	class It,
	class CIt,
	class IArgs = std::tuple<>>
class fprism : public cfprism<C, CIt, IArgs> {
private:
	using base = cfprism<C, CIt, IArgs>;

public:
	// Member types ===========================================================
	using value_type      = typename std::iterator_traits<It>::value_type;
	using reference       = typename std::iterator_traits<It>::reference;
	using const_reference = typename std::iterator_traits<CIt>::reference;
	using pointer         = typename std::iterator_traits<It>::pointer;
	using const_pointer   = typename std::iterator_traits<CIt>::pointer;

	using size_type       = std::size_t;
	using difference_type = typename std::iterator_traits<It>::difference_type;

	using iterator        = It;
	using const_iterator  = CIt;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	using base::base;

	// Iterators --------------------------------------------------------------
	constexpr It begin() noexcept;
	// Other begins inherited

	constexpr It end() noexcept;
	// Other ends inherited

	// Element access ---------------------------------------------------------
	constexpr decltype(auto) front();
	// const version inherited

	constexpr decltype(auto) back();
	// const version inherited

	constexpr decltype(auto) operator[](difference_type offset);
	// const version inherited

	// Capacity methods inherited
};

} // namespace zh

#include "fprism.inl"