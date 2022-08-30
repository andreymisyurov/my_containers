#pragma once
using namespace s21;

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::Node*
Map<key_type, mapped_type>::Node::min_left(Node* elem) {
  while (elem->left) {
    elem = elem->left;
  }
  return elem;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::Node*
Map<key_type, mapped_type>::Node::max_right(Node* elem) {
  while (elem->right) {
    elem = elem->right;
  }
  return elem;
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::copy_tree(Node* t) {
  if (!t) return;
  copy_tree(t->left);
  insert(std::make_pair(t->data.first, t->data.second));
  copy_tree(t->right);
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::print() {
  if (size() != 0) {
    this->root->show(0);
  }
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::Node::show(int level) {
  if (this->right) this->right->show(level + 1);

  for (int i = 0; i < 3 * level; i++) std::cout << " ";

  std::cout << this->data.first << "(" << this->data.second << ")\n";

  if (this->left) this->left->show(level + 1);
}

template <typename key_type, typename mapped_type>
int Map<key_type, mapped_type>::deleted(Node* t) {
  if (!t) return 0;
  deleted(t->left);
  deleted(t->right);
  t->parent = nullptr;
  delete t;
  return 0;
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::search(Map<key_type, mapped_type>* tree, Node* node,
                                   const key_type& k) {
  std::pair<iterator, bool> res;
  if (!node) {
    res.second = false;
    return res;
  }
  if (k == node->data.first) {
    iterator it(tree, node);
    res.first = it;
    res.second = true;
    return res;
  }
  if (k < node->data.first) {
    return search(tree, node->left, k);
  } else {
    return search(tree, node->right, k);
  }
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::Node::add_node(Map<key_type, mapped_type>* tree,
                                           const value_type& value) {
  std::pair<iterator, bool> res;
  if (value.first == data.first) {
    iterator it(tree, this);
    res.first = it;
    res.second = false;
    return res;
  }
  if (value.first < data.first) {
    if (left) {
      res = left->add_node(tree, value);
      if (res.second) {
        balance(left);
      }
    } else {
      left = new Node(value);
      left->parent = this;
      iterator it(tree, left);
      res.first = it;
      res.second = true;
    }
  } else {
    if (right) {
      res = right->add_node(tree, value);
      if (res.second) {
        balance(right);
      }
    } else {
      right = new Node(value);
      right->parent = this;
      iterator it(tree, right);
      res.first = it;
      res.second = true;
    }
  }
  return res;
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::Node::erase_node(const key_type& key) {
  Node* temp;
  int is_left;
  if (left && left->data.first == key) {
    is_left = 2;
    temp = left;
  } else if (right && right->data.first == key) {
    is_left = 1;
    temp = right;
  } else {
    is_left = 0;
    temp = nullptr;
  }
  if (is_left != 0) {
    if ((!temp->left && !temp->right) || (temp->left && !temp->right)) {
      if (is_left == 2) {
        left = temp->left;
        if (left) left->parent = this;
      } else {
        right = temp->left;
        if (right) right->parent = this;
      }
      temp->left = nullptr;
      delete temp;
      temp = nullptr;
      return;
    }
    if (is_left == 2) {
      left = left->right;
      left = left->min_left(left);
      left->swap(left, temp);
    } else {
      right = right->right;
      right = right->min_left(right);
      right->swap(right, temp);
    }
    temp->right = nullptr;
    temp->left = nullptr;
    delete temp;
    temp = nullptr;
    return;
  }
  if (key < data.first) {
    if (left) {
      left->erase_node(key);
      balance(left);
    }
  } else {
    if (right) {
      right->erase_node(key);
      balance(right);
    }
  }
  return;
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::Node::swap(Node* new_, Node* del) {
  if (new_->parent->left == new_) {
    new_->parent->left = nullptr;
  }
  if (new_->parent->right != new_) {
    new_->right = del->right;
  }
  new_->left = del->left;
  if (!del->parent) {
    new_->parent = nullptr;
  }
  new_->parent = (!del->parent) ? nullptr : del->parent;
  if (new_->left) new_->left->parent = new_;
  if (new_->right) new_->right->parent = new_;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::Node*
Map<key_type, mapped_type>::Node::balance(
    Map<key_type, mapped_type>::Node* node) {
  if (!node) return node;
  node->fix_height();
  if (node->balance_criterion() == 2) {
    if (node->right->balance_criterion() < 0) {
      rotate_right(node->right);
    }
    return rotate_left(node);
  }
  if (node->balance_criterion() == -2) {
    if (node->left->balance_criterion() > 0) {
      rotate_left(node->left);
    }
    return rotate_right(node);
  }
  return node;
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::Node::fix_height() {
  int left_height = 0, right_height = 0;
  if (left) {
    left_height = left->height;
  }
  if (right) {
    right_height = right->height;
  }
  if (left_height > right_height) {
    height = left_height + 1;
  } else {
    height = right_height + 1;
  }
}

template <typename key_type, typename mapped_type>
int Map<key_type, mapped_type>::Node::balance_criterion() {
  int left_height = 0, right_height = 0;
  if (left) {
    left_height = left->height;
  }
  if (right) {
    right_height = right->height;
  }
  return right_height - left_height;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::Node*
Map<key_type, mapped_type>::Node::rotate_left(Node* a) {
  Node* dad = a->parent;
  bool is_left;
  if (dad) {
    if (dad->left == a) {
      is_left = true;
    } else {
      is_left = false;
    }
  }
  Node* b = a->right;
  a->right = b->left;
  b->left = a;

  b->parent = dad;
  if (dad) {
    if (is_left)
      dad->left = b;
    else
      dad->right = b;
  }
  if (b->right) b->right->parent = b;

  if (b->left) b->left->parent = b;

  if (a->left) a->left->parent = a;

  if (a->right) a->right->parent = a;

  a->fix_height();
  b->fix_height();

  return b;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::Node*
Map<key_type, mapped_type>::Node::rotate_right(Node* b) {
  Node* dad = b->parent;
  bool is_left;
  if (dad) {
    if (dad->left == b)
      is_left = true;
    else
      is_left = false;
  }
  Node* a = b->left;
  b->left = a->right;
  a->right = b;

  a->parent = dad;
  if (dad) {
    if (is_left)
      dad->left = a;
    else
      dad->right = a;
  }
  if (a->left) a->left->parent = a;

  if (a->right) a->right->parent = a;

  if (b->right) b->right->parent = b;

  if (b->left) b->left->parent = b;

  b->fix_height();
  a->fix_height();

  return a;
}
