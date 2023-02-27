#include <gtest/gtest.h>

#include "s21_multiset.h"

TEST(func, insert_1) {
  multiset<int> test1{1, 2, 3, 4, 5, 6, 7, 7, 7};
  GTEST_ASSERT_EQ(test1.size(), 9);
  test1.insert(4);
  GTEST_ASSERT_EQ(test1.size(), 10);
  auto l = test1.find(4);
  GTEST_ASSERT_EQ(*l, 4);
}

TEST(func, insert_2) {
  multiset<int> test1{4, 5, 7, 4, 9, 4, 1, 1, 1};
  GTEST_ASSERT_EQ(test1.size(), 9);
  test1.insert(41);
  GTEST_ASSERT_EQ(test1.size(), 10);
  auto l = test1.find(41);
  GTEST_ASSERT_EQ(*l, 41);
}

TEST(func, insert_3) {
  multiset<int> test1;
  GTEST_ASSERT_EQ(test1.empty(), 1);
  GTEST_ASSERT_EQ(test1.size(), 0);
  test1.insert(41);
  GTEST_ASSERT_EQ(test1.size(), 1);
  auto l = test1.begin();
  GTEST_ASSERT_EQ(*l, 41);
}

TEST(func, merge_1) {
  multiset<int> test1{4, 5, 7, 4, 9, 4, 1, 1, 1};
  multiset<int> test2{14, 15, 17, 4, 19, 11, 1, 1};
  GTEST_ASSERT_EQ(test1.size(), 9);
  GTEST_ASSERT_EQ(test2.size(), 8);
  test1.merge(test2);
  GTEST_ASSERT_EQ(test1.size(), 17);
  GTEST_ASSERT_EQ(test2.size(), 0);
}

TEST(func, merge_2) {
  multiset<int> test1{4, 5, 7, 4, 9, 4, 1, 1, 1};
  multiset<int> test2;
  GTEST_ASSERT_EQ(test1.size(), 9);
  GTEST_ASSERT_EQ(test2.size(), 0);
  test1.merge(test2);
  GTEST_ASSERT_EQ(test1.size(), 9);
  GTEST_ASSERT_EQ(test2.size(), 0);
}

TEST(func, merge_3) {
  multiset<int> test2{4, 5, 7, 4, 9, 4, 1, 1, 1};
  multiset<int> test1;
  GTEST_ASSERT_EQ(test2.size(), 9);
  GTEST_ASSERT_EQ(test1.size(), 0);
  test1.merge(test2);
  GTEST_ASSERT_EQ(test1.size(), 9);
  GTEST_ASSERT_EQ(test2.size(), 0);
}

TEST(func, lower_bound_1) {
  multiset<int> test2{4, 5, 7, 4, 9, 4};
  auto l = test2.lower_bound(4);
  auto b = test2.begin();
  GTEST_ASSERT_EQ(*l, *b);
  GTEST_ASSERT_EQ(l.getter(), b.getter());
}

TEST(func, lower_bound_2) {
  multiset<int> test2{4, 5, 7, 4, 9, 4};
  auto l = test2.lower_bound(6);
  GTEST_ASSERT_EQ(l.getter() == nullptr, 1);
}

TEST(func, upper_bound_1) {
  multiset<int> test2{4, 5, 7, 4, 9, 4};
  auto b = test2.begin();
  ++b;
  ++b;
  auto l = test2.upper_bound(4);
  GTEST_ASSERT_EQ(l.getter(), b.getter());
}

TEST(func, upper_bound_4) {
  multiset<int> test2{4, 5, 7, 77, 9, 41};
  auto b = test2.begin();
  auto l = test2.upper_bound(4);
  GTEST_ASSERT_EQ(l == b, 1);
}

TEST(func, upper_bound_2) {
  multiset<int> test2{4, 5, 7, 4, 9, 4};
  auto l = test2.upper_bound(10);
  GTEST_ASSERT_EQ(l.getter() == nullptr, 1);
}

TEST(func, upper_bound_3) {
  multiset<int> test2;
  auto l = test2.upper_bound(4);
  auto b = test2.begin();
  GTEST_ASSERT_EQ(l.getter(), b.getter());
}

