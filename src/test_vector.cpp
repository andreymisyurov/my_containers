#include <gtest/gtest.h>

#include "s21_vector.h"

TEST(constr, defolt_1) { vector<int> testa; }

TEST(constr, defolt_2) { vector<int> testa{}; }

TEST(constr, move) {
  vector<int> testa{1, 2, 3, 4, 5};
  vector<int> a(std::move(testa));
}

TEST(constr, copy) {
  vector<int> testa{1, 2, 3, 4, 5};
  vector<int> a(testa);
  GTEST_ASSERT_EQ(testa.size(), a.size());
  for (int i = testa.size(); i > 0; --i) {
    GTEST_ASSERT_EQ(testa.back(), a.back());
    testa.pop_back();
    a.pop_back();
  }
}

TEST(constr, with_size) { vector<int> testa(50); }

TEST(constr, init_list_1) {
  vector<int> testa{4, 5, 2};
  GTEST_ASSERT_EQ(testa.size(), 3);
  GTEST_ASSERT_EQ(testa.capacity(), 6);
}

TEST(constr, init_1) {
  vector<int> testa{1};
  GTEST_ASSERT_EQ(testa.size(), 1);
  GTEST_ASSERT_EQ(testa.capacity(), 4);
}

TEST(equals, move) {
  vector<int> a{1, 2, 3, 4, 5};
  vector<int> b;
  b = std::move(a);
  GTEST_ASSERT_EQ(b.size(), 5);
  GTEST_ASSERT_EQ(b.capacity(), 10);
  GTEST_ASSERT_EQ(b.front(), 1);
  GTEST_ASSERT_EQ(b.back(), 5);
}

TEST(equal, copy) {
  vector<int> testa{1, 2, 3, 4, 5};
  vector<int> a;
  a = testa;
  GTEST_ASSERT_EQ(testa.size(), a.size());
  for (int i = testa.size(); i > 0; --i) {
    GTEST_ASSERT_EQ(testa.back(), a.back());
    testa.pop_back();
    a.pop_back();
  }
}

TEST(func, push_back) {
  vector<int> test;
  test.push_back(15);
  test.push_back(15);
  GTEST_ASSERT_EQ(test.size(), 2);
}

TEST(func, pop_back) {
  vector<int> test;
  test.push_back(15);
  test.push_back(15);
  test.push_back(15);
  test.push_back(15);
  test.push_back(15);
  test.pop_back();
  test.pop_back();
  GTEST_ASSERT_EQ(test.size(), 3);
}

TEST(func, empty_1) {
  vector<int> test;
  test.push_back(15);
  test.push_back(15);
  GTEST_ASSERT_EQ(test.empty(), 0);
}

TEST(func, empty_2) {
  vector<int> test;
  GTEST_ASSERT_EQ(test.empty(), 1);
}

