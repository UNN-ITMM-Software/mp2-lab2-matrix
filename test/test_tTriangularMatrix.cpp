#include "Triangular_matrix.h"
#include <gtest.h>

TEST(TTriangularDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TTriangularDynamicMatrix<int> m(5));
}

TEST(TTriangularDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TTriangularDynamicMatrix<int> m(MAX_TR_MATRIX_SIZE + 1));
}

TEST(TTriangularDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TTriangularDynamicMatrix<int> m(-5));
}

TEST(TTriangularDynamicMatrix, can_create_copied_matrix)
{
  TTriangularDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TTriangularDynamicMatrix<int> m1(m));
}

TEST(TTriangularDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TTriangularDynamicMatrix<int> m(5);
  m[0][0] = 1;
  m[1][1] = 2;
  TTriangularDynamicMatrix<int> v(m);
  EXPECT_EQ(1, v[0][0]);
  EXPECT_EQ(2, v[1][1]);
  EXPECT_EQ(true, v == m);
}

TEST(TTriangularDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TTriangularDynamicMatrix<int> m(5);
  m[0][0] = 4;
  TTriangularDynamicMatrix<int> v(m);
  int* a = &(m[0][0]);
  int* b = &(v[0][0]);
  EXPECT_NE(a, b);
}

TEST(TTriangularDynamicMatrix, can_get_size)
{
  TTriangularDynamicMatrix<int> m(5);
  EXPECT_EQ(5, m.size());
}

TEST(TTriangularDynamicMatrix, can_set_and_get_element)
{
  TTriangularDynamicMatrix<int> m(5);
  ASSERT_NO_THROW(m[0][0] = 4);
  EXPECT_EQ(4, m[0][0]);
}

TEST(TTriangularDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TTriangularDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(-1).at(0));
}

TEST(TTriangularDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TTriangularDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(5).at(0));
}

TEST(TTriangularDynamicMatrix, can_assign_matrix_to_itself)
{
  TTriangularDynamicMatrix<int> m(5);
  m[0][0] = 4;
  ASSERT_NO_THROW(m = m);
}

TEST(TTriangularDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TTriangularDynamicMatrix<int> m(5), v(5);
  m[0][0] = 4;
  m[1][0] = 76;
  ASSERT_NO_THROW(v = m);
  EXPECT_EQ(4, v[0][0]);
  EXPECT_EQ(76, v[1][0]);
}

TEST(TTriangularDynamicMatrix, assign_operator_change_matrix_size)
{
  TTriangularDynamicMatrix<int> m(5), v(7);
  ASSERT_NO_THROW(m = v);
  m = v;
  EXPECT_EQ(7, m.size());
}

TEST(TTriangularDynamicMatrix, can_assign_matrices_of_different_size)
{
  TTriangularDynamicMatrix<int> m(5), v(7);
  v[0][0] = 4;
  v[1][1] = 76;
  ASSERT_NO_THROW(m = v);
}

TEST(TTriangularDynamicMatrix, compare_equal_matrices_return_true)
{
  TTriangularDynamicMatrix<int> m(2), v(2);
  m[0][0] = 2;
  v[0][0] = 2;
  EXPECT_EQ(true, m == v);
}

TEST(TTriangularDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TTriangularDynamicMatrix<int> m(2);
  EXPECT_EQ(true, m == m);
}

TEST(TTriangularDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TTriangularDynamicMatrix<int> m(2), v(3);
  EXPECT_EQ(false, m == v);
}

TEST(TTriangularDynamicMatrix, can_add_matrices_with_equal_size)
{
  TTriangularDynamicMatrix<int> m(5), v(5);
  m[0][0] = 2;
  v[0][0] = 2;
  ASSERT_NO_THROW(m + v);
  m = m + v;
  EXPECT_EQ(4, m[0][0]);
}

TEST(TTriangularDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TTriangularDynamicMatrix<int> m(5), v(7);
  ASSERT_ANY_THROW(m + v);
}

TEST(TTriangularDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TTriangularDynamicMatrix<int> m(5), v(5);
  m[0][0] = 2;
  v[0][0] = 2;
  ASSERT_NO_THROW(m - v);
  m = m - v;
  EXPECT_EQ(0, m[0][0]);
}

TEST(TTriangularDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TTriangularDynamicMatrix<int> m(5), v(7);
  ASSERT_ANY_THROW(m - v);
}

TEST(TTriangularDynamicMatrix, can_multiplication_matrixes_with_equal_size)
{
  TTriangularDynamicMatrix<int> m(3), v(3);
  m[0][0] = 1;
  m[1][0] = 4; m[1][1] = 5;
  m[2][0] = 7; m[2][1] = 8; m[2][2] = 9;

  v[0][0] = 11;
  v[1][0] = 14; v[1][1] = 15; 
  v[2][0] = 17; v[2][1] = 18; v[2][2] = 19;

  ASSERT_NO_THROW(m * v);
  m = m * v;

  EXPECT_EQ(11, m[0][0]);
  EXPECT_EQ(114, m[1][0]);
  EXPECT_EQ(75, m[1][1]);
  EXPECT_EQ(342, m[2][0]);
  EXPECT_EQ(282, m[2][1]);
  EXPECT_EQ(171, m[2][2]);
}

TEST(TTriangularDynamicMatrix, can_output_triangular_matrixes_in_normal_form)
{
  std::cout << std::endl;
  TTriangularDynamicMatrix<int> a(3), b(3);
  a[0][0] = 1; a[1][0] = 2; a[1][1] = 3; a[2][0] = 4; a[2][1] = 5; a[2][2] = 6;
  b[0][0] = 7; b[1][0] = 8; b[1][1] = 9; b[2][0] = 10; b[2][1] = 11; b[2][2] = 12;

  TTriangularDynamicMatrix<int> c(3);

  c = a * b;

  std::cout << c;
}