#include <gtest/gtest.h>

#include "s21_stack.h"

using namespace s21;

TEST(constr, defolt_1) { stack<int> testa{}; }

TEST(constr, defolt_2) { stack<int> testa; }

TEST(constr, init_list) {
  stack<int> testa{1, 2, 3};
  for (int i = testa.size(); i > 0; i--) {
    GTEST_ASSERT_EQ(testa.top(), i);
    testa.pop();
  }
}

TEST(constr, copy) {
  stack<int> test_1{1, 2, 3, 4, 5};
  stack<int> test_2(test_1);
  GTEST_ASSERT_EQ(test_1.size(), test_2.size());
  for (int i = test_1.size(); i > 0; i--) {
    GTEST_ASSERT_EQ(test_1.top(), test_2.top());
    test_1.pop();
    test_2.pop();
  }
}

TEST(constr, move) {
  stack<int> test_1{1, 2, 3, 4, 5};
  stack<int> test_2(std::move(test_1));
  GTEST_ASSERT_EQ(test_2.size(), 5);
  for (int i = test_2.size(); i > 0; i--) {
    GTEST_ASSERT_EQ(i, test_2.top());
    test_2.pop();
  }
}

TEST(equal, overload_lvalue_1) {
  stack<int> testa{1, 2, 3};
  stack<int> b2;
  b2 = testa;
  GTEST_ASSERT_EQ(b2.size(), testa.size());
  for (int i = b2.size(); i > 0; i--) {
    GTEST_ASSERT_EQ(b2.top(), testa.top());
    b2.pop();
    testa.pop();
  }
}

TEST(equal, overload_lvalue_2) {
  stack<int> testa{1, 2, 3};
  testa = testa;
  GTEST_ASSERT_EQ(3, testa.size());
  for (int i = testa.size(); i > 0; i--) {
    GTEST_ASSERT_EQ(i, testa.top());
    testa.pop();
  }
}

TEST(equal, overload_rvalue_1) {
  stack<int> testa{1, 2, 3};
  stack<int> b2;
  b2 = std::move(testa);
  GTEST_ASSERT_EQ(0, testa.size());
  GTEST_ASSERT_EQ(3, b2.size());
  for (int i = b2.size(); i > 0; i--) {
    GTEST_ASSERT_EQ(b2.top(), i);
    b2.pop();
  }
}

TEST(equal, overload_rvalue_2) {
  stack<int> testa{1, 2, 3};
  testa = std::move(testa);
  GTEST_ASSERT_EQ(3, testa.size());
  for (int i = testa.size(); i > 0; i--) {
    GTEST_ASSERT_EQ(testa.top(), i);
    testa.pop();
  }
}

TEST(func, size_1) {
  stack<int> testa;
  GTEST_ASSERT_EQ(testa.size(), 0);
}

TEST(func, size_2) {
  stack<int> testa{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(testa.size(), 5);
}

TEST(func, top_1) {
  stack<int> testa{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(testa.top(), 5);
}

TEST(func, empty_1) {
  stack<int> testa{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(testa.empty(), 0);
}

TEST(func, empty_2) {
  stack<int> testa{};
  GTEST_ASSERT_EQ(testa.empty(), 1);
}

TEST(func, push_pop) {
  stack<int> testa;
  testa.push(1);
  testa.push(1);
  testa.push(1);
  testa.pop();
  testa.pop();
  testa.push(1);
  testa.pop();
  testa.pop();
  GTEST_ASSERT_EQ(testa.empty(), 1);
}

TEST(func, swap) {
  stack<int> test_5;
  stack<int> test_3{1, 2, 3};
  test_5.push(1);
  test_5.push(1);
  test_5.push(1);
  test_5.push(1);
  test_5.push(1);
  test_5.swap(test_3);
  GTEST_ASSERT_EQ(test_5.size(), 3);
  GTEST_ASSERT_EQ(test_3.size(), 5);
}

TEST(temp_func, free_stack) {
  stack<int> test{1, 2, 3, 4, 5};
  test.free_stack();
  GTEST_ASSERT_EQ(test.size(), 0);
  GTEST_ASSERT_EQ(test.empty(), 1);
}

TEST(extra_func, emplace_front_1) {
  stack<int> test{2, 3, 1};
  test.emplace_front(11, 22, 33);
  GTEST_ASSERT_EQ(test.size(), 6);
  GTEST_ASSERT_EQ(test.top(), 33);
  test.pop();
  GTEST_ASSERT_EQ(test.top(), 22);
  test.pop();
  GTEST_ASSERT_EQ(test.top(), 11);
  test.pop();
  GTEST_ASSERT_EQ(test.top(), 1);
  test.pop();
  GTEST_ASSERT_EQ(test.top(), 3);
  test.pop();
  GTEST_ASSERT_EQ(test.top(), 2);
}

TEST(extra_func, emplace_front_2) {
  stack<int> test{2, 3, 1};
  test.emplace_front(55);
  GTEST_ASSERT_EQ(test.size(), 4);
  GTEST_ASSERT_EQ(test.top(), 55);
  test.pop();
  GTEST_ASSERT_EQ(test.top(), 1);
  test.pop();
  GTEST_ASSERT_EQ(test.top(), 3);
  test.pop();
  GTEST_ASSERT_EQ(test.top(), 2);
  test.pop();
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
  return 0;
}
