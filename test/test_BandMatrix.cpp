#include "tBandMatrix.h"
#include <gtest.h>

TEST(TBandDynamicMatrix, can_create_matrix_with_positive_length_and_positive_width)
{
  ASSERT_NO_THROW(TBandDynamicMatrix<int> m(5, 3));
}

TEST(TBandDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TBandDynamicMatrix<int> m(MAX_BAND_MATRIX_SIZE + 1));
}

TEST(TBandDynamicMatrix, throws_when_create_matrix_with_negative_length_and_negative_width)
{
  ASSERT_ANY_THROW(TBandDynamicMatrix<int> m(-5, -3));
}

TEST(TBandDynamicMatrix, can_create_copied_matrix)
{
  TBandDynamicMatrix<int> a(5, 3);

  ASSERT_NO_THROW(TBandDynamicMatrix<int> b(a));
}

TEST(TBandDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TBandDynamicMatrix<int> a(5, 3);
  a[0][0] = 0;
  a[1][1] = 1;
  TBandDynamicMatrix<int> b(a);
  EXPECT_EQ(0, b[0][0]);
  EXPECT_EQ(1, b[1][1]);
  EXPECT_EQ(true, a == b);
}

TEST(TBandDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TBandDynamicMatrix<int> a(5, 3);
  a[0][0] = 0;
  TBandDynamicMatrix<int> b(a);
  int* x = &(a[0][0]);
  int* y = &(b[0][0]);
  EXPECT_NE(x, y);
}

TEST(TBandDynamicMatrix, can_get_size)
{
  TBandDynamicMatrix<int> m(5);
  EXPECT_EQ(5, m.size());
}

TEST(TBandDynamicMatrix, can_set_and_get_element)
{
  TBandDynamicMatrix<int> m(5, 3);
  ASSERT_NO_THROW(m[0][0] = 0);
  EXPECT_EQ(0, m[0][0]);
}

TEST(TBandDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TBandDynamicMatrix<int> m(5, 3);
  ASSERT_ANY_THROW(m.at(-1).at(0));
}

TEST(TBandDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TBandDynamicMatrix<int> m(5, 3);
  ASSERT_ANY_THROW(m.at(5).at(0));
}

TEST(TBandDynamicMatrix, can_assign_matrix_to_itself)
{
  TBandDynamicMatrix<int> m(5, 1);
  m[0][0] = 0;
  ASSERT_NO_THROW(m = m);
}

TEST(TBandDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TBandDynamicMatrix<int> a(5, 1), b(5, 1);
  a[0][0] = 0;
  a[0][1] = 1;
  ASSERT_NO_THROW(b = a);
  EXPECT_EQ(0, b[0][0]);
  EXPECT_EQ(1, b[0][1]);
  b[0][0] = 2;
  EXPECT_NE(2, a[0][0]);
}

TEST(TBandDynamicMatrix, assign_operator_change_matrix_size)
{
  TBandDynamicMatrix<int> a(5), b(7);
  ASSERT_NO_THROW(a = b);
  a = b;
  EXPECT_EQ(7, a.size());
}

TEST(TBandDynamicMatrix, can_assign_matrices_of_different_size)
{
  TBandDynamicMatrix<int> a(5), b(7);
  a[0][0] = 0;
  a[0][1] = 1;
  ASSERT_NO_THROW(a = b);
}

TEST(TBandDynamicMatrix, compare_equal_matrices_return_true)
{
  TBandDynamicMatrix<int> a(2), b(2);
  a[0][0] = 0;
  b[0][0] = 0;
  EXPECT_EQ(true, a == b);
}

TEST(TBandDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TBandDynamicMatrix<int> m(2);
  EXPECT_EQ(true, m == m);
}

TEST(TBandDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TBandDynamicMatrix<int> a(5), b(7);
  EXPECT_EQ(false, a == b);
}

TEST(TBandDynamicMatrix, can_add_matrices_with_equal_size)
{
  TBandDynamicMatrix<int> a(5), b(5);
  a[0][0] = 1;
  b[0][0] = 1;
  ASSERT_NO_THROW(a + b);
  a = a + b;
  EXPECT_EQ(2, a[0][0]);
}

TEST(TBandDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TBandDynamicMatrix<int> a(5), b(7);
  ASSERT_ANY_THROW(a + b);
}

TEST(TBandDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TBandDynamicMatrix<int> a(5), b(5);
  a[0][0] = 1;
  b[0][0] = 1;
  ASSERT_NO_THROW(a - b);
  a = a - b;
  EXPECT_EQ(0, a[0][0]);
}

TEST(TBandDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TBandDynamicMatrix<int> a(5), b(7);
  ASSERT_ANY_THROW(a - b);
}

TEST(TBandDynamicMatrix, can_output_lent_matrixes_in_normal_form)
{
  std::cout << std::endl;
  TBandDynamicMatrix<int> g(7, 3);
  g[0][0] = 1; g[0][1] = 2; g[0][2] = 3; g[0][3] = 4; g[0][4] = 5;
  g[1][0] = 6; g[1][1] = 7; g[1][2] = 8; g[1][3] = 9; g[1][4] = 10; g[1][5] = 11;
  g[2][0] = 12; g[2][1] = 13; g[2][2] = 14; g[2][3] = 15; g[2][4] = 16; g[2][5] = 17; g[2][6] = 18;
  g[3][0] = 19; g[3][1] = 20; g[3][2] = 21; g[3][3] = 22; g[3][4] = 23; g[3][5] = 24;
  g[4][0] = 25; g[4][1] = 26; g[4][2] = 27; g[4][3] = 28; g[4][4] = 29;

  std::cout << g;
}