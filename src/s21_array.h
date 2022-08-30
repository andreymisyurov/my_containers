#pragma once
#include <initializer_list>
#include <ostream>

namespace s21 {

template <typename T, size_t N>
class Array {
 public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef const T *const_iterator;
  typedef size_t size_type;

 private:
  class iterator {
   private:
    value_type *pointer_;

   public:
    explicit iterator(value_type *point) : pointer_(point) {}

   public:
    value_type &operator*() { return *pointer_; }
    const value_type &operator*() const { return *pointer_; }
    bool operator==(iterator const &other) {
      return pointer_ == other.pointer_;
    }
    bool operator!=(iterator const &other) {
      return pointer_ != other.pointer_;
    }
    iterator &operator--() {
      --pointer_;
      return *this;
    }
    iterator &operator++() {
      ++pointer_;
      return *this;
    }
  };
  value_type *arr_ = nullptr;
  size_type size_ = N + 1;

 public:
  Array();
  explicit Array(std::initializer_list<value_type> const &items);
  Array(const Array &other);
  Array(Array &&other);
  ~Array();

 public:
  value_type &operator[](size_type const &index);
  void operator=(const Array &other);
  void operator=(Array &&other);

 public:
  iterator begin();
  iterator end();
  iterator data();
  const value_type &front();
  const value_type &back();

 public:
  value_type &at(size_type const &index);
  size_type size();
  size_type max_size();
  bool empty();
  void swap(Array &other);
  void fill(value_type const &value);
};

}  // namespace s21

#include "s21_array.inl"
