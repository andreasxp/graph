# `graph`
A collection of C++ classes for representing graphs.

# Installation
Graph can be installed as a single-header library with no additional dependencies. It can be compiled using a favorite tool of your choice from `zh/graph.hpp`. Optionally it can also be used as a single CMake package or via `conan`.

CMake offers the target `zh::graph` for linking with other libraries. Options graph_BUILD_TESTS and graph_BUILD_EXAMPLES (default off) can be turned on to build tests and examples for this library.

Conan package manager can be used to locally install this library with options `tests` and `examples` corresponding to the CMake switches.

# Usage
The main class of this library is `zh::graph`:
```C++
template <class T, class E>
class graph;
```
Where T and E are types of values to be stored in nodes and edges of the graph.

Graph is a container - iterating over it will allow you to iteratre over it's node values:
```C++
zh::graph<int> g;
g.emplace(1);
g.emplace(2);
g.emplace(3);
g.emplace(4);

for (auto& i : g) {
    std::cout << i; // prints 1234
}
```
`zh::graph` also allows you to iterate over it's nodes and edges directly:
```C++
for (zh::node& i : g.nodes()) {
}

for (zh::edge i : g.edges()) {
}
```
Note that `edge` is not a reference - the graph does not store edges as objects and creates them on demand. `zh::edge` only holds information about the nodes, the direction, and the value.

# Reference
## zh::graph
Public functions:
```C++
iterator       begin() noexcept;
const_iterator begin() const noexcept;
const_iterator cbegin() const noexcept;
```
Iterator access to node values of the graph. Returns `iterator` or `const_iterator` to the first value.  
Note: although values preserve insertion order, this behavior should not be relied upon and may be changed in future releases of `graph`.
```C++
iterator       end() noexcept;
const_iterator end() const noexcept;
const_iterator cend() const noexcept;
```
Iterator access to node values of the graph. Returns `iterator` or `const_iterator` to the past-the-end value.  
Note: although values preserve insertion order, this behavior should not be relied upon and may be changed in future releases of `graph`.
```C++
nodes_view       nodes() noexcept;
const_nodes_view nodes() const noexcept;
```
Provides a view into the nodes of the graph. `nodes_view` is similar to `string_view` in that it provides a reference to values, and should not outlive the graph.
```C++
edges_view       edges() noexcept;
const_edges_view edges() const noexcept;
```
Provides a view into the nodes of the graph. `edges_view` is similar to `string_view` in that it provides a reference to values, and should not outlive the graph. Note that edges are not stored in the graph - `edges_view` generates them on demand.
```C++
template <class... Args>
static void connect(node<T, E>& nd1, node<T, E>& nd2, Args&&... args);
template <class... Args>
static void connect(iterator it1, iterator it2, Args&&... args);
template <class... Args>
static void connect(node_iterator it1, node_iterator it2, Args&&... args);
```
Connects two nodes with an edge. The edge value is constructed from `args`. This function can connect two nodes, two iterators, or two node_iterators.
```C++
static void disconnect(node<T, E>& nd1, node<T, E>& nd2);
static void disconnect(iterator it1, iterator it2);
static void disconnect(node_iterator it1, node_iterator it2);
```
Connects two nodes with an edge. The edge value is destroyed. This function can disconnect two nodes, two iterators, or two node_iterators.
```C++
T&       front();
const T& front() const;
```
Access the value of the first node in the graph.  
Note: although values preserve insertion order, this behavior should not be relied upon and may be changed in future releases of `graph`.
```C++
T&       back();
const T& back() const;
```
Access the value of the last node in the graph.  
Note: although values preserve insertion order, this behavior should not be relied upon and may be changed in future releases of `graph`.
```C++
node_iterator insert(const T& val);
node_iterator insert(T&& val);
template <class InputIt>
void insert(InputIt first, InputIt last);
void insert(std::initializer_list<value_type> ilist);
```
Inserts values into the graph as new nodes.
```C++
template <class... Args>
node_iterator emplace(Args&&... args);
```
Emplaces a new node containing the `T` value constructed from `args`.
```C++
iterator erase(iterator it);
node_iterator erase(node_iterator it);
void erase(edge<T, E> e);
```
Erases items from graph. Can erase a node via an iterator or node_iterator, or can erase an edge.
```C++
void clear() noexcept;
```
Removes everything from the graph.
```C++
void reserve(size_type new_size);
```
```C++
bool empty() const noexcept;
```
```C++
std::size_t size() const noexcept;
```
```C++
std::size_t capacity() const noexcept;
```
```C++
std::size_t count_edges() const noexcept;
```
```C++
double ratio() const noexcept;
```
