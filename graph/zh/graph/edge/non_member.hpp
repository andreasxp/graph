#pragma once
#include <iostream>
#include "edge_fwd.hpp"
#include "const_edge.hpp"

namespace zh {

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const edge<T, E>& e);

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const const_edge<T, E>& e);

} // namespace zh

#include "non_member.inl"