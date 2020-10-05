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
  TMatrix<int> m1(5);

  ASSERT_NO_THROW(TMatrix<int> m2(m1));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m1(5);
	TMatrix<int> m2(m1);

	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix <int> m1(5);
	for (int i = 0; i < 5; i++)
	{
		for (int j = i; j < 5; j++)
		{
			m1[i][j] = 1;
		}
	}
	m1[3][3] = 55;
	TMatrix <int> m2(m1);
	m2[3][3] = 5;

	EXPECT_NE(m1[3][3], m2[3][3]);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m1(5);

	EXPECT_EQ(m1.GetSize(), 5);
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m1(5);
	m1[1][1] = 5;

	EXPECT_EQ(m1[1][1], 5);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<double> m1(10);

	ASSERT_ANY_THROW(m1[-1][6] = 10);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
  TMatrix<int> m1(5);

  ASSERT_ANY_THROW(m1[0][10] = 1);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m1(5);

	ASSERT_NO_THROW(m1 = m1);
}

TEST(TMatrix, can_assign_matrices_of_equal_size) //может присваивать матрицу такого же размера
{
	TMatrix<int> m1(5);
	TMatrix<int> m2(5);
	m1[0][0] = 1;
	m1 = m2;

	EXPECT_EQ(m1 , m2);
}

TEST(TMatrix, assign_operator_change_matrix_size) //оператор присваивания может менять размер 
{
	TMatrix<int> m1(5);
	TMatrix<int> m2(6);
	m2 = m1;

	EXPECT_EQ(5, m2.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)// может присваивать матрицы разного размера
{

	TMatrix<int> m1(5);
	TMatrix<int> m2(6);
	m1[0][0] = 5;
	m2 = m1;

	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m1(5), m2(5);
	m1[1][1] = m2[1][1] = 1;

	EXPECT_TRUE(m1 == m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m1(5);
	m1[1][1] = 1;

	EXPECT_TRUE(m1 == m1);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m1(5);
	TMatrix<int> m2(7);

	EXPECT_FALSE(m1 == m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m1(5);
	TMatrix<int> m2(5);

	ASSERT_NO_THROW(m1 + m2);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m1(5);
	TMatrix<int> m2(7);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m1(5);
	TMatrix<int> m2(5);

	ASSERT_NO_THROW(m1 - m2);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m1(5);
	TMatrix<int> m2(7);

	ASSERT_ANY_THROW(m1 - m2);
}

