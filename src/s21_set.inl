#pragma once
using namespace s21;

template <typename value_type>
set<value_type>::set(){};

template <typename value_type>
set<value_type>::set(std::initializer_list<value_type> const& items) {
  for (const_reference value_ : items) {
    insert(value_);
  }
};

template <typename value_type>
set<value_type>::set(const set<value_type>& other) {
  size_ = 0;
  copy_travers(other.root_);
}

template <typename value_type>
set<value_type>::set(set<value_type>&& other) {
  std::swap(size_, other.size_);
  std::swap(root_, other.root_);
}

template <typename value_type>
set<value_type>::~set() {
  DestroyNode(root_);
}

template <typename value_type>
set<value_type> set<value_type>::operator=(const set<value_type>& other) {
  if (this->root_ != other.root_) {
    size_ = 0;
    copy_travers(other.root_);
  }
  return *this;
}

template <typename value_type>
set<value_type> set<value_type>::operator=(set<value_type>&& other) {
  if (this->root_ != other.root_) {
    std::swap(size_, other.size_);
    std::swap(root_, other.root_);
  }
  return *this;
}

template <typename value_type>
void set<value_type>::erase(iterator_set<value_type> value) {
  if (value.getter()) {
    Node<value_type>* curr = value.getter();
    Node<value_type>* parent = value.getter()->father;
    if (curr->left == nullptr) {
      if (parent && parent->left == curr) {
        parent->left = curr->right;
        if (curr->right != nullptr) curr->right->father = parent;
      }
      if (parent && parent->right == curr) {
        parent->right = curr->right;
        if (curr->right != nullptr) curr->right->father = parent;
      }
      if ((parent == nullptr) && (curr == root_)) {
        root_ = curr->right;
        if (curr->right != nullptr) curr->right->father = nullptr;
      }
      --size_;
      curr->right = curr->left = nullptr;
      delete curr;
    } else if (curr->right == nullptr) {
      if (parent && parent->left == curr) {
        parent->left = curr->left;
        curr->left->father = parent;
      }
      if (parent && parent->right == curr) {
        parent->right = curr->left;
        curr->left->father = parent;
      }
      --size_;
      if ((parent == nullptr) && (curr == root_)) {
        root_ = curr->left;
        curr->left->father = nullptr;
      }
      curr->right = curr->left = nullptr;
      delete curr;
    } else {
      Node<value_type>* replace = curr->right;
      while (replace->left) {
        replace = replace->left;
      }
      value_type change_value = replace->get_value();
      erase(iterator_set<value_type>(replace));
      curr->set_value() = change_value;
    }
  }
}

template <typename value_type>
void set<value_type>::merge(set<value_type>& other) {
  if (this->root_ != other.root_) {
    for (auto beg = other.begin(), endl = other.end(); beg != endl;) {
      std::pair<iterator_set<value_type>, bool> temp = this->insert(*beg);
      if (temp.second) {
        auto del = beg;
        if (beg != other.begin()) {
          --beg;
          other.erase(del);
        } else {
          other.erase(del);
          beg.setter() = beg.find_min(other.root_);
          continue;
        }
      }
      ++beg;
    }
  }
}

template <typename value_type>
void set<value_type>::swap(set<value_type>& other) noexcept {
  if (this->root_ != other.root_) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }
}

template <typename value_type>
std::pair<iterator_set<value_type>, bool> set<value_type>::insert(
    const_reference x) {
  if ((size() + 1) > max_size()) {
    throw std::range_error("exceeded max size");
  }
  std::pair<iterator_set<value_type>, bool> result{nullptr, true};
  recurs_insert(x, root_, nullptr, result.second);
  if (result.second) {
    ++size_;
    result.first = find(x);
  } else {
    result.first.setter() = nullptr;
  }
  return result;
}

template <typename value_type>
void set<value_type>::recurs_insert(const_reference x, Node<value_type>*& piece,
                                    Node<value_type>* father, bool& flag) {
  if (piece == nullptr) {
    piece = new Node<value_type>;
    piece->set_value() = x;
    piece->father = father;
  } else if (x < piece->set_value()) {
    recurs_insert(x, piece->left, piece, flag);
  } else if (x > piece->set_value()) {
    recurs_insert(x, piece->right, piece, flag);
  } else {
    flag = false;
  }
}

template <typename value_type>
iterator_set<value_type> set<value_type>::begin() {
  iterator_set<value_type> needle(root_);
  if (root_ != nullptr) {
    while (needle.getter()->left != nullptr) {
      needle.setter() = needle.getter()->left;
    }
  }
  return needle;
}

template <typename value_type>
iterator_set<value_type> set<value_type>::end() {
  iterator_set<value_type> needle(root_);
  if (root_ != nullptr) {
    while (needle.getter() != nullptr) {
      needle.setter() = needle.getter()->right;
    }
  }
  return needle;
}

template <typename value_type>
iterator_set<value_type> set<value_type>::end_element() {
  iterator_set<value_type> needle(root_);
  while (needle.getter()->right != nullptr) {
    needle.setter() = needle.getter()->right;
  }
  return needle;
}

template <typename value_type>
void set<value_type>::clear() {
  DestroyNode(root_);
  size_ = 0;
}

template <typename value_type>
bool set<value_type>::contains(const_reference key) {
  bool result = false;
  contains_travers(root_, result, key);
  return result;
}

template <typename value_type>
void set<value_type>::contains_travers(Node<value_type>* data, bool& flag,
                                       const_reference value) {
  if (data == NULL) return;
  contains_travers(data->left, flag, value);
  if (value == data->get_value()) {
    flag = true;
  }
  contains_travers(data->right, flag, value);
}

template <typename value_type>
iterator_set<value_type> set<value_type>::find(const_reference key) {
  iterator_set<value_type> result;
  result.setter() = nullptr;
  auto beg = begin();
  auto endl = end();
  bool breaker = false;
  for (; beg != endl && !breaker; ++beg) {
    if (*beg == key) {
      result = beg;
      breaker = true;
    }
  }
  return result;
}

template <typename value_type>
template <typename... Args>
std::pair<iterator_set<value_type>, bool> set<value_type>::emplace(
    Args&&... args) {
  value_type storage[] = {args...};
  std::pair<iterator_set<value_type>, bool> result{nullptr, true};
  for (value_type& elem : storage) {
    result = insert(elem);
    if (!result.second) {
      result.first = find(elem);
    }
  }
  return result;
}

template <typename value_type>
bool set<value_type>::empty() {
  return root_ == nullptr;
}

template <typename value_type>
size_t set<value_type>::max_size() {
  auto maximum = 2097152;
  return maximum / sizeof(value_type);
}

template <typename value_type>
size_t set<value_type>::size() {
  return size_;
}

template <typename value_type>
Node<value_type>* iterator_set<value_type>::find_min(
    Node<value_type>* const piece) {
  Node<value_type>* result = piece;
  if (piece != nullptr) {
    if (piece->left != nullptr) {
      result = find_min(piece->left);
    }
  }
  return result;
}

template <typename value_type>
Node<value_type>* iterator_set<value_type>::find_max(
    Node<value_type>* const piece) {
  Node<value_type>* result = piece;
  if (piece != nullptr) {
    if (piece->right != nullptr) {
      result = find_max(piece->right);
    }
  }
  return result;
}

template <typename value_type>
void set<value_type>::copy_travers(Node<value_type>* const data) {
  if (data == NULL) return;
  copy_travers(data->left);
  insert(data->get_value());
  copy_travers(data->right);
}

template <typename value_type>
void set<value_type>::DestroyNode(Node<value_type>*& node) {
  if (node != nullptr) {
    DestroyNode(node->left);
    DestroyNode(node->right);
    delete node;
    node = nullptr;
  }
}
