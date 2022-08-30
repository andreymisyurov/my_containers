#pragma once
using namespace s21;

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map() {
  size_ = 0;
  root = nullptr;
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map(const Map& m) : Map() {
  copy_tree(m.root);
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map(std::initializer_list<value_type> const& items)
    : Map() {
  for (const value_type& item : items) {
    insert(item);
  }
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map(Map&& m) : Map() {
  std::swap(size_, m.size_);
  std::swap(root, m.root);
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::~Map() {
  clear();
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::clear() {
  if (root) {
    deleted(root);
  }
  size_ = 0;
  root = nullptr;
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::operator=(Map&& m) {
  if (root != m.root) {
    std::swap(size_, m.size_);
    std::swap(root, m.root);
  }
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::mapped_type&
Map<key_type, mapped_type>::at(const key_type& key) {
  std::pair<iterator, bool> res = search(this, root, key);
  if (res.first == end())
    throw std::out_of_range("There is no such key in the map!");
  return (res.first.get_current_node())->data.second;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::mapped_type&
Map<key_type, mapped_type>::operator[](const key_type& key) {
  std::pair<iterator, bool> res = search(this, root, key);
  if (!res.second) {
    res = insert(key, mapped_type());
  }
  return (res.first.get_current_node())->data.second;
}

template <typename key_type, typename mapped_type>
bool Map<key_type, mapped_type>::empty() {
  return (root == nullptr);
}

template <typename key_type, typename mapped_type>
bool Map<key_type, mapped_type>::contains(const key_type& key) {
  return (search(this, root, key)).second;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::size_type
Map<key_type, mapped_type>::size() {
  return size_;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::size_type
Map<key_type, mapped_type>::max_size() {
  size_type max_size =
      (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
  return max_size;
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert(const value_type& value) {
  if ((size() + 1) > max_size()) throw std::out_of_range("Limit is exceeded");
  std::pair<iterator, bool> res;
  if (!root) {
    root = new Node(value);
    size_++;
    iterator it(this, root);
    res.first = it;
    res.second = true;
  } else {
    res = root->add_node(this, value);
    if (res.second) {
      root = root->balance(root);
      size_++;
    }
  }
  return res;
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert(const key_type& key,
                                   const mapped_type& obj) {
  return insert(std::make_pair(key, obj));
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
  std::pair<iterator, bool> res;
  res = search(this, root, key);
  if (res.second) {
    res.first.get_current_node()->data.second = obj;
    res.second = false;
    return res;
  } else {
    return insert(std::make_pair(key, obj));
  }
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::erase(iterator pos) {
  if (!root) return;
  Node* temp;
  if ((pos.get_current_node())->data.first == root->data.first) {
    temp = root;
    if ((!temp->left && !temp->right) || (temp->left && !temp->right)) {
      root = temp->left;
      if (root) root->parent = nullptr;

      temp->left = nullptr;
      delete temp;
      temp = nullptr;
      size_--;
      Node r;
      root = r.balance(root);
      return;
    }
    root = temp->right;
    root = root->min_left(root);
    root->swap(root, temp);
    temp->right = nullptr;
    temp->left = nullptr;
    delete temp;
    temp = nullptr;
    size_--;
    root = root->balance(root);
    return;
  }
  root->erase_node((pos.get_current_node())->data.first);
  root = root->balance(root);
  size_--;
  return;
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::swap(Map& other) {
  if (this != &other) {
    std::swap(root, other.root);
    std::swap(size_, other.size_);
  }
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::merge(Map& other) {
  if (this->root != other.root) {
    for (auto beg = other.begin(), endl = other.end(); beg != endl;) {
      std::pair<iterator, bool> temp =
          insert((beg.get_current_node())->data.first,
                 (beg.get_current_node())->data.second);
      if (temp.second) {
        auto del = beg;
        if (beg != other.begin()) {
          --beg;
          other.erase(del);
        } else {
          other.erase(del);
          beg = other.begin();
          continue;
        }
      }
      ++beg;
    }
  }
}

template <typename key_type, typename mapped_type>
template <class... Args>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::emplace(Args&&... args) {
  std::pair<key_type, mapped_type> storage[] = {args...};
  std::pair<iterator, bool> result;
  for (std::pair<key_type, mapped_type>& elem : storage) {
    result = insert(elem.first, elem.second);
    if (!result.second) {
      result = search(this, root, elem.first);
      result.second = false;
    }
  }
  return result;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::iterator
Map<key_type, mapped_type>::begin() {
  Node* elem = root;
  if (!elem) {
    MapIterator iter(this, elem);
    return iter;
  }
  elem = elem->min_left(elem);
  MapIterator iter(this, elem);
  return iter;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::iterator
Map<key_type, mapped_type>::end() {
  Node* elem = root;
  if (!elem) {
    MapIterator iter(this, elem);
    return iter;
  }
  elem = elem->max_right(elem);
  MapIterator iter(this, elem->right);
  return iter;
}
