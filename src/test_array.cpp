#include <gtest/gtest.h>

#include <array>

#include "s21_array.h"

using namespace s21;

TEST(constr, defo) {
  ;
  Array<int, 5> temp;
}

TEST(constr, init_1) {
  Array<int, 5> temp{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(temp[0], 1);
  GTEST_ASSERT_EQ(temp[1], 2);
  GTEST_ASSERT_EQ(temp[2], 3);
  GTEST_ASSERT_EQ(temp[3], 4);
  GTEST_ASSERT_EQ(temp[4], 5);
}

TEST(constr, copy_1) {
  Array<int, 5> temp{1, 2, 3, 4, 5};
  Array<int, 5> test(temp);
}

TEST(constr, copy_2) {
  Array<int, 0> temp;
  Array<int, 0> test(temp);
}

TEST(func, empty_1) {
  Array<int, 5> temp{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(temp.empty(), 0);
}

TEST(func, empty_2) {
  Array<int, 0> temp;
  GTEST_ASSERT_EQ(temp.empty(), 1);
}

TEST(func, size_1) {
  Array<int, 0> temp;
  GTEST_ASSERT_EQ(temp.size(), 0);
}

TEST(func, size_2) {
  Array<int, 10> temp;
  GTEST_ASSERT_EQ(temp.size(), 10);
}

TEST(func, max_size_2) {
  Array<int, 10> temp;
  GTEST_ASSERT_EQ(temp.max_size(), 10);
}

TEST(func, swap_1) {
  Array<int, 5> temp_1{1, 2, 3, 4, 5};
  Array<int, 5> temp_2{0, 9, 8, 7, 6};
  temp_1.swap(temp_2);
  GTEST_ASSERT_EQ(temp_1[0], 0);
  GTEST_ASSERT_EQ(temp_1[1], 9);
  GTEST_ASSERT_EQ(temp_1[2], 8);
  GTEST_ASSERT_EQ(temp_1[3], 7);
  GTEST_ASSERT_EQ(temp_1[4], 6);
  GTEST_ASSERT_EQ(temp_2[0], 1);
  GTEST_ASSERT_EQ(temp_2[1], 2);
  GTEST_ASSERT_EQ(temp_2[2], 3);
  GTEST_ASSERT_EQ(temp_2[3], 4);
  GTEST_ASSERT_EQ(temp_2[4], 5);
}

TEST(func, swap_2) {
  Array<int, 0> temp_1{};
  Array<int, 0> temp_2{};
  temp_1.swap(temp_2);
  GTEST_ASSERT_EQ(temp_1.size(), 0);
  GTEST_ASSERT_EQ(temp_2.size(), 0);
}

TEST(func, swap_3) {
  Array<int, 1> temp_1{0};
  Array<int, 1> temp_2{1};
  temp_1.swap(temp_2);
  GTEST_ASSERT_EQ(temp_1[0], 1);
  GTEST_ASSERT_EQ(temp_2[0], 0);
}

TEST(func, fill_1) {
  Array<int, 5> temp_1;
  temp_1.fill(0);
  GTEST_ASSERT_EQ(temp_1[0], 0);
  GTEST_ASSERT_EQ(temp_1[1], 0);
  GTEST_ASSERT_EQ(temp_1[2], 0);
  GTEST_ASSERT_EQ(temp_1[3], 0);
  GTEST_ASSERT_EQ(temp_1[4], 0);
}

TEST(iter, begin_1) {
  Array<int, 5> temp_1{1, 2, 3, 4, 5};
  auto it = temp_1.begin();
  GTEST_ASSERT_EQ(*it, 1);
}

TEST(iter, end_1) {
  Array<int, 5> temp_1{1, 2, 3, 4, 5};
  auto it = temp_1.end();
  GTEST_ASSERT_EQ(*it != 5, 1);
}

TEST(iter, inctiment) {
  Array<int, 5> temp_1{1, 2, 3, 4, 5};
  auto it = temp_1.begin();
  GTEST_ASSERT_EQ(*it, 1);
  ++it;
  GTEST_ASSERT_EQ(*it, 2);
  ++it;
  GTEST_ASSERT_EQ(*it, 3);
  ++it;
  GTEST_ASSERT_EQ(*it, 4);
  ++it;
  GTEST_ASSERT_EQ(*it, 5);
}

TEST(iter, dectiment) {
  Array<int, 5> temp_1{1, 2, 3, 4, 5};
  auto it = temp_1.end();
  --it;
  GTEST_ASSERT_EQ(*it, 5);
  --it;
  GTEST_ASSERT_EQ(*it, 4);
  --it;
  GTEST_ASSERT_EQ(*it, 3);
  --it;
  GTEST_ASSERT_EQ(*it, 2);
  --it;
  GTEST_ASSERT_EQ(*it, 1);
}

TEST(iter, data) {
  Array<int, 5> temp_1{1, 2, 3, 4, 5};
  auto it = temp_1.data();
  GTEST_ASSERT_EQ(*it, 1);
}

TEST(iter, front) {
  Array<int, 5> temp_1{1, 2, 3, 4, 5};
  auto it = temp_1.front();
  GTEST_ASSERT_EQ(it, 1);
}

TEST(iter, back) {
  Array<int, 5> temp_1{1, 2, 3, 4, 5};
  auto it = temp_1.back();
  GTEST_ASSERT_EQ(it, 5);
}

TEST(constr, stl) {
  std::array<int, 5> temp{1, 2, 3, 4, 5};
  auto l = temp.front();
  //   std::array<int, 6> test(std::move(temp));
  std::cout << l;
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
