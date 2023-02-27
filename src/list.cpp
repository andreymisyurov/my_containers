#include "list.h"

#include <gtest/gtest.h>

#include <list>
#include <ostream>

TEST(constuctor, default_constructor) { List<int> test; }

TEST(constuctor, size_n) {
  List<int> test(5);
  GTEST_ASSERT_EQ(test.getSize(), 5);
}

TEST(constuctor, init_list) {
  List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
  GTEST_ASSERT_EQ(test.getSize(), 8);
}

TEST(func, begin) {
  List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
  GTEST_ASSERT_EQ(*test.begin(), 5);
}

TEST(func, end) {
  List<int> test{5, 4, 22, 156, 3, 2, 1, 111};
  GTEST_ASSERT_EQ(*test.end(), 111);
}

TEST(foreach, foreach) {
  List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
  for (auto &&el : test) {
  }
}

TEST(constuctor, copy) {
  List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
  List<int> result(test);
  GTEST_ASSERT_EQ(result.getSize(), 8);
  GTEST_ASSERT_EQ(*result.begin(), 5);
  GTEST_ASSERT_EQ(*result.end(), 0);
}

TEST(constuctor, move) {
  List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
  List<int> result(std::move(test));
  GTEST_ASSERT_EQ(result.getSize(), 8);
  GTEST_ASSERT_EQ(*result.begin(), 5);
  GTEST_ASSERT_EQ(*result.end(), 0);
}

TEST(operator, equals) {
  List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
  List<int> result;
  GTEST_ASSERT_EQ(result.getSize(), 0);
  result = test;
  GTEST_ASSERT_EQ(result.getSize(), 8);
  GTEST_ASSERT_EQ(*result.begin(), 5);
  GTEST_ASSERT_EQ(*result.end(), 0);
}

TEST(push_back, ex_1) {
  List<int> test;
  test.push_back(5);
  test.push_back(5);
  test.push_back(5);
  GTEST_ASSERT_EQ(test.getSize(), 3);
}

TEST(push_front, ex_1) {
  List<int> test;
  test.push_front(5);
  test.push_front(5);
  test.push_front(5);
  GTEST_ASSERT_EQ(test.getSize(), 3);
}

TEST(pop_back, ex_1) {
  List<int> test;
  test.push_front(5);
  test.push_front(5);
  test.push_front(5);
  test.pop_back();
  test.pop_back();
  GTEST_ASSERT_EQ(test.getSize(), 1);
}

TEST(pop_back, ex_2) {
  List<int> test;
  test.push_front(5);
  test.push_front(5);
  test.push_front(5);
  test.pop_back();
  test.pop_back();
  test.pop_back();
  GTEST_ASSERT_EQ(test.getSize(), 0);
}

TEST(pop_front, ex_1) {
  List<int> test;
  test.push_front(5);
  test.push_front(5);
  test.push_front(5);
  test.pop_front();
  test.pop_front();
  test.pop_front();
  GTEST_ASSERT_EQ(test.getSize(), 0);
}

TEST(pop_front, ex_2) {
  List<int> test;
  test.push_front(5);
  test.push_front(5);
  test.push_front(5);
  test.pop_front();
  test.pop_front();
  GTEST_ASSERT_EQ(test.getSize(), 1);
}

TEST(clear, ex_1) {
  List<int> test;
  test.push_front(5);
  test.push_front(4);
  test.push_front(10);
  test.clear();
  GTEST_ASSERT_EQ(test.getSize(), 0);
}

TEST(iterator, begin) {
  List<int> test;
  test.push_front(5);
  test.push_front(4);
  test.push_front(10);
  GTEST_ASSERT_EQ(*test.begin(), 10);
}

TEST(iterator, end) {
  List<int> test;
  test.push_front(5);
  test.push_front(4);
  test.push_front(10);
  GTEST_ASSERT_EQ(*test.end(), 5);
}

TEST(iterator, not_equals) {
  List<int> test;
  test.push_front(5);
  test.push_front(4);
  test.push_front(10);
  GTEST_ASSERT_EQ(test.begin() != test.end(), 1);
}

TEST(iterator, increment) {
  List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
  auto it = test.begin();
  GTEST_ASSERT_EQ(*it, 5);
  ++it;
  GTEST_ASSERT_EQ(*it, 4);
  ++it;
  GTEST_ASSERT_EQ(*it, 22);
}

TEST(iterator, decrement) {
  List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
  auto it = test.end();
  GTEST_ASSERT_EQ(*it, 0);
  --it;
  GTEST_ASSERT_EQ(*it, 0);
  --it;
  GTEST_ASSERT_EQ(*it, 1);
  --it;
  GTEST_ASSERT_EQ(*it, 2);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
