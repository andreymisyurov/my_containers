#pragma once

#include <cstring>
#include <initializer_list>

namespace s21 {

template <typename T>
class vector {
 public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef const T *const_iterator;
  typedef size_t size_type;

 private:
  class iterator {
   public:
    value_type *my_item_;

   public:
    void setIterator(value_type *item_) { my_item_ = item_; }

   public:
    reference operator*() { return *my_item_; }
    const_reference operator*() const { return *(my_item_); }
    value_type *operator++() {
      ++my_item_;
      return my_item_;
    }
    value_type *operator--() {
      --my_item_;
      return my_item_;
    }
    bool operator==(iterator const other) { return my_item_ == other.my_item_; }
    bool operator!=(iterator const other) { return my_item_ != other.my_item_; }
    bool operator>(iterator const other) {
      return (my_item_ - other.my_item_) > 0;
    }
    bool operator>=(iterator const other) {
      return (my_item_ - other.my_item_) >= 0;
    }
    bool operator<(iterator const other) {
      return (my_item_ - other.my_item_) < 0;
    }
    bool operator<=(iterator const other) {
      return (my_item_ - other.my_item_) <= 0;
    }
  };

 private:
  value_type *item_ = nullptr;
  size_type count_ = 0;
  size_type cap_ = 0;
  iterator it_begin_;
  iterator it_end_;

 public:
  vector();
  explicit vector(size_type const size);
  explicit vector(std::initializer_list<value_type> const &items);
  vector(const vector &other);
  vector(vector &&other);
  ~vector();

 public:
  vector<value_type> &operator=(const vector &other);
  vector<value_type> &operator=(vector &&other);
  reference operator[](size_type const pos) { return (item_)[pos]; }

 public:
  reference at(size_type const pos);
  const_reference front();
  const_reference back();
  value_type *data() { return item_; }
  iterator begin() const { return it_begin_; }
  iterator end() const { return it_end_; }

 public:
  iterator insert(iterator pos, const_reference value);
  void clear();
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector<value_type> &other) noexcept;
  template <typename... Args>
  iterator emplace(const iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);

 public:
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type const size);
  size_type capacity();
  void shrink_to_fit();

 public:
  void check_fillness();
};
}  // namespace s21

#include "s21_vector.inl"