TEST(access, front) {
  vector<int> test{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(test.front(), 1);
}

TEST(access, back) {
  vector<int> test{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(test.back(), 5);
}

TEST(access, data) {
  vector<int> test{1, 2, 3, 4, 5};
  int* data = test.data();
  data[2] = 1;
  test.pop_back();
  test.pop_back();
  GTEST_ASSERT_EQ(test.back(), 1);
}

TEST(func, swap_1) {
  vector<int> test_1;
  vector<int> test_2(50);
  test_1.push_back(1);
  test_1.push_back(1);
  test_1.push_back(1);
  test_1.push_back(1);
  test_1.push_back(1);
  test_2.push_back(2);
  test_2.push_back(2);
  test_2.push_back(2);
  test_1.swap(test_2);
  GTEST_ASSERT_EQ(test_1.size(), 3);
  GTEST_ASSERT_EQ(test_2.size(), 5);
  GTEST_ASSERT_EQ(test_2.capacity(), 100);
  GTEST_ASSERT_EQ(test_1.capacity(), 50);
}

TEST(func, clear_1) {
  vector<int> test_1;
  for (int i = 0; i < 100; ++i) {
    test_1.push_back(i);
  }
  GTEST_ASSERT_EQ(test_1.size(), 100);
  test_1.clear();
  GTEST_ASSERT_EQ(test_1.size(), 0);
}

TEST(func, capacity_1) {
  vector<int> test_1;
  GTEST_ASSERT_EQ(test_1.capacity(), 100);
  test_1.push_back(1);
  test_1.push_back(2);
  test_1.clear();
  GTEST_ASSERT_EQ(test_1.capacity(), 100);
}

TEST(func, capacity_2) {
  vector<int> test_1(50);
  test_1.push_back(1);
  test_1.push_back(2);
  GTEST_ASSERT_EQ(test_1.capacity(), 50);
}

TEST(temp_func, fillness) {
  vector<int> test_1(7);
  test_1.push_back(1);
  test_1.push_back(2);
  test_1.push_back(3);
  test_1.push_back(4);
  test_1.push_back(5);
  test_1.push_back(6);
  test_1.push_back(7);
  GTEST_ASSERT_EQ(test_1.capacity(), 7);
}

TEST(overload, bracket) {
  vector<int> test_1(7);
  test_1.push_back(-2);
  test_1.push_back(2);
  test_1.push_back(3);
  test_1.push_back(4);
  test_1.push_back(5);
  test_1.push_back(6);
  test_1.push_back(7);
  test_1[6] = -2;
  GTEST_ASSERT_EQ(test_1[6], -2);
  GTEST_ASSERT_EQ(test_1[6], test_1.front());
}

TEST(func, at) {
  vector<int> test_1(7);
  test_1.push_back(-2);
  test_1.push_back(2);
  test_1.push_back(3);
  test_1.push_back(4);
  test_1.push_back(5);
  test_1.push_back(6);
  test_1.push_back(7);
  test_1[6] = -2;
  GTEST_ASSERT_EQ(test_1.at(6), -2);
  GTEST_ASSERT_EQ(test_1[6], test_1.front());
}

// TEST(func, at_exaption) {
//   vector<int> test_1(7);
//   test_1.push_back(-2);
//   test_1.push_back(2);
//   EXPECT_THROW(test_1.at(6), std::runtime_error);
// }

TEST(func, reserve_1) {
  vector<int> test_1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTEST_ASSERT_EQ(test_1.capacity(), 20);
  test_1.reserve(50);
  GTEST_ASSERT_EQ(test_1.size(), 10);
  GTEST_ASSERT_EQ(test_1.capacity(), 50);
  for (int i = 0; i < 10; ++i) {
    GTEST_ASSERT_EQ(test_1.at(i), i + 1);
  }
}

TEST(func, shrink_to_fit_1) {
  vector<int> test_1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTEST_ASSERT_EQ(test_1.capacity(), 20);
  test_1.reserve(50);
  test_1.push_back(11);
  test_1.push_back(12);
  GTEST_ASSERT_EQ(test_1.capacity(), 50);
  GTEST_ASSERT_EQ(test_1.size(), 12);
  test_1.shrink_to_fit();
  GTEST_ASSERT_EQ(test_1.size(), 12);
  GTEST_ASSERT_EQ(test_1.capacity(), 12);
  for (int i = 0; i < 12; ++i) {
    GTEST_ASSERT_EQ(test_1.at(i), i + 1);
  }
}

TEST(func, begin) {
  vector<int> test_1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTEST_ASSERT_EQ(*(test_1.begin()), 1);
}

TEST(func, end) {
  vector<int> test_1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTEST_ASSERT_EQ(*(--test_1.end()), 10);
}

TEST(iter, zvezda_1) {
  vector<int> test_1;
  test_1[0] = 1;
  GTEST_ASSERT_EQ(*(test_1.begin()), 1);
}

TEST(iter, more_1) {
  vector<int> test_1{1, 2, 3, 4, 5};
  auto a = test_1.begin();
  auto b = test_1.end();
  GTEST_ASSERT_EQ(b > a, 1);
}

TEST(iter, more_2) {
  vector<int> test_1{1, 2, 3, 4, 5};
  auto a = test_1.begin();
  auto b = test_1.begin();
  ++a;
  GTEST_ASSERT_EQ(b > a, 0);
}

TEST(iter, more_equal_2) {
  vector<int> test_1{1, 2, 3, 4, 5};
  auto a = test_1.begin();
  auto b = test_1.begin();
  GTEST_ASSERT_EQ(b >= a, 1);
}

TEST(iter, less_1) {
  vector<int> test_1{1, 2, 3, 4, 5};
  auto a = test_1.begin();
  auto b = test_1.end();
  GTEST_ASSERT_EQ(a < b, 1);
}

TEST(iter, prefix_1) {
  vector<int> test_1;
  test_1[0] = 11;
  test_1[1] = 22;
  test_1[2] = 33;
  auto iter = ++(test_1.begin());
  GTEST_ASSERT_EQ(*iter, 22);
}

TEST(iter, prefix_2) {
  vector<int> test_1;
  test_1[0] = 11;
  test_1[1] = 22;
  test_1[2] = 33;
  auto iter = test_1.begin();
  ++iter;
  ++iter;
  --iter;
  GTEST_ASSERT_EQ(*iter, 22);
}

TEST(iter, erase_1_midl) {
  vector<int> test_1;
  test_1.push_back(11);
  test_1.push_back(22);
  test_1.push_back(33);
  auto iter = test_1.begin();
  ++iter;
  test_1.erase(iter);
  GTEST_ASSERT_EQ(test_1.size(), 2);
  GTEST_ASSERT_EQ(test_1.at(0), 11);
  GTEST_ASSERT_EQ(test_1.at(1), 33);
}

TEST(iter, erase_2_end) {
  vector<int> test_1;
  test_1.push_back(11);
  test_1.push_back(22);
  test_1.push_back(33);
  test_1.push_back(44);
  test_1.push_back(55);
  auto iter = test_1.end();
  --iter;
  test_1.erase(iter);
  GTEST_ASSERT_EQ(test_1.size(), 4);
  GTEST_ASSERT_EQ(test_1.at(0), 11);
  GTEST_ASSERT_EQ(test_1.at(1), 22);
  GTEST_ASSERT_EQ(test_1.at(2), 33);
  GTEST_ASSERT_EQ(test_1.at(3), 44);
}

TEST(iter, erase_3_begin) {
  vector<int> test_1;
  test_1.push_back(11);
  test_1.push_back(22);
  test_1.push_back(33);
  test_1.push_back(44);
  test_1.push_back(55);
  auto iter = test_1.begin();
  test_1.erase(iter);
  GTEST_ASSERT_EQ(test_1.size(), 4);
  GTEST_ASSERT_EQ(test_1.at(0), 22);
  GTEST_ASSERT_EQ(test_1.at(1), 33);
  GTEST_ASSERT_EQ(test_1.at(2), 44);
  GTEST_ASSERT_EQ(test_1.at(3), 55);
}

TEST(iter, insert_1_midl) {
  vector<int> test_1;
  test_1.push_back(11);
  test_1.push_back(22);
  test_1.push_back(33);
  test_1.push_back(44);
  test_1.push_back(55);
  test_1.push_back(66);
  test_1.push_back(77);
  test_1.push_back(88);
  test_1.push_back(99);
  auto iter = test_1.begin();
  ++iter;
  ++iter;
  ++iter;
  ++iter;
  test_1.insert(iter, 21);
  GTEST_ASSERT_EQ(test_1.size(), 10);
  GTEST_ASSERT_EQ(test_1.at(0), 11);
  GTEST_ASSERT_EQ(test_1.at(1), 22);
  GTEST_ASSERT_EQ(test_1.at(2), 33);
  GTEST_ASSERT_EQ(test_1.at(3), 44);
  GTEST_ASSERT_EQ(test_1.at(4), 21);
  GTEST_ASSERT_EQ(test_1.at(5), 55);
  GTEST_ASSERT_EQ(test_1.at(6), 66);
  GTEST_ASSERT_EQ(test_1.at(7), 77);
  GTEST_ASSERT_EQ(test_1.at(8), 88);
  GTEST_ASSERT_EQ(test_1.at(9), 99);
}

TEST(iter, insert_2_begin) {
  vector<int> test_1;
  test_1.push_back(11);
  test_1.push_back(22);
  test_1.push_back(33);
  test_1.push_back(44);
  test_1.push_back(55);
  test_1.push_back(66);
  test_1.push_back(77);
  test_1.push_back(88);
  test_1.push_back(99);
  auto iter = test_1.begin();
  test_1.insert(iter, 21);
  GTEST_ASSERT_EQ(test_1.size(), 10);
  GTEST_ASSERT_EQ(test_1.at(0), 21);
  GTEST_ASSERT_EQ(test_1.at(1), 11);
  GTEST_ASSERT_EQ(test_1.at(2), 22);
  GTEST_ASSERT_EQ(test_1.at(3), 33);
  GTEST_ASSERT_EQ(test_1.at(4), 44);
  GTEST_ASSERT_EQ(test_1.at(5), 55);
  GTEST_ASSERT_EQ(test_1.at(6), 66);
  GTEST_ASSERT_EQ(test_1.at(7), 77);
  GTEST_ASSERT_EQ(test_1.at(8), 88);
  GTEST_ASSERT_EQ(test_1.at(9), 99);
}

TEST(iter, insert_3_end) {
  vector<int> test_1;
  test_1.push_back(11);
  test_1.push_back(22);
  test_1.push_back(33);
  test_1.push_back(44);
  test_1.push_back(55);
  test_1.push_back(66);
  test_1.push_back(77);
  test_1.push_back(88);
  test_1.push_back(99);
  auto iter = test_1.end();
  test_1.insert(iter, 21);
  GTEST_ASSERT_EQ(test_1.size(), 10);
  GTEST_ASSERT_EQ(test_1.at(0), 11);
  GTEST_ASSERT_EQ(test_1.at(1), 22);
  GTEST_ASSERT_EQ(test_1.at(2), 33);
  GTEST_ASSERT_EQ(test_1.at(3), 44);
  GTEST_ASSERT_EQ(test_1.at(4), 55);
  GTEST_ASSERT_EQ(test_1.at(5), 66);
  GTEST_ASSERT_EQ(test_1.at(6), 77);
  GTEST_ASSERT_EQ(test_1.at(7), 88);
  GTEST_ASSERT_EQ(test_1.at(8), 99);
  GTEST_ASSERT_EQ(test_1.at(9), 21);
}

TEST(extra_func, emplace_1) {
  vector<int> test_1{1, 2, 3, 4, 8, 9, 10};
  auto it = test_1.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  auto check = test_1.emplace(it, 5, 6, 7);
  GTEST_ASSERT_EQ(test_1[0], 1);
  GTEST_ASSERT_EQ(test_1[1], 2);
  GTEST_ASSERT_EQ(test_1[2], 3);
  GTEST_ASSERT_EQ(test_1[3], 4);
  GTEST_ASSERT_EQ(test_1[4], 5);
  GTEST_ASSERT_EQ(test_1[5], 6);
  GTEST_ASSERT_EQ(test_1[6], 7);
  GTEST_ASSERT_EQ(test_1[7], 8);
  GTEST_ASSERT_EQ(test_1[8], 9);
  GTEST_ASSERT_EQ(test_1[9], 10);
  GTEST_ASSERT_EQ(*check, 5);
}

TEST(extra_func, emplace_2) {
  vector<int> test_1{2, 3, 4};
  auto it = test_1.begin();
  auto check = test_1.emplace(it, 1);
  GTEST_ASSERT_EQ(test_1[0], 1);
  GTEST_ASSERT_EQ(test_1[1], 2);
  GTEST_ASSERT_EQ(test_1[2], 3);
  GTEST_ASSERT_EQ(test_1[3], 4);
  GTEST_ASSERT_EQ(test_1.size(), 4);
}

TEST(extra_func, emplace_3) {
  vector<int> test_1{1, 2, 3};
  auto it = test_1.end();
  auto check = test_1.emplace(it, 4);
  GTEST_ASSERT_EQ(test_1[0], 1);
  GTEST_ASSERT_EQ(test_1[1], 2);
  GTEST_ASSERT_EQ(test_1[2], 3);
  GTEST_ASSERT_EQ(test_1[3], 4);
  GTEST_ASSERT_EQ(test_1.size(), 4);
}

TEST(extra_func, emplace_4) {
  vector<int> test_1;
  auto it = test_1.begin();
  auto check = test_1.emplace(it, 1, 2, 3, 4);
  GTEST_ASSERT_EQ(test_1[0], 1);
  GTEST_ASSERT_EQ(test_1[1], 2);
  GTEST_ASSERT_EQ(test_1[2], 3);
  GTEST_ASSERT_EQ(test_1[3], 4);
  GTEST_ASSERT_EQ(test_1.size(), 4);
}

TEST(extra_func, emplace_back_1) {
  vector<int> test_1{1, 2, 3, 4};
  test_1.emplace_back(5, 6, 7);
  GTEST_ASSERT_EQ(test_1[0], 1);
  GTEST_ASSERT_EQ(test_1[1], 2);
  GTEST_ASSERT_EQ(test_1[2], 3);
  GTEST_ASSERT_EQ(test_1[3], 4);
  GTEST_ASSERT_EQ(test_1[4], 5);
  GTEST_ASSERT_EQ(test_1[5], 6);
  GTEST_ASSERT_EQ(test_1[6], 7);
  GTEST_ASSERT_EQ(test_1.size(), 7);
}

TEST(extra_func, emplace_back_2) {
  vector<int> test_1{1, 2, 3, 4};
  test_1.emplace_back(5);
  GTEST_ASSERT_EQ(test_1[0], 1);
  GTEST_ASSERT_EQ(test_1[1], 2);
  GTEST_ASSERT_EQ(test_1[2], 3);
  GTEST_ASSERT_EQ(test_1[3], 4);
  GTEST_ASSERT_EQ(test_1[4], 5);
  GTEST_ASSERT_EQ(test_1.size(), 5);
}

TEST(extra_func, emplace_back_3) {
  vector<int> test_1;
  test_1.emplace_back(1, 2, 3, 4, 5);
  GTEST_ASSERT_EQ(test_1[0], 1);
  GTEST_ASSERT_EQ(test_1[1], 2);
  GTEST_ASSERT_EQ(test_1[2], 3);
  GTEST_ASSERT_EQ(test_1[3], 4);
  GTEST_ASSERT_EQ(test_1[4], 5);
  GTEST_ASSERT_EQ(test_1.size(), 5);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
  return 0;
}
