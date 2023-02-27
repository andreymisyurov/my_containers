## My own container class implementation.<br>

#### Containers such as:<br>
- Vector<br>
- Array<br>
- Stack<br>
were developed in this project.<br>

Any container works fine with primitive data types like int, char, double, float etc<br>
`make test` command will run the tests<br>
`make docker-test` command will run the tests in ubuntu docker container<br>

Functions for the most part perform the same actions as in stl containers.<br>
Just `#include need_container.h`

(Also List, Set, Multiset, but I wrote this code 8 months ago,<br>
and now I'm a little ashamed of it. Therefore, they need to be refactored.<br>
I implement as I have free time)<br>

## Stack
![](misc/stack01.png)
*Stack Member type*
This table contains in-class type overrides (typical for the standard STL library) that are adopted to make class code easy to understand:
| Member type      | Definition                                       |
|------------------|--------------------------------------------------|
| `value_type`       | `T` the template parameter T                   |
| `reference`              | `T &` defines the type of the reference to an element                                                             |
| `const_reference`        | `const T &` defines the type of the constant reference                                         |
| `size_type`        | `size_t` defines the type of the container size (standard type is size_t) |

*Stack Member functions*
This table contains the main public methods for interacting with the class:
| Functions      | Definition                                      |
|----------------|-------------------------------------------------|
| `stack()`  | default constructor, creates an empty stack                                 |
| `stack(std::initializer_list<value_type> const &items)`  | initializer list constructor, creates stack initizialized using std::initializer_list<T>    |
| `stack(const stack &s)`  | copy constructor  |
| `stack(stack &&s)`  | move constructor  |
| `~stack()`  | destructor  |
| `operator=(stack &&s)`      | assignment operator overload for moving an object                                |
| `const_reference top()`              | accesses the top element                         |
| `bool empty()`          | checks whether the container is empty           |
| `size_type size()`           | returns the number of elements                  |
| `void push(const_reference value)`             | inserts an element at the top                       |
| `void pop()`              | removes the top element                        |
| `void swap(stack& other)`             | swaps the contents                               |


## Vector

*Vector Member type*
This table contains in-class type overrides (typical for the standard STL library) that are adopted to make class code easy to understand:
| Member type            | definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `value_type`             | `T` defines the type of the element (T is template parameter)                                  |
| `reference`              | `T &` defines the type of the reference to an element                                                             |
| `const_reference`        | `const T &` defines the type of the constant reference                                         |
| `iterator`               | `T *` or internal class `VectorIterator<T>` defines the type for iterating through the container                                                 |
| `const_iterator`         | `const T *` or internal class `VectorConstIterator<T>` defines the constant type for iterating through the container                                           |
| `size_type`              | `size_t` defines the type of the container size (standard type is size_t) |

*Vector Member functions*
This table contains the main public methods for interacting with the class:
| Functions      | Definition                                      |
|----------------|-------------------------------------------------|
| `vector()`  | default constructor, creates an empty vector                                 |
| `vector(size_type n)`  | parameterized constructor, creates the vector of size n                                 |
| `vector(std::initializer_list<value_type> const &items)`  | initializer list constructor, creates a vector initizialized using std::initializer_list<T>    |
| `vector(const vector &v)`  | copy constructor  |
| `vector(vector &&v)`  | move constructor  |
| `~vector()`  | destructor  |
| `operator=(vector &&v)`      | assignment operator overload for moving an object                                |

This table contains the public methods:
| Capacity               | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `bool empty()`          | checks whether the container is empty           |
| `size_type size()`           | returns the number of elements                  |
| `size_type max_size()`       | returns the maximum possible number of elements |
| `void reserve(size_type size)`                | allocate storage of size elements and copies current array elements to a newely allocated array                                     |
| `size_type capacity()`               | returns the number of elements that can be held in currently allocated storage         |
| `void shrink_to_fit()`          | reduces memory usage by freeing unused memory                                          |
| `iterator begin()`    | returns an iterator to the beginning            |
| `iterator end()`        | returns an iterator to the end                  |
| `reference at(size_type pos)`                     | access a specified element with bounds checking                                          |
| `reference operator[](size_type pos);`             | access a specified element                                                               |
| `const_reference front()`          | access the first element                        |
| `const_reference back()`           | access the last element                         |
| `iterator data()`                   | direct access the underlying array                                                  |
| `void clear()`          | clears the contents                             |
| `iterator insert(iterator pos, const_reference value)`         | inserts elements into concrete pos and returns the iterator that points to the new element     |
| `void erase(iterator pos)`          | erases an element at pos                                 |
| `void push_back(const_reference value)`      | adds an element to the end                      |
| `void pop_back()`   | removes the last element        |
| `void swap(vector& other)`                   | swaps the contents                                                                     |


## Array

Array is a sequence container that encapsulates a static array. You cannot add new elements to an array container, you can only modify the value of the original ones. In terms of interaction, a container array combines the obvious properties of a static array with the main advantage of container classes - a clearer organisation of data. For example, an Array container stores the size of an array and provides iterators. Just like a vector, an array occupies a sequential part of memory and can be passed to a function as a standard array in C. The second template argument of the array class is its actual size.<br>

*Array Member type*
This table contains in-class type overrides (typical for the standard STL library) that are adopted to make class code easy to understand:
| Member type            | definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `value_type`             | `T` defines the type of an element (T is template parameter)                                  |
| `reference`              | `T &` defines the type of the reference to an element                                                             |
| `const_reference`        | `const T &` defines the type of the constant reference                                         |
| `iterator`               | `T *` defines the type for iterating through the container                                                 |
| `const_iterator`         | `const T *` defines the constant type for iterating through the container                                           |
| `size_type`              | `size_t` defines the type of the container size (standard type is size_t) |

*Array Member functions*
This table contains the main public methods for interacting with the class:
| Functions      | Definition                                      |
|----------------|-------------------------------------------------|
| `array()`  | default constructor, creates an empty array                                 |
| `array(std::initializer_list<value_type> const &items)`  | initializer list constructor, creates array initizialized using std::initializer_list<T>    |
| `array(const array &a)`  | copy constructor  |
| `array(array &&a)`  | move constructor  |
| `~array()`  | destructor  |
| `operator=(array &&a)`      | assignment operator overload for moving an object                                |
| `reference at(size_type pos)`                     | access a specified element with bounds checking                                          |
| `reference operator[](size_type pos)`             | access a specified element                                                               |
| `const_reference front()`          | access the first element                        |
| `const_reference back()`           | access the last element                         |
| `iterator data()`                   | direct access to the underlying array                                                  |
| `iterator begin()`    | returns an iterator to the beginning            |
| `iterator end()`        | returns an iterator to the end                  |
| `bool empty()`          | checks whether the container is empty           |
| `size_type size()`           | returns the number of elements                  |
| `size_type max_size()`       | returns the maximum possible number of elements |
| `void swap(array& other)`                   | swaps the contents                                |
| `void fill(const_reference value);`         | assigns the given value to all elements in the container. |
