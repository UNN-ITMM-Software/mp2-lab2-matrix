#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  //ASSERT_NO_THROW(TMatrix<int> m(5));
	ASSERT_NO_THROW(TMatrix<int> m(6));
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
  //ADD_FAILURE();
	TMatrix<int>m1(7);
	TMatrix<int>m2(m1);
	ASSERT_TRUE(m1 == m2);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
 // ADD_FAILURE();
	TMatrix<int>m1(7);
	TMatrix<int>m2(5);
	m1[0] = 1;
	EXPECT_EQ(m2[0][0], 0);
}

TEST(TMatrix, can_get_size)
{
 // ADD_FAILURE();
	TMatrix<int>m1(7);
	EXPECT_EQ(7, m1.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
  //ADD_FAILURE();
	TMatrix<int>m1(7);
	m1[1][2] = 1;
	EXPECT_EQ(m1[1][2], 1);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
 // ADD_FAILURE();
	TMatrix<int>m1(7);
	ASSERT_ANY_THROW(m1[1][-2]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
  //ADD_FAILURE();
	TMatrix<int>m1(7);
	ASSERT_ANY_THROW(m1[1][10]);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
  //ADD_FAILURE();
	TMatrix<int>m1(7);
	ASSERT_TRUE(m1 == m1);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
  //ADD_FAILURE();
	TMatrix<int>m1(7), m2(7);
	m1[0][0] = 1;
	m2 = m1;
	EXPECT_EQ(m2[0][0], 1);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
 // ADD_FAILURE();
	TMatrix<int>m1(5), m2(7);
	m2 = m1;
	EXPECT_EQ(m2.GetSize(), 5);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
  //ADD_FAILURE();
	TMatrix<int>m1(5), m2(7);
	m1[0][0] = 5;
	m2 = m1;
	EXPECT_EQ(m2[0][0], 5);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
  //ADD_FAILURE();
	TMatrix<int>m1(7), m2(7);
	m1[0][0] = 2;
	m2[0][0] = 2;
	EXPECT_TRUE(m1 == m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
  //ADD_FAILURE();
	TMatrix<int>m1(7), m2(7);
	m1[0][0] = 2;
	EXPECT_TRUE(m1 == m1);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
  //ADD_FAILURE();
	TMatrix<int>m1(2), m2(7);
	EXPECT_NE(m1, m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
 // ADD_FAILURE();
	TMatrix<int>m1(7), m2(7);
	m1[0][0] = 2;
	m2[0][0] = 5;
	ASSERT_TRUE(m1[0][0] + m2[0][0], 7);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
 // ADD_FAILURE();
	TMatrix<int>m1(5), m2(7);
	m1[0][0] = 2;
	m2[0][0] = 5;
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
 // ADD_FAILURE();
	TMatrix<int>m1(7), m2(7);
	m1[0][0] = 2;
	m2[0][0] = 5;
	ASSERT_TRUE(m2[0][0] - m1[0][0], 3);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  //ADD_FAILURE();
	TMatrix<int>m1(5), m2(7);
	m1[0][0] = 2;
	m2[0][0] = 5;
	ASSERT_ANY_THROW(m2 - m1);
}

