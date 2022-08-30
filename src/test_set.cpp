#include <gtest/gtest.h>

#include "s21_set.h"

TEST(constr, defo) {
  set<int> test1;
  set<double> test2;
  set<std::string> test3;
}

TEST(constr, init_list) {
  set<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  set<double> test2{1.2, 2.2, 3.2, 4.2};
  set<char> test3{12, 122, 34, 4};
}

TEST(constr, copy) {
  set<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  set<int> test2(test1);
}

TEST(constr, move) {
  set<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  set<int> test2(std::move(test1));
}

TEST(overload, eq_copy) {
  set<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  set<int> test2;
  test2 = test1;
}

TEST(overload, eq_move) {
  set<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  set<int> test2;
  test2 = std::move(test1);
}

TEST(overload, star) {
  set<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTEST_ASSERT_EQ(*test1.begin(), 1);
}

TEST(overload, iter_plusplus_1) {
  set<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto iter = test1.begin();
  ++iter;
  GTEST_ASSERT_EQ(*iter, 2);
}

TEST(overload, iter_plusplus_2) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto iter = test1.begin();
  ++iter;
  ++iter;
  ++iter;
  GTEST_ASSERT_EQ(*iter, 8);
}

TEST(overload, iter_plusplus_3) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto iter = test1.end();
  --iter;
  GTEST_ASSERT_EQ(*iter, 15);
}

TEST(overload, iter_plusplus_4) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto iter = test1.end();
  GTEST_ASSERT_EQ(*iter, 15);
}

TEST(overload, iter_plusplus_5) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto iter = test1.end();
  ++iter;
  GTEST_ASSERT_EQ(*iter, 15);
}

TEST(overload, iter_plusplus_6) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto iter = test1.end();
  ++iter;
  ++iter;
  ++iter;
  ++iter;
  --iter;
  --iter;
  GTEST_ASSERT_EQ(*iter, 9);
}

TEST(overload, iter_plusplus_7) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto iter = test1.begin();
  --iter;
  --iter;
  --iter;
  GTEST_ASSERT_EQ(*iter, -10);
}

TEST(func, find_1) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto iter = test1.find(9);
  GTEST_ASSERT_EQ(*iter, 9);
}

TEST(func, find_2) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto iter = test1.find(99);
  GTEST_ASSERT_EQ((iter.getter() == nullptr), 1);
}

TEST(overload, iter_minus_minus) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto iter = test1.find(9);
  --iter;
  --iter;
  GTEST_ASSERT_EQ(*iter, 5);
}

TEST(func, erase_1) {
  set<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto iter = test1.begin();
  GTEST_ASSERT_EQ(test1.size(), 10);
  GTEST_ASSERT_EQ(*test1.begin(), 1);
  test1.erase(iter);
  GTEST_ASSERT_EQ(*test1.begin(), 2);
  GTEST_ASSERT_EQ(test1.size(), 9);
}

TEST(func, erase_2) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto iter = test1.find(9);
  GTEST_ASSERT_EQ(test1.size(), 6);
  test1.erase(iter);
  GTEST_ASSERT_EQ(test1.size(), 5);
  iter = test1.find(9);
  GTEST_ASSERT_EQ((iter.getter() == nullptr), 1);
}

TEST(func, insert_1) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  GTEST_ASSERT_EQ(test1.size(), 6);
  test1.insert(10);
  GTEST_ASSERT_EQ(test1.size(), 7);
  auto iter = test1.find(10);
  GTEST_ASSERT_EQ(*iter, 10);
}

TEST(func, insert_2) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  GTEST_ASSERT_EQ(test1.size(), 6);
  auto temp = test1.insert(10);
  GTEST_ASSERT_EQ(*(temp.first), 10);
  GTEST_ASSERT_EQ(test1.size(), 7);
  GTEST_ASSERT_EQ(temp.second, true);
}

TEST(func, insert_3) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  GTEST_ASSERT_EQ(test1.size(), 6);
  auto temp = test1.insert(15);
  GTEST_ASSERT_EQ(temp.first.getter() == nullptr, true);
  GTEST_ASSERT_EQ(temp.second, false);
  GTEST_ASSERT_EQ(test1.size(), 6);
}

