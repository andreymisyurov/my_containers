#ifndef SRC_MY_ARRAY_H_
#define SRC_MY_ARRAY_H_

#include <initializer_list>

namespace victoriv {

template <typename T, size_t N>
class Array {
 public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef const T *const_iterator;
  typedef size_t size_type;

 private:
  class iterator;

 public:
  Array();
  explicit Array(std::initializer_list<value_type> const &in_items);
  Array(const Array &in_other);
  Array(Array &&move_other);
  ~Array();

  auto operator[](size_type in_index)   -> value_type &;
  auto operator=(const Array &in_other) -> Array&;
  auto operator=(Array &&move_other)    -> Array&;

  auto begin()                          -> iterator;
  auto end()                            -> iterator;
  auto data()                           -> iterator;
  auto front()                          -> const value_type &;
  auto back()                           -> const value_type &;

  auto at(size_type in_index)           -> value_type &;
  auto max_size() const                 -> size_type;
  auto size() const                     -> size_type;
  auto empty() const                    -> bool;
  auto swap(Array &inout_other)         -> void;
  auto fill(value_type const &in_value)  -> void;

  auto operator==(const Array &in_other) const -> bool;

 private:
  value_type *m_arr = nullptr;
  size_type m_size = N + 1;

 private:
  class iterator {
   public:
    value_type *m_pointer;
    explicit iterator(value_type *in_point) : m_pointer(in_point) {}
    value_type &operator*() { return *m_pointer; }
    const value_type &operator*() const { return *m_pointer; }
    bool operator==(iterator const &in_other) {
      return m_pointer == in_other.m_pointer;
    }
    bool operator!=(iterator const &in_other) {
      return m_pointer != in_other.m_pointer;
    }
    iterator &operator--() {
      --m_pointer;
      return *this;
    }
    iterator &operator++() {
      ++m_pointer;
      return *this;
    }
  };
};

template <typename T, size_t N>
Array<T, N>::Array() {
  m_arr = new value_type[m_size];
}

template <typename T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const &in_items) {
  m_arr = new value_type[m_size];
  int count = 0;
  for (auto el : in_items) {
    m_arr[count] = el;
    ++count;
  }
}

template <typename T, size_t N>
Array<T, N>::Array(const Array &in_other) {
  *this = in_other;
}

template <typename T, size_t N>
Array<T, N>::Array(Array &&move_other) {
  *this = move_other;
}

template <typename T, size_t N>
typename Array<T, N>::value_type &Array<T, N>::operator[](size_type in_index) {
  return m_arr[in_index];
}

template <typename T, size_t N>
Array<T, N> &Array<T, N>::operator=(const Array &in_other) {
  T *m_temp = new T[in_other.m_size];
  memcpy(m_temp, in_other.m_arr, m_size * sizeof(T));

  std::swap(this->m_arr, m_temp);
  delete[] m_temp;
  return *this;
}

template <typename T, size_t N>
Array<T, N> &Array<T, N>::operator=(Array &&move_other) {
  swap(move_other);
  return *this;
}

template <typename T, size_t N>
Array<T, N>::~Array() {
  delete[] m_arr;
}

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() {
  if (m_size < 2) {
    throw std::out_of_range("We haven't got begin iterator");
  }
  iterator temp(m_arr);
  return temp;
}

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::end() {
  if (m_size < 2) {
    throw std::out_of_range("We haven't got end iterator");
  }
  iterator temp(m_arr + m_size - 1);
  return temp;
}

template <typename T, size_t N>
const typename Array<T, N>::value_type &Array<T, N>::front() {
  if (m_size < 2) {
    throw std::out_of_range("That index isn't validate!");
  }
  return m_arr[0];
}

template <typename T, size_t N>
const typename Array<T, N>::value_type &Array<T, N>::back() {
  if (m_size < 2) {
    throw std::out_of_range("That index isn't validate!");
  }
  return m_arr[m_size - 2];
}

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::data() {
  return begin();
}

template <typename T, size_t N>
typename Array<T, N>::value_type &Array<T, N>::at(size_type in_index) {
  if (in_index >= (m_size - 2)) {
    throw std::out_of_range("That index isn't validate!");
  }
  return m_arr[in_index];
}

template <typename T, size_t N>
bool Array<T, N>::empty() const {
  return m_size == 1;
}

template <typename T, size_t N>
void Array<T, N>::swap(Array &inout_other) {
  std::swap(m_arr, inout_other.m_arr);
}

template <typename T, size_t N>
void Array<T, N>::fill(value_type const &in_value) {
  for (value_type &element : *this) {
    element = in_value;
  }
}

template <typename T, size_t N>
typename Array<T, N>::size_type Array<T, N>::size() const {
  return m_size - 1;
}

template <typename T, size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size() const {
  return size();
}

template <typename T, size_t N>
bool Array<T, N>::operator==(const Array &in_other) const {
  for (int i = 0; i < static_cast<int>(in_other.size()); ++i) {
    if (this->m_arr[i] != in_other.m_arr[i]) {
      return false;
    }
  }
  return true;
}

}  // namespace victoriv

#endif  // SRC_MY_ARRAY_H_
