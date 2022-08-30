#pragma once
using namespace s21;

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::MapIterator::MapIterator() {
  cur = nullptr;
  tree = nullptr;
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::MapIterator::MapIterator(
    Map<key_type, mapped_type>* tr, Node* c) {
  cur = c;
  tree = tr;
}

template <typename key_type, typename mapped_type>
bool Map<key_type, mapped_type>::MapIterator::operator==(
    const MapIterator& other) {
  return (cur == other.cur);
}

template <typename key_type, typename mapped_type>
bool Map<key_type, mapped_type>::MapIterator::operator!=(
    const MapIterator& other) {
  return (cur != other.cur);
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::MapIterator&
Map<key_type, mapped_type>::MapIterator::operator++() {
  if (cur == nullptr) {
    throw std::out_of_range("\nThe end of the iterator is reached\n");
  }
  if (cur->right) {
    cur = cur->right;
    cur = cur->min_left(cur);
  } else {
    return parent_lift(1);
  }
  return *this;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::MapIterator&
Map<key_type, mapped_type>::MapIterator::operator--() {
  if (cur) {
    if (cur->left) {
      cur = cur->left;
      cur = cur->max_right(cur);
    } else {
      return parent_lift(0);
    }
  } else {
    cur = tree->root->max_right(tree->root);
  }
  return *this;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::const_reference
Map<key_type, mapped_type>::MapIterator::operator*() {
  if (cur == nullptr) {
    throw std::out_of_range("\nThe iterator limit has been reached\n");
  }
  return cur->data;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::Node*
Map<key_type, mapped_type>::MapIterator::get_current_node() {
  return cur;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::MapIterator&
Map<key_type, mapped_type>::MapIterator::parent_lift(bool is_left) {
  while (1) {
    if (!cur->parent) {
      cur = nullptr;
      return *this;
    }
    if (is_left) {
      if (cur->parent->left == cur) {
        cur = cur->parent;
        return *this;
      }
    } else {
      if (cur->parent->right == cur) {
        cur = cur->parent;
        return *this;
      }
    }
    cur = cur->parent;
  }
}
