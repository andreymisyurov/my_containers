#pragma once

#include <iostream>
#include <limits>

namespace s21 {
template <typename K, typename T>
class Map {
  class Node;

 public:
  typedef K key_type;
  typedef T mapped_type;
  typedef std::pair<const key_type, mapped_type> value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;

  class MapIterator {
   private:
    Map* tree = nullptr;
    Node* cur = nullptr;

   public:
    MapIterator();
    MapIterator(Map<key_type, mapped_type>* tr, Node* c);
    const_reference operator*();
    MapIterator& operator++();
    MapIterator& operator--();
    bool operator==(const MapIterator& other);
    bool operator!=(const MapIterator& other);

    Node* get_current_node();
    MapIterator& parent_lift(bool is_left);
  };

  typedef MapIterator iterator;
  typedef const MapIterator const_iterator;

 public:
  Map();
  explicit Map(std::initializer_list<value_type> const& items);
  Map(const Map& m);
  Map(Map&& m);
  ~Map();
  void operator=(Map&& m);

 public:
  mapped_type& at(const key_type& key);
  mapped_type& operator[](const key_type& key);

 public:
  iterator begin();
  iterator end();

 public:
  bool empty();
  size_type size();
  size_type max_size();

 public:
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);
  void erase(iterator pos);
  void swap(Map& other);
  void merge(Map& other);

 public:
  bool contains(const key_type& key);

 public:
  template <class... Args>
  std::pair<iterator, bool> emplace(Args&&... args);
  void insert(std::initializer_list<value_type> ilist);

 public:
  int deleted(Node* t);
  void print();
  std::pair<iterator, bool> search(Map<key_type, mapped_type>* tree, Node* node,
                                   const key_type& k);
  void copy_tree(Node* t);

 private:
  class Node {
   public:
    value_type data;
    Node *left, *right, *parent;
    int height;

    Node() : data() {
      left = nullptr;
      right = nullptr;
      parent = nullptr;
      height = 0;
    }
    explicit Node(value_type dat) : data(dat) {
      left = nullptr;
      right = nullptr;
      parent = nullptr;
      height = 1;
    }

    std::pair<iterator, bool> add_node(Map<key_type, mapped_type>* tree,
                                       const value_type& value);
    void erase_node(const key_type& key);
    void show(int level);
    void swap(Node* new_, Node* del);
    Node* min_left(Node* elem);
    Node* max_right(Node* elem);

   public:
    Node* balance(Node* node);
    Node* rotate_left(Node* a);
    Node* rotate_right(Node* b);
    void fix_height();
    int balance_criterion();
  };

  size_type size_ = 0;
  Node* root = nullptr;
};

}  // namespace s21

#include "s21_map.inl"
#include "s21_map_add_func.inl"
#include "s21_map_iterator.inl"
