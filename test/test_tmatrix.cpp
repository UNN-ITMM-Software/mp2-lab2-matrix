#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
  TMatrix<int> m(5);
  m[1][2] = 3;
  TMatrix<int> m1(m);

  EXPECT_EQ(m, m1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
  TMatrix<int> m(5);
  m[1][2] = 3;
  TMatrix<int> m1(m);
  m1[1][2] = 5;

  EXPECT_NE(m[1][2], m1[1][2]);
}

TEST(TMatrix, can_get_size)
{
  TMatrix<int> m(5);
  
  ASSERT_NO_THROW(m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
  TMatrix<int> m(5);
  m[1][2] = 3;
  
  EXPECT_EQ(3, m[1][2]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
  TMatrix<int> m(5);

  ASSERT_ANY_THROW(m[1][-2] = 3);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
  TMatrix<int> m(5);

  ASSERT_ANY_THROW(m[1][50] = 3);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
  TMatrix<int> m1(5), m2(5), expm(5);
  m1[1][1] = 5;
  expm[1][1] = 5;
  ASSERT_NO_THROW(m2 = m1);

  EXPECT_EQ(expm, m2);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
  TMatrix<int> m1(5), m2(10);
  m1[1][1] = 5;
  ASSERT_NO_THROW(m2 = m1);

  EXPECT_EQ(5, m2.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
  TMatrix<int> m1(5), m2(10), expm(5);
  m1[1][1] = 5;
  expm[1][1] = 5;
  ASSERT_NO_THROW(m2 = m1);

  EXPECT_EQ(expm, m2);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
  TMatrix<int> m1(5), m2(5);
  m1[1][1] = 5;
  m2[1][1] = 5;

  ASSERT_TRUE(m1 == m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
  TMatrix<int> m1(5);
  m1[1][1] = 5;

  ASSERT_TRUE(m1 == m1);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
  TMatrix<int> m1(5), m2(10);
  m1[1][1] = 5;
  m2[1][1] = 5;

  ASSERT_FALSE(m1 == m2);
  ASSERT_TRUE(m1 != m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
  TMatrix<int> m1(5), m2(5), expm(5);
  m1[5][5] = 2;
  m2[5][5] = 3;
  expm[5][5] = 5;

  EXPECT_EQ(expm, m1 + m2);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
  TMatrix<int> m1(5), m2(10), expm(10);
  m1[5][5] = 2;
  m2[5][5] = 3;
  m2[7][7] = 10;
  expm[5][5] = 5;
  expm[7][7] = 10;

  EXPECT_EQ(expm, m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
  TMatrix<int> m1(5), m2(5), expm(5);
  m1[5][5] = 2;
  m2[5][5] = 3;
  expm[5][5] = -1;

  EXPECT_EQ(expm, m1 - m2);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TMatrix<int> m1(5), m2(10), expm(10);
  m1[5][5] = 2;
  m2[5][5] = 3;
  m2[7][7] = 10;
  expm[5][5] = -1;
  expm[7][7] = -10;

  EXPECT_EQ(expm, m1 - m2);
}