TEST(func, merge_1) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  set<int> test2{18, 9, 4, 55, -10};
  GTEST_ASSERT_EQ(test1.size(), 6);
  GTEST_ASSERT_EQ(test2.size(), 5);
  test1.merge(test2);
  GTEST_ASSERT_EQ(test1.size(), 8);
  GTEST_ASSERT_EQ(test2.size(), 3);
}

TEST(func, merge_2) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  set<int> test2;
  GTEST_ASSERT_EQ(test1.size(), 6);
  GTEST_ASSERT_EQ(test2.size(), 0);
  test1.merge(test2);
  GTEST_ASSERT_EQ(test1.size(), 6);
  GTEST_ASSERT_EQ(test2.size(), 0);
}

TEST(func, merge_3) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  set<int> test2(test1);
  GTEST_ASSERT_EQ(test1.size(), 6);
  GTEST_ASSERT_EQ(test2.size(), 6);
  test1.merge(test2);
  GTEST_ASSERT_EQ(test1.size(), 6);
  GTEST_ASSERT_EQ(test2.size(), 6);
}

TEST(func, merge_4) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  set<int> test2{18, 9, 4, 55, 3};
  GTEST_ASSERT_EQ(test1.size(), 6);
  GTEST_ASSERT_EQ(test2.size(), 5);
  test1.merge(test2);
  GTEST_ASSERT_EQ(test1.size(), 9);
  GTEST_ASSERT_EQ(test2.size(), 2);
}

TEST(func, merge_5) {
  set<int> animals{5, 3, 7, 1, 2, 6, 10, 8, 9, 4};
  set<int> fruits{5, 13, 7, 1, 2, 16, 11};
  set<int> map_merge;
  map_merge.merge(animals);
  ASSERT_EQ(map_merge.size(), 10);
  ASSERT_EQ(animals.size(), 0);
  map_merge.merge(fruits);
  ASSERT_EQ(map_merge.size(), 13);
  ASSERT_EQ(fruits.size(), 4);
}

TEST(func, end) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  GTEST_ASSERT_EQ(test1.end().getter() == nullptr, true);
}

TEST(func, empty_1) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  GTEST_ASSERT_EQ(test1.empty(), false);
}

TEST(func, empty_2) {
  set<int> test1;
  GTEST_ASSERT_EQ(test1.empty(), true);
}

TEST(func, clear_1) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  GTEST_ASSERT_EQ(test1.empty(), false);
  test1.clear();
  GTEST_ASSERT_EQ(test1.empty(), true);
}

TEST(func, clear_2) {
  set<int> test1;
  GTEST_ASSERT_EQ(test1.empty(), true);
  test1.clear();
  GTEST_ASSERT_EQ(test1.empty(), true);
}

TEST(func, swap_1) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  set<int> test2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTEST_ASSERT_EQ(test1.size(), 6);
  GTEST_ASSERT_EQ(test2.size(), 10);
  test1.swap(test2);
  GTEST_ASSERT_EQ(test1.size(), 10);
  GTEST_ASSERT_EQ(test2.size(), 6);
}

TEST(func, swap_2) {
  set<int> test1;
  set<int> test2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTEST_ASSERT_EQ(test1.size(), 0);
  GTEST_ASSERT_EQ(test2.size(), 10);
  test1.swap(test2);
  GTEST_ASSERT_EQ(test1.size(), 10);
  GTEST_ASSERT_EQ(test2.size(), 0);
}

TEST(func, swap_3) {
  set<int> test1;
  set<int> test2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTEST_ASSERT_EQ(test1.size(), 0);
  GTEST_ASSERT_EQ(test2.size(), 10);
  test2.swap(test1);
  GTEST_ASSERT_EQ(test1.size(), 10);
  GTEST_ASSERT_EQ(test2.size(), 0);
}

TEST(func, contains_1) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  bool eight = test1.contains(9);
  GTEST_ASSERT_EQ(eight, true);
}

TEST(func, contains_2) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  bool eight = test1.contains(99);
  GTEST_ASSERT_EQ(eight, false);
}

TEST(func, max_size) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  set<double> test2;
  GTEST_ASSERT_EQ(test1.max_size(), 524288);
  GTEST_ASSERT_EQ(test2.max_size(), 262144);
}

TEST(temp_func, find_min_1) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto eight = test1.begin();
  ++eight;
  ++eight;
  ++eight;
  auto result = eight.find_min(eight.getter());
  GTEST_ASSERT_EQ((*result).get_value(), -10);
}

TEST(temp_func, find_min_2) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto eight = test1.begin();
  ++eight;
  ++eight;
  ++eight;
  ++eight;
  auto result = eight.find_min(eight.getter());
  GTEST_ASSERT_EQ((*result).get_value(), 9);
}

TEST(temp_func, find_max_1) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto eight = test1.begin();
  ++eight;
  ++eight;
  ++eight;
  auto result = eight.find_max(eight.getter());
  GTEST_ASSERT_EQ((*result).get_value(), 15);
}

TEST(temp_func, find_max_2) {
  set<int> test1{8, 15, 9, 4, 5, -10};
  auto eight = test1.begin();
  ++eight;
  auto result = eight.find_max(eight.getter());
  GTEST_ASSERT_EQ((*result).get_value(), 5);
}

TEST(extra, iterator_sets_1) {
  set<int> test1{5, -20, -30, -40, 18, 10, 7, 6, 12, 15, 29, 20, 37};
  auto l = test1.begin();
  GTEST_ASSERT_EQ(*l, -40);
  ++l;
  GTEST_ASSERT_EQ(*l, -30);
  ++l;
  GTEST_ASSERT_EQ(*l, -20);
  ++l;
  GTEST_ASSERT_EQ(*l, 5);
  ++l;
  GTEST_ASSERT_EQ(*l, 6);
  ++l;
  GTEST_ASSERT_EQ(*l, 7);
  ++l;
  GTEST_ASSERT_EQ(*l, 10);
  ++l;
  GTEST_ASSERT_EQ(*l, 12);
  ++l;
  GTEST_ASSERT_EQ(*l, 15);
  ++l;
  GTEST_ASSERT_EQ(*l, 18);
  ++l;
  GTEST_ASSERT_EQ(*l, 20);
  ++l;
  GTEST_ASSERT_EQ(*l, 29);
  ++l;
  GTEST_ASSERT_EQ(*l, 37);
}

TEST(extra, iterator_sets_2) {
  set<int> test1{5, -20, -30, -40, 18, 10, 7, 6, 12, 15, 29, 20, 37};
  auto l = test1.end_element();
  GTEST_ASSERT_EQ(*l, 37);
  --l;
  GTEST_ASSERT_EQ(*l, 29);
  --l;
  GTEST_ASSERT_EQ(*l, 20);
  --l;
  GTEST_ASSERT_EQ(*l, 18);
  --l;
  GTEST_ASSERT_EQ(*l, 15);
  --l;
  GTEST_ASSERT_EQ(*l, 12);
  --l;
  GTEST_ASSERT_EQ(*l, 10);
  --l;
  GTEST_ASSERT_EQ(*l, 7);
  --l;
  GTEST_ASSERT_EQ(*l, 6);
  --l;
  GTEST_ASSERT_EQ(*l, 5);
  --l;
  GTEST_ASSERT_EQ(*l, -20);
  --l;
  GTEST_ASSERT_EQ(*l, -30);
  --l;
  GTEST_ASSERT_EQ(*l, -40);
}

