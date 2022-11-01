#include "Matrix.h"
#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(5);
  m[0][0] = 4;
  m[1][3] = 76;
  TDynamicMatrix<int> v(m);
  EXPECT_EQ(4, v[0][0]);
  EXPECT_EQ(76, v[1][3]);
  EXPECT_EQ(true, v == m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(5);
  m[0][0] = 4;
  TDynamicMatrix<int> v(m);
  int* a = &(m[0][0]);
  int* b = &(v[0][0]);
  EXPECT_NE(a, b);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(5);
  EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(5);
  ASSERT_NO_THROW(m[0][0] = 4);
  EXPECT_EQ(4, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(-1).at(0));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(5).at(0));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(5);
  m[0][0] = 4;
  ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m(5), v(5);
  m[0][0] = 4;
  m[1][3] = 76;
  ASSERT_NO_THROW(v = m);
  EXPECT_EQ(4, v[0][0]);
  EXPECT_EQ(76, v[1][3]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m(5), v(7);
  ASSERT_NO_THROW(m = v);
  m = v;
  EXPECT_EQ(7, m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m(5), v(7);
  m[0][0] = 4;
  m[1][3] = 76;
  ASSERT_NO_THROW(m = v);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m(2), v(2);
  m[0][0] = 2;
  v[0][0] = 2;
  EXPECT_EQ(true, m == v);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(2);
  EXPECT_EQ(true, m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m(2), v(3);
  EXPECT_EQ(false, m == v);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(5), v(5);
  m[0][0] = 2;
  v[0][0] = 2;
  ASSERT_NO_THROW(m + v);
  m = m + v;
  EXPECT_EQ(4, m[0][0]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m(5), v(7);
  ASSERT_ANY_THROW(m + v);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(5), v(5);
  m[0][0] = 2;
  v[0][0] = 2;
  ASSERT_NO_THROW(m - v);
  m = m - v;
  EXPECT_EQ(0, m[0][0]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m(5), v(7);
  ASSERT_ANY_THROW(m - v);
}

TEST(TDynamicMatrix, can_multiplication_matrixes_with_equal_size)
{
  TDynamicMatrix<int> m(3), v(3);
  m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
  m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;
  m[2][0] = 7; m[2][1] = 8; m[2][2] = 9;

  v[0][0] = 11; v[0][1] = 12; v[0][2] = 13;
  v[1][0] = 14; v[1][1] = 15; v[1][2] = 16;
  v[2][0] = 17; v[2][1] = 18; v[2][2] = 19;

  ASSERT_NO_THROW(m * v);
  m = m * v;

  EXPECT_EQ(90, m[0][0]); 
  EXPECT_EQ(96, m[0][1]);
  EXPECT_EQ(102, m[0][2]);
  EXPECT_EQ(216, m[1][0]);
  EXPECT_EQ(231, m[1][1]);
  EXPECT_EQ(246, m[1][2]);
  EXPECT_EQ(342, m[2][0]);
  EXPECT_EQ(366, m[2][1]);
  EXPECT_EQ(390, m[2][2]);
}
