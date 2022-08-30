#pragma once

#include "s21_set.h"

namespace s21 {

template <typename value_type>
class multiset : public set<value_type> {
 public:
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;

 public:
  multiset() : set<value_type>::set() {}
  explicit multiset<value_type>(
      std::initializer_list<value_type> const& items) {
    for (const_reference value : items) {
      insert(value);
    }
  }
  explicit multiset<value_type>(const set<value_type>& other)
      : set<value_type>::set(other) {}
  explicit multiset<value_type>(set<value_type>&& other)
      : set<value_type>::set(other) {}

 public:
  iterator_set<value_type> insert(const_reference key);
  void recurs_insert(const_reference x, Node<value_type>*& piece,
                     Node<value_type>* father);
  void merge(multiset& other);
  iterator_set<value_type> lower_bound(const_reference key);
  iterator_set<value_type> upper_bound(const_reference key);
  std::pair<iterator_set<value_type>, iterator_set<value_type>> equal_range(
      const_reference key);
  size_type count(const_reference key);
  iterator_set<value_type> find_reverso(const_reference key);
  template <typename... Args>
  std::pair<iterator_set<value_type>, bool> emplace(Args&&... args);
};

}  // namespace s21
#include "s21_multiset.inl"