TEST(extra, iterator_sets_3) {
  set<int> test1{0, 3, -50, -25, -70, -100, -45, -48, -30, -10, -5, 60, 80, 99};
  auto endl = test1.end();
  auto beg = test1.begin();
  GTEST_ASSERT_EQ(*endl, 99);
  --endl;
  GTEST_ASSERT_EQ(*endl, 99);
  --endl;
  GTEST_ASSERT_EQ(*endl, 80);
  --endl;
  GTEST_ASSERT_EQ(*endl, 60);
  --endl;
  GTEST_ASSERT_EQ(*endl, 3);
  --endl;
  GTEST_ASSERT_EQ(*endl, 0);
  --endl;
  GTEST_ASSERT_EQ(*endl, -5);
  --endl;
  GTEST_ASSERT_EQ(*endl, -10);
  --endl;
  GTEST_ASSERT_EQ(*endl, -25);
  --endl;
  GTEST_ASSERT_EQ(*endl, -30);
  --endl;
  GTEST_ASSERT_EQ(*endl, -45);
  --endl;
  GTEST_ASSERT_EQ(*endl, -48);
  --endl;
  GTEST_ASSERT_EQ(*endl, -50);
  --endl;
  GTEST_ASSERT_EQ(*endl, -70);
  --endl;
  GTEST_ASSERT_EQ(*endl, -100);
  --endl;
  GTEST_ASSERT_EQ(*endl, -100);
  --endl;
  GTEST_ASSERT_EQ(*endl, -100);

  GTEST_ASSERT_EQ(*beg, -100);
  ++beg;
  GTEST_ASSERT_EQ(*beg, -70);
  ++beg;
  GTEST_ASSERT_EQ(*beg, -50);
  ++beg;
  GTEST_ASSERT_EQ(*beg, -48);
  ++beg;
  GTEST_ASSERT_EQ(*beg, -45);
  ++beg;
  GTEST_ASSERT_EQ(*beg, -30);
  ++beg;
  GTEST_ASSERT_EQ(*beg, -25);
  ++beg;
  GTEST_ASSERT_EQ(*beg, -10);
  ++beg;
  GTEST_ASSERT_EQ(*beg, -5);
  ++beg;
  GTEST_ASSERT_EQ(*beg, 0);
  ++beg;
  GTEST_ASSERT_EQ(*beg, 3);
  ++beg;
  GTEST_ASSERT_EQ(*beg, 60);
  ++beg;
  GTEST_ASSERT_EQ(*beg, 80);
  ++beg;
  GTEST_ASSERT_EQ(*beg, 99);
  ++beg;
  GTEST_ASSERT_EQ(*beg, 99);
  ++beg;
  GTEST_ASSERT_EQ(*beg, 99);
  ++beg;
}

TEST(func, emplace_1) {
  set<int> temp{5, 3, 4, 10, 6, 8};
  GTEST_ASSERT_EQ(temp.size(), 6);
  auto test = temp.emplace(7);
  GTEST_ASSERT_EQ(temp.size(), 7);
  GTEST_ASSERT_EQ(*(test.first), 7);
  GTEST_ASSERT_EQ(test.second, true);
}

TEST(func, emplace_2) {
  set<int> temp{5, 3, 4, 10, 6, 8};
  GTEST_ASSERT_EQ(temp.size(), 6);
  auto test = temp.emplace(4);
  GTEST_ASSERT_EQ(temp.size(), 6);
  GTEST_ASSERT_EQ(*(test.first), 4);
  GTEST_ASSERT_EQ(test.second, false);
}

TEST(func, emplace_3) {
  set<int> temp{5, 3, 4, 10, 6, 8};
  GTEST_ASSERT_EQ(temp.size(), 6);
  auto test = temp.emplace(4, 7, 9, 12);
  GTEST_ASSERT_EQ(temp.size(), 9);
  GTEST_ASSERT_EQ(*(test.first), 12);
  GTEST_ASSERT_EQ(test.second, true);
}

TEST(func, emplace_4) {
  set<int> temp;
  GTEST_ASSERT_EQ(temp.size(), 0);
  auto test = temp.emplace(4, 7, 9, 12, 22, 11, 2);
  GTEST_ASSERT_EQ(temp.size(), 7);
  GTEST_ASSERT_EQ(*(test.first), 2);
  GTEST_ASSERT_EQ(test.second, true);
}

TEST(func, big_size) {
  set<int> temp;
  for (auto i = 3000; i > 0; --i) {
    temp.insert(i);
  }
  auto f = temp.find(1684);
  GTEST_ASSERT_EQ(temp.size(), 3000);
  GTEST_ASSERT_EQ(*f, 1684);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
  return 0;
}
