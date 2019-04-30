#pragma once
#include <vector>
#include <memory>
#include <range/v3/all.hpp>
#include "node/node.hpp"

namespace zh {
namespace detail {

template <class T, class E>
using graph_container = std::vector<std::unique_ptr<node<T, E>>>;

}
}