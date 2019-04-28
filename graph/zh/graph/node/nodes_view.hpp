#pragma once
#include "node.hpp"
#include "node_iterator.hpp"
#include "deps/zh/prism.hpp"

namespace zh {

template <class T, class E>
class node<T, E>::nodes_view 
	: public zh::fprism<
		node<T, E>::container,
		node<T, E>::node_iterator,
		node<T, E>::const_node_iterator> {
private:
	using base = zh::fprism<
		node<T, E>::container,
		node<T, E>::node_iterator,
		node<T, E>::const_node_iterator>;

	friend class node<T, E>::const_nodes_view;
public:
	using base::base;

	using iterator       = typename base::iterator;
	using const_iterator = typename base::const_iterator;
	// other typedefs are not explicitly defined because not needed in class definition.
	// they are still available for class users.

	iterator       find(const node<T, E>& n);
	const_iterator find(const node<T, E>& n) const;

	bool contains(const node<T, E>& n) const;
};

template <class T, class E>
class node<T, E>::const_nodes_view
	: public zh::cfprism<
	node<T, E>::container,
	node<T, E>::const_node_iterator> {
private:
	using base = zh::cfprism<
		node<T, E>::container,
		node<T, E>::const_node_iterator>;

public:
	using const_iterator = typename base::const_iterator;
	// other typedefs are not explicitly defined because not needed in class definition.
	// they are still available for class users.

	using base::base;
	const_nodes_view(const node<T, E>::nodes_view& other);

	typename base::const_iterator find(const node<T, E>& n) const;

	bool contains(const node<T, E>& n) const;
};

} // namespace zh

#include "nodes_view.inl"