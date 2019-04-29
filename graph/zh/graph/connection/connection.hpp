#pragma once
#include <variant>
#include "connection_fwd.hpp"
#include "deps/zh/manual_ptr.hpp"
#include "../node/node_fwd.hpp"

namespace zh {

// Connection represents a "connection" one node has to another.
// This is not an edge, because an edge holds information about both source
// and target nodes, while a connection is a "pointer with extra data".
// Connection is sometimes responsible for deleting E (value) (see 
// manual_ptr.hpp), and never responsible for deleting nodes it's pointing to.
template <class T, class E>
class connection {
private:
	node<T, E>*   m_node_ptr;
	manual_ptr<E> m_value_ptr;

	connection(node<T, E>* node_ptr, manual_ptr<E>&& value_ptr);

public:
	// Member types ===========================================================
	using value_type = E;
	using element_type = node<T, E>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	connection() = delete;

	connection(const connection&) = delete;
	connection(connection&&) = default;

	connection& operator=(const connection&) = delete;
	connection& operator=(connection&&) = default;

	template <class... Args>
	explicit connection(node<T, E>& where, Args&&... value_args);

	template <class T_, class E_, class... Args>
	friend std::pair<connection<T_, E_>, connection<T_, E_>>
	make_connections(node<T_, E_>& first, node<T_, E_>& second, Args&&... value_args);

	// Fake connection constructors
	// These don't construct actual valid connections. Use with caution.
	//template <class... Args>
	//static connection unpointed(Args&&... value_args);
	static connection valueless(node<T, E>& where);
	static connection blank();

	// Member access ----------------------------------------------------------
	node<T, E>& operator*() const noexcept;
	node<T, E>* get() const noexcept;
	node<T, E>* operator->() const noexcept;

	E& value() const noexcept;
	manual_ptr<E>& value_ptr() noexcept;
	const manual_ptr<E>& value_ptr() const noexcept;
};

template <class T>
class connection<T, void> {
private:
	node<T, void>* m_node_ptr;

	explicit connection(node<T, void>* node_ptr);

public:
	// Member types ===========================================================
	using value_type = void;
	using element_type = node<T, void>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	connection() = delete;

	connection(const connection&) = delete;
	connection(connection&&) = default;

	connection& operator=(const connection&) = delete;
	connection& operator=(connection&&) = default;

	explicit connection(node<T, void>& where);

	template <class T_, class E_, class... Args>
	friend std::pair<connection<T_, E_>, connection<T_, E_>>
	make_connections(node<T_, E_>& first, node<T_, E_>& second, Args&&... value_args);

	// Fake connection constructors
	// These don't construct actual valid connections. Use with caution.
	//static connection unpointed();
	static connection valueless(node<T, void>& where);
	static connection blank();

	// Member access ----------------------------------------------------------
	node<T, void>& operator*() const noexcept;
	node<T, void>* get() const noexcept;
	node<T, void>* operator->() const noexcept;
};

template<class T, class E> inline bool operator==(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator!=(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator< (const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator> (const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator<=(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator>=(const connection<T, E>& lhs, const connection<T, E>& rhs);

// Make two connections, from first to second and in reverse, with one value.
template <class T, class E, class... Args>
std::pair<connection<T, E>, connection<T, E>>
make_connections(node<T, E>& first, node<T, E>& second, Args&& ... value_args);

} // namespace zh

namespace std {

template <class T, class E>
struct hash<zh::connection<T, E>>;

}

#include "connection.inl"