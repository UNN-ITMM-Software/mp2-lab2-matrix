#include "MyMatrix.h"

#include <../gtest/gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, can_create_copied_matrix)
{
	TMatrix<int> m(5);

	ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m(5);
	TMatrix<int>m1(m);
	EXPECT_EQ(m, m1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int>A(5);
	TMatrix<int>B(A);
	EXPECT_NE(A.GetVector(), B.GetVector());
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int>Res(10);
	EXPECT_EQ(Res.GetSize(), 10);
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int>Res(10);
	Res[1][0] = 2;
	EXPECT_EQ(Res[1][0], 2);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int>res(1);
	ASSERT_ANY_THROW(res[-1][-2]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int>res(MAX_MATRIX_SIZE);
	ASSERT_ANY_THROW(res[MAX_MATRIX_SIZE + 3]);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int>A(10);
	TMatrix<int>B(1);
	B = A;
	EXPECT_EQ(B.GetSize(), 10);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int>A(10);
	EXPECT_EQ(A, A);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int>A(10);
	TMatrix<int>B(1);
	EXPECT_NE(A, B);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int>A(10);
	TMatrix<int>B(10);
	ASSERT_NO_THROW(A + B);
}


TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int>A(10);
	TMatrix<int>B(11);
	ASSERT_ANY_THROW(A + B);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int>A(10);
	TMatrix<int>B(20);
	ASSERT_ANY_THROW(A - B);
}