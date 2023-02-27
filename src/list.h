#pragma once

#include <__nullptr>
#include <initializer_list>
#include <ostream>

// конструкторы
// нода
// итераторы
// основные функции

template <typename T>
class List {
 public:
  typedef T value_type;
  typedef size_t size_type;
  typedef T &reference;
  typedef const T &const_reference;

 private:
  class Node {
   public:
    value_type n_item_;
    Node *n_prev_;
    Node *n_next_;
    Node() : n_next_(nullptr){};
    explicit Node(value_type item, Node *prev, Node *next)
        : n_item_(item), n_prev_(prev), n_next_(next) {}
  };
  Node *m_head_;
  Node *m_tail_;
  Node *m_last_;
  size_t m_size_;

 public:
  class Iterator {
   public:
    Iterator(Node *value) : i_data_(value){};
    Iterator &operator++() {
      i_data_ = i_data_->n_next_;
      return *this;
    }
    Iterator &operator--() {
      i_data_ = i_data_->n_prev_;
      return *this;
    }

    bool operator!=(const Iterator &other) { return i_data_ != other.i_data_; }

    const_reference operator*() {
      if (i_data_->n_next_ == nullptr) {
        auto result = i_data_->n_prev_;
        return result->n_item_;
      }
      return i_data_->n_item_;
    }

   private:
    Node *i_data_;
  };

 public:
  List();                                                // +
  List(size_type n);                                     // +
  List(std::initializer_list<value_type> const &items);  // +
  List(const List &other);                               // +
  List(List &&other);                                    // +
  ~List();                                               // + починить
  List<value_type> &operator=(const List &other);        // +
  List<value_type> &operator=(List &&other);             // +

 public:
  size_type getSize() const { return m_size_; }         // +
  Iterator end() const { return Iterator(m_last_); }    // +
  Iterator begin() const { return Iterator(m_head_); }  // +
  const_reference top() { return m_head_->n_item_; }    // +
  const_reference back() { return m_tail_->n_item_; }   // +
  void clear();                                         // +
  void push_back(value_type value);                     // +
  void push_front(value_type value);                    // +
  void pop_front();                                     // +
  void pop_back();                                      // +
  void sort();
  void unique();
  void reverse();
  void splice(const Iterator pos, List &other);
  void merge(List &other);
  void swap(List &other);
  void erase(Iterator pos);
  Iterator insert(Iterator pos, const_reference value);
};

#include "list.inl"