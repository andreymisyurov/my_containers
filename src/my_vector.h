#ifndef SRC_MY_VECTOR_H_
#define SRC_MY_VECTOR_H_

#include <cstring>
#include <initializer_list>

namespace victoriv {

constexpr size_t k_START_SIZE = 100;

template <typename T>
class vector {
  class iterator;

 public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef const T *const_iterator;
  typedef size_t size_type;

 public:
  vector();
  explicit vector(size_type in_size);
  explicit vector(std::initializer_list<value_type> const &in_items);
  vector(const vector &in_other);
  vector(vector &&move_other);
  ~vector();

  auto shrink_to_fit()                                       -> void;
  auto reserve(size_type const size)                        -> void;
  auto clear()                                              -> void;
  auto swap(vector<value_type> &inout_other) noexcept       -> void;
  auto erase(iterator inout_pos)                            -> void;
  auto pop_back()                                           -> void;
  auto push_back(const_reference in_value)                  -> void;
  auto insert(iterator in_pos, const_reference in_value)    -> iterator;
  auto begin() const                                        -> iterator;
  auto end() const                                          -> iterator;
  auto size() const                                         -> size_type;
  auto max_size() const                                     -> size_type;
  auto capacity() const                                     -> size_type;
  auto front() const                                        -> const_reference;
  auto back() const                                         -> const_reference;
  auto at(size_type in_pos)                                 -> reference;
  auto data()                                               -> value_type *;
  auto empty() const                                        -> bool;

  template <typename... Args>
  auto emplace(const iterator in_pos, Args &&...move_args)  -> iterator;
  template <typename... Args>
  auto emplace_back(Args &&...move_args)                    -> void;

  auto operator==(const vector &in_other) const             -> bool;
  auto operator=(const vector &in_other)                    -> vector<value_type> &;
  auto operator=(vector &&move_other)                       -> vector<value_type> &;
  auto operator[](size_type in_pos)                         -> reference;

 private:
  auto check_fullness()                                     -> void;

  value_type *m_item = nullptr;
  size_type m_count = 0;
  size_type m_cap = 0;
  iterator m_it_begin{};
  iterator m_it_end{};

 private:
  class iterator {
   public:
    value_type *it_item;

