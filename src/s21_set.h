#pragma once
#include <initializer_list>

namespace s21 {
template <typename value_type>
class Node {
 private:
  value_type value_ = 0;

 public:
  Node* left = nullptr;
  Node* right = nullptr;
  Node* father = nullptr;

 public:
  Node() {}

 public:
  value_type& set_value() { return value_; }
  const value_type& get_value() { return value_; }
};

template <typename value_type>
class iterator_set {
 private:
  Node<value_type>* it_root_ = nullptr;
  Node<value_type>* current_ = nullptr;

 public:
  iterator_set() {}
  explicit iterator_set(Node<value_type>* item)
      : current_(item), it_root_(item) {}
  Node<value_type>* find_min(Node<value_type>* const piece);
  Node<value_type>* find_max(Node<value_type>* const piece);

 public:
  Node<value_type>* getter() const { return current_; }
  Node<value_type>*& setter() { return current_; }

 public:
  iterator_set operator=(iterator_set other) {
    current_ = other.current_;
    return *this;
  }
  value_type& operator*() {
    return current_ == nullptr ? find_max(it_root_)->set_value()
                               : current_->set_value();
  }
  bool operator!=(const iterator_set& other) {
    return current_ != other.current_;
  }
  bool operator==(const iterator_set& other) {
    return current_ == other.current_;
  }
  bool operator>(const iterator_set& other) {
    return current_->value_ > other.current_->value_;
  }
  bool operator<(const iterator_set& other) {
    return current_->value_ < other.current_->value_;
  }
  bool operator>=(const iterator_set& other) {
    return current_->value_ >= other.current_->value_;
  }
  bool operator<=(const iterator_set& other) {
    return current_->value_ <= other.current_->value_;
  }

  Node<value_type>* operator++() {
    if (current_ != nullptr) {
      if (current_->right != nullptr) {
        current_ = find_min(current_->right);
      } else if (current_->father == nullptr) {
        current_ = nullptr;
      } else {
        if (current_ == current_->father->left) {
          current_ = current_->father;
        } else if (current_ == current_->father->right) {
          while ((current_->father != nullptr) &&
                 (current_ != current_->father->left)) {
            current_ = current_->father;
          }
          current_ = current_->father;
        }
      }
    }
    return current_;
  }

  Node<value_type>* operator--() {
    if (current_ != find_min(it_root_)) {
      if (current_ == nullptr) {
        current_ = find_max(it_root_);
      } else if (current_->left != nullptr) {
        current_ = find_max(current_->left);
      } else if (current_->father == nullptr) {
        current_ = nullptr;
      } else {
        if (current_ == current_->father->right) {
          current_ = current_->father;
        } else if (current_ == current_->father->left) {
          while ((current_->father != nullptr) &&
                 (current_ != current_->father->right)) {
            current_ = current_->father;
          }
          current_ = current_->father;
        }
      }
    }
    return current_;
  }
};

template <typename value_type>
class set {
 public:
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;

 protected:
  size_type size_ = 0;

 public:
  Node<value_type>* root_ = nullptr;
  set<value_type>();
  explicit set<value_type>(std::initializer_list<value_type> const& items);
  set<value_type>(const set<value_type>& other);
  set<value_type>(set<value_type>&& other);
  set<value_type> operator=(const set<value_type>& other);
  set<value_type> operator=(set<value_type>&& other);
  ~set<value_type>();

 public:
  std::pair<iterator_set<value_type>, bool> insert(const_reference x);
  void erase(iterator_set<value_type> value);
  void merge(set<value_type>& other);
  void swap(set<value_type>& other) noexcept;
  iterator_set<value_type> find(const_reference key);
  void clear();
  bool contains(const_reference key);
  template <typename... Args>
  std::pair<iterator_set<value_type>, bool> emplace(Args&&... args);

 public:
  iterator_set<value_type> begin();
  iterator_set<value_type> end();
  iterator_set<value_type> end_element();
  bool empty();
  size_type max_size();
  size_type size();

 protected:
  void recurs_insert(const_reference x, Node<value_type>*& piece,
                     Node<value_type>* father, bool& flag);
  void copy_travers(Node<value_type>* const data);
  void contains_travers(Node<value_type>* data, bool& flag,
                        const_reference value);
  void DestroyNode(Node<value_type>*& node);
};

}  // namespace s21
#include "s21_set.inl"
