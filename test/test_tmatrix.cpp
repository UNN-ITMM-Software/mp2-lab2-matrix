#include "tmatrix.h"

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
  TDynamicMatrix<int> m(3);
  m[0][0] = 0; m[0][1] = 1; m[0][2] = 2;
  m[1][0] = 3; m[1][1] = 4; m[1][2] = 5;
  m[2][0] = 6; m[2][1] = 7; m[2][2] = 8;
  TDynamicMatrix<int> m1(m);
  EXPECT_EQ(m,m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 0; m[0][1] = 1; m[0][2] = 2;
  m[1][0] = 3; m[1][1] = 4; m[1][2] = 5;
  m[2][0] = 6; m[2][1] = 7; m[2][2] = 8;
  TDynamicMatrix<int> m1(m);
  EXPECT_NE(&m,&m1);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(10);

  EXPECT_EQ(10,m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 5;
  int val = m[0][0];

  EXPECT_EQ(m[0][0],5);
  EXPECT_EQ(m[0][0],val);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(3);
  ASSERT_ANY_THROW(m.at(-1).at(0));
  ASSERT_ANY_THROW(m.at(0).at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(3);
  ASSERT_ANY_THROW(m.at(10).at(0));
  ASSERT_ANY_THROW(m.at(0).at(10));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(3);
  ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m(3),m2(3);
  m[0][0] = 0; m[0][1] = 1; m[0][2] = 2;
  m[1][0] = 3; m[1][1] = 4; m[1][2] = 5;
  m[2][0] = 6; m[2][1] = 7; m[2][2] = 8;
  m2 = m;
  ASSERT_NO_THROW(m2 = m);
  EXPECT_EQ(m,m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m(3),m2(5);
  m2 = m;
  EXPECT_EQ(3,m2.size());
  EXPECT_EQ(3,m2[0].size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m(3),m2(2);
  m[0][0] = 0; m[0][1] = 1; m[0][2] = 2;
  m[1][0] = 3; m[1][1] = 4; m[1][2] = 5;
  m[2][0] = 6; m[2][1] = 7; m[2][2] = 8;
  m2 = m;
  ASSERT_NO_THROW(m2 = m);
  EXPECT_EQ(m,m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m(3),m2;
  m[0][0] = 0; m[0][1] = 1; m[0][2] = 2;
  m[1][0] = 3; m[1][1] = 4; m[1][2] = 5;
  m[2][0] = 6; m[2][1] = 7; m[2][2] = 8;
  m2 = m;
  EXPECT_TRUE(m==m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 0; m[0][1] = 1; m[0][2] = 2;
  m[1][0] = 3; m[1][1] = 4; m[1][2] = 5;
  m[2][0] = 6; m[2][1] = 7; m[2][2] = 8;
  EXPECT_TRUE(m==m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m(3), m2(5);
  EXPECT_TRUE(m!=m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(2),m2(2), res(2);
  m[0][0] = 0; m[0][1] = 1; m2[0][0] = 0; m2[0][1] = 1; res[0][0] = 0; res[0][1] = 2;
  m[1][0] = 2; m[1][1] = 3; m2[1][0] = 2; m2[1][1] = 3; res[1][0] = 4; res[1][1] = 6;
  EXPECT_EQ(m+m2,res);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m(3),m2(2);

  ASSERT_ANY_THROW(m + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(2),m2(2), res(2);
  m[0][0] = 0; m[0][1] = 1; m2[0][0] = 0; m2[0][1] = 1;
  m[1][0] = 2; m[1][1] = 3; m2[1][0] = 2; m2[1][1] = 3;
  EXPECT_EQ(m-m2,res);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m(3),m2(2);

  ASSERT_ANY_THROW(m - m2);
}