TEST(func, equal_range_2) {
  multiset<int> test2{4, 5, 7, 4, 9, 4, 15, 731, 4};
  auto p2 = test2.equal_range(4);
  auto l_lower = test2.begin();
  auto l_upper = l_lower;
  ++l_upper;
  ++l_upper;
  ++l_upper;
  GTEST_ASSERT_EQ(l_lower.getter() == (p2.first).getter(), 1);
  GTEST_ASSERT_EQ(l_upper.getter() == (p2.second).getter(), 1);
}

TEST(func, equal_range_3) {
  multiset<int> test2{5, 9, 4, 15, 12, 451};
  auto p2 = test2.equal_range(9);
  auto l_lower = test2.begin();
  ++l_lower;
  ++l_lower;
  GTEST_ASSERT_EQ(l_lower.getter() == (p2.first).getter(), 1);
  GTEST_ASSERT_EQ(l_lower.getter() == (p2.second).getter(), 1);
}

TEST(func, equal_range_4) {
  multiset<int> test2{5, 9, 4, 15, 12, 451};
  auto p2 = test2.equal_range(99);
  GTEST_ASSERT_EQ(nullptr == (p2.first).getter(), 1);
  GTEST_ASSERT_EQ(nullptr == (p2.second).getter(), 1);
}

TEST(func, equal_range_5) {
  multiset<int> test2;
  auto p2 = test2.equal_range(99);
  GTEST_ASSERT_EQ(nullptr == (p2.first).getter(), 1);
  GTEST_ASSERT_EQ(nullptr == (p2.second).getter(), 1);
}

TEST(func, count_1) {
  multiset<int> test2{9, 6, 4, 6, 6, 1, 2, 6, 9, 25, 125};
  auto p2 = test2.count(6);
  GTEST_ASSERT_EQ(p2, 4);
}

TEST(func, count_2) {
  multiset<int> test2{9, 6, 4, 6, 6, 1, 2, 6, 9, 25, 125};
  auto p2 = test2.count(4);
  GTEST_ASSERT_EQ(p2, 1);
}

TEST(func, count_3) {
  multiset<int> test2{9, 6, 4, 6, 6, 1, 2, 6, 9, 25, 125};
  auto p2 = test2.count(44);
  GTEST_ASSERT_EQ(p2, 0);
}

TEST(func, count_4) {
  multiset<int> test2;
  auto p2 = test2.count(4);
  GTEST_ASSERT_EQ(p2, 0);
}

TEST(func, emplace_1) {
  multiset<int> test2{1, 2, 3, 4, 5, 6};
  auto it = test2.emplace(7, 8, 9, 10);
  GTEST_ASSERT_EQ(test2.size(), 10);
  GTEST_ASSERT_EQ(*(it.first), 10);
  GTEST_ASSERT_EQ(it.second, true);
}

TEST(func, emplace_2) {
  multiset<int> test2{1, 2, 3, 4, 5, 6};
  auto it = test2.emplace(7, 8, 9, 10, 5, 6, 10, 9);
  GTEST_ASSERT_EQ(test2.size(), 14);
  GTEST_ASSERT_EQ(*(it.first), 9);
  GTEST_ASSERT_EQ(it.second, true);
}

TEST(func, emplace_3) {
  multiset<int> test2{1, 2, 3, 4, 5, 6};
  auto it = test2.emplace(7);
  GTEST_ASSERT_EQ(test2.size(), 7);
  GTEST_ASSERT_EQ(*(it.first), 7);
  GTEST_ASSERT_EQ(it.second, true);
}

TEST(func, emplace_4) {
  multiset<int> test2{1, 2, 3, 4, 5, 6};
  auto it = test2.emplace(6);
  GTEST_ASSERT_EQ(test2.size(), 7);
  GTEST_ASSERT_EQ(*(it.first), 6);
  GTEST_ASSERT_EQ(it.second, true);
}

TEST(func, emplace_5) {
  multiset<int> test2{};
  auto it = test2.emplace(7, 8, 9);
  GTEST_ASSERT_EQ(test2.size(), 3);
  GTEST_ASSERT_EQ(*(it.first), 9);
  GTEST_ASSERT_EQ(it.second, true);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
  return 0;
}