    void setIterator(value_type *m_item) { it_item = m_item; }
    reference operator*() { return *it_item; }
    const_reference operator*() const { return *(it_item); }
    value_type *operator++() { return ++it_item; }
    value_type *operator--() { return --it_item; }
    bool operator==(iterator const other) { return it_item == other.it_item; }
    bool operator!=(iterator const other) { return it_item != other.it_item; }
    bool operator>(iterator const other) { return (it_item - other.it_item) > 0; }
    bool operator>=(iterator const other) { return (it_item - other.it_item) >= 0; }
    bool operator<(iterator const other) { return (it_item - other.it_item) < 0; }
    bool operator<=(iterator const other) { return (it_item - other.it_item) <= 0; }
  };
};

template <typename value_type>
vector<value_type>::vector() {
  m_cap = k_START_SIZE;
  m_item = new value_type[m_cap];
  m_it_begin.setIterator(m_item);
  m_it_end.setIterator(m_item);
}

template <typename value_type>
vector<value_type>::vector(size_type in_size) {
  if (in_size < 1)
    throw std::runtime_error("your vector can't create, because size < 1");
  m_cap = in_size;
  m_item = new value_type[m_cap];
  m_it_begin.setIterator(m_item);
  m_it_end.setIterator(m_item);
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &in_items) {
  m_count = 0;
  m_cap = in_items.size() * 2;
  m_item = new value_type[m_cap];
  m_it_begin.setIterator(m_item);
  for (value_type temp : in_items) push_back(temp);
  m_it_end.setIterator(m_item + in_items.size());
}

template <typename value_type>
vector<value_type>::vector(const vector &in_other) {
  *this = in_other;
}

template <typename value_type>
vector<value_type>::vector(vector &&move_other) {
  *this = move_other;
}

template <typename value_type>
vector<value_type>::~vector() {
  delete[] m_item;
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(const vector &in_other) {
  vector<value_type> temp(in_other.m_cap);
  for (auto &&el : in_other) temp.push_back(el);

  this->swap(temp);
  return *this;
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(vector &&move_other) {
  if (this != &move_other) {
    std::swap(m_item, move_other.m_item);
    std::swap(m_count, move_other.m_count);
    std::swap(m_cap, move_other.m_cap);
    std::swap(m_it_begin, move_other.m_it_begin);
    std::swap(m_it_end, move_other.m_it_end);
  }
  return *this;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](size_type in_pos) {
  return (m_item)[in_pos];
}

template <typename value_type>
bool vector<value_type>::operator==(const vector &in_other) const {
  if (m_count != in_other.m_count) return false;
  for (int i = 0; i < static_cast<int>(m_count); ++i)
    if (m_item[i] != in_other.m_item[i]) return false;
  return true;
}

template <typename value_type>
void vector<value_type>::clear() {
  memset(m_item, 0, sizeof(value_type) * m_count);
  m_count = 0;
}

template <typename value_type>
void vector<value_type>::push_back(const value_type &in_value) {
  if ((m_count + 1) > max_size()) throw std::runtime_error("exceeded max size");
  check_fullness();
  m_item[++m_count - 1] = in_value;
  ++m_it_end;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  m_item[--m_count] = 0;
  --m_it_end;
}

template <typename value_type>
void vector<value_type>::check_fullness() {
  if (capacity() < 3) {
    value_type *trash = m_item;
    value_type *new_arr = new value_type[m_cap * 2];
    std::memcpy(new_arr, trash, m_count * sizeof(value_type));

    std::swap(m_item, new_arr);
    m_cap *= 2;
    delete[] trash;
  }
}

template <typename value_type>
void vector<value_type>::swap(vector<value_type> &inout_other) noexcept {
  std::swap(m_item, inout_other.m_item);
  std::swap(m_count, inout_other.m_count);
  std::swap(m_cap, inout_other.m_cap);
}

template <typename value_type>
void vector<value_type>::reserve(size_t size) {
  if (size > m_cap) {
    vector<value_type> temp(size);
    m_cap = size;
    memcpy(temp.m_item, m_item, sizeof(value_type) * m_count);

    std::swap(m_item, temp.m_item);
  }
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  vector<value_type> temp(m_count);
  m_cap = m_count;
  memcpy(temp.m_item, m_item, m_count * sizeof(value_type));

  std::swap(m_item, temp.m_item);
}

template <typename value_type>
value_type &vector<value_type>::at(size_t in_pos) {
  if (in_pos > m_count - 1) throw std::range_error("you haven't got this index");
  return m_item[in_pos];
}

template <typename value_type>
const value_type &vector<value_type>::front() const {
  if (empty()) throw std::runtime_error("vector is empty");
  return m_item[0];
}

template <typename value_type>
const value_type &vector<value_type>::back() const {
  if (m_count == 0) throw std::runtime_error("vector is empty");
  return (m_item)[m_count - 1];
}

template <typename value_type>
void vector<value_type>::erase(iterator inout_pos) {
  if (inout_pos >= m_it_end || inout_pos < m_it_begin) {
    throw std::runtime_error("your vector said \"segmentation fault\" to your erase\n");
  }
  value_type *temp = m_item;
  for (auto iter = m_it_begin; iter != m_it_end; ++iter) {
    if (iter != inout_pos) {
      *temp = *iter;
      ++temp;
    }
  }
  --m_count;
  --m_it_end;
  *m_it_end = 0;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator in_pos, const value_type &in_value) {
  if ((m_count + 1) > max_size()) throw std::range_error("exceeded max size");
  iterator temp = m_it_end;
  if ((in_pos > m_it_end) || (in_pos < m_it_begin))
    throw std::runtime_error("your vector said \"segmentation fault\" to your insert\n");
  if (in_pos == temp) {
    *temp = in_value;
  } else {
    iterator needle = m_it_end;
    --needle;
    for (; needle >= in_pos; --needle, --temp) {
      if (needle > in_pos) {
        *temp = *needle;
      } else {
        *temp = *needle;
        *needle = in_value;
      }
    }
  }
  ++m_count;
  ++m_it_end;
  return temp;
}

template <typename value_type>
template <class... Args>
typename vector<value_type>::iterator vector<value_type>::emplace(const iterator in_pos, Args &&...in_args) {
  value_type storage[] = {in_args...};
  auto current = in_pos;
  for (value_type &elem : storage) {
    insert(current, elem);
    ++current;
  }
  return in_pos;
}

template <typename value_type>
template <class... Args>
void vector<value_type>::emplace_back(Args &&...in_args) {
  value_type storage[] = {in_args...};
  for (value_type &elem : storage) push_back(elem);
}

template <typename value_type>
bool vector<value_type>::empty() const {
  return !m_count;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() const {
  return m_count;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() const {
  size_type result = size_t(std::numeric_limits<int64_t>::max() / sizeof(value_type));
  return result;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() const {
  return m_cap;
}

template <typename value_type>
typename vector<value_type>::value_type *vector<value_type>::data() {
  return m_item;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() const {
  return m_it_begin;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() const {
  return m_it_end;
}

}  // namespace victoriv

#endif  // SRC_MY_VECTOR_H_
