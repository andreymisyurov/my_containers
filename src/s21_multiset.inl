#pragma once
using namespace s21;

template <typename value_type>
void multiset<value_type>::merge(multiset<value_type>& other) {
  for (auto beg = other.begin(), endl = other.end(); beg != endl; ++beg) {
    insert(*beg);
  }
  other.clear();
}

template <typename value_type>
iterator_set<value_type> multiset<value_type>::insert(const_reference key) {
  iterator_set<value_type> result;
  result.setter() = nullptr;
  recurs_insert(key, this->root_, nullptr);
  ++(this->size_);
  result = this->find(key);
  return result;
}

template <typename value_type>
void multiset<value_type>::recurs_insert(const_reference key,
                                         Node<value_type>*& piece,
                                         Node<value_type>* father) {
  if (piece == nullptr) {
    piece = new Node<value_type>;
    piece->set_value() = key;
    piece->father = father;
  } else if (key <= piece->get_value()) {
    recurs_insert(key, piece->left, piece);
  } else {
    recurs_insert(key, piece->right, piece);
  }
}

template <typename value_type>
std::pair<iterator_set<value_type>, iterator_set<value_type>>
multiset<value_type>::equal_range(const value_type& key) {
  std::pair<iterator_set<value_type>, iterator_set<value_type>> result{
      lower_bound(key), upper_bound(key)};
  return result;
}

template <typename value_type>
iterator_set<value_type> multiset<value_type>::lower_bound(
    const_reference key) {
  return this->find(key);
}

template <typename value_type>
iterator_set<value_type> multiset<value_type>::upper_bound(
    const_reference key) {
  return find_reverso(key);
}

template <typename value_type>
size_t multiset<value_type>::count(const_reference key) {
  size_t counter = 0;
  auto a = lower_bound(key);
  if (a.getter() != nullptr) {
    ++counter;
  }
  auto b = upper_bound(key);
  for (; a != b; ++a) {
    ++counter;
  }
  return counter;
}

template <typename value_type>
iterator_set<value_type> multiset<value_type>::find_reverso(
    const_reference key) {
  iterator_set<value_type> result;
  result.setter() = nullptr;
  if (this->root_ != nullptr) {
    auto beg = this->begin();
    auto endl = this->end();
    bool breaker = true;
    while (breaker) {
      if (*endl == key) {
        result = endl;
        breaker = false;
      }
      if (beg == endl) {
        breaker = false;
      }
      --endl;
    }
  }
  return result;
}

template <typename value_type>
template <typename... Args>
std::pair<iterator_set<value_type>, bool> multiset<value_type>::emplace(
    Args&&... args) {
  value_type storage[] = {args...};
  std::pair<iterator_set<value_type>, bool> result{nullptr, true};
  result.second = true;
  for (value_type& elem : storage) {
    result.first = insert(elem);
  }
  return result;
}