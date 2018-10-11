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

	ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> mat1(1);
	mat1[0][0] = 0;
	TMatrix<int> mat2(mat1);
	mat1[0][0] = 1;
	ASSERT_NO_THROW(mat1 == mat2);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> mat(1);
	EXPECT_EQ(1, mat.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> mat(1);
	mat[0][0] = 1;
	EXPECT_TRUE(1 == mat[0][0]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> mat(1);
	ASSERT_ANY_THROW(mat[-1][-1]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(TMatrix<int> mat(MAX_MATRIX_SIZE + 1));
}
TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> mat(1);
	mat[0][0] = 1;
	ASSERT_NO_THROW(mat = mat);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> mat1(1);
	mat1[0][0] = 1;
	TMatrix<int>mat2(mat1);
	EXPECT_TRUE(mat1 == mat2);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix <int> mat1(1), mat2(2);
	mat1 = mat2;
	EXPECT_TRUE(2 == mat1.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix <int> mat1(1);
	mat1[0][0] = 1;
	TMatrix<int>mat2(2);
	ASSERT_NO_THROW(mat2 = mat1);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> mat1(1);
	mat1[0][0] = 1;
	TMatrix<int> mat2(mat1);
	ASSERT_TRUE(mat1 == mat2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> mat(1);
	mat[0][0] = 1;
	ASSERT_NO_THROW(mat = mat);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> mat1(1), mat2(2);
	ASSERT_NO_THROW(mat1 == mat2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix <int> mat1(2);
	TMatrix <int> mat2(2);
	TMatrix <int> sum(2);

	mat1[0][0] = 1;
	mat1[0][1] = 2;
	mat1[1][1] = 2;

	mat2[0][0] = 1;
	mat2[0][1] = 2;
	mat2[1][1] = 2;


	sum = mat1 + mat2;
	EXPECT_EQ(sum[0][0], 2);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix <int> mat1(1), mat2(2);
	ASSERT_ANY_THROW(mat1 + mat2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix <int> mat1(2);
	TMatrix <int> mat2(2);
	TMatrix <int> sum(2);

	mat1[0][0] = 1;
	mat1[0][1] = 2;
	mat1[1][1] = 2;


	mat2[0][0] = 1;
	mat2[0][1] = 2;
	mat2[1][1] = 2;


	sum = mat1 - mat2;
	EXPECT_EQ(sum[0][0], 0);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix <int> mat1(1), mat2(2);
	ASSERT_ANY_THROW(mat1 - mat2);
}

