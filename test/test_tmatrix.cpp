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
  TMatrix<int> tMatrix(5);

  ASSERT_NO_THROW(TMatrix<int> tMatrix_(tMatrix));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> tMatrix(3); 
	TMatrix<int> tMatrix_(tMatrix);
	EXPECT_TRUE(tMatrix_ == tMatrix);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
  TMatrix<int> tMatrix(3);
  TMatrix<int> tMatrix_(tMatrix);

  EXPECT_TRUE(&tMatrix_ != &tMatrix);
}

TEST(TMatrix, can_get_size)
{
	TMatrix <int> tMatrix(5);
	EXPECT_EQ(5,tMatrix.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	int i;
	TMatrix<int> tMatrix(3);
	tMatrix[0][2] = 7;
	i = tMatrix[0][2];
	EXPECT_EQ(7, i);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix <int> tMatrix(4);
	ASSERT_ANY_THROW (tMatrix[-2][-3]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{

	TMatrix<int> tMatrix(3);
	ASSERT_ANY_THROW(tMatrix[5] = 1);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix <int> tMatrix(5);
	ASSERT_NO_THROW (tMatrix = tMatrix);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> tMatrix(4);
	TMatrix<int> tMatrix_(4);
	ASSERT_NO_THROW(tMatrix = tMatrix_);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> tMatrix(3);
	TMatrix<int> tMatrix_(5);
	tMatrix = tMatrix_;
	EXPECT_TRUE(tMatrix.GetSize() == tMatrix_.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> tMatrix(5);
	TMatrix<int> tMatrix_(7);

	ASSERT_NO_THROW(tMatrix = tMatrix_);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix <int> tMatrix(3);
	TMatrix <int> tMatrix_(3);
	EXPECT_EQ(true,tMatrix == tMatrix_ );
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> tMatrix(3);
	EXPECT_TRUE(tMatrix == tMatrix);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix <int> tMatrix(4);
	TMatrix <int> tMatrix_(5);
	EXPECT_EQ(true, tMatrix != tMatrix_);	
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{

	TMatrix<int> tMatrix(1);
	TMatrix<int> tMatrix_(1);
	ASSERT_NO_THROW(tMatrix + tMatrix_);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix <int> tMatrix(1);
	TMatrix <int> tMatrix_(2);
	ASSERT_ANY_THROW(tMatrix + tMatrix_);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix <int> tMatrix(1);
	TMatrix <int> tMatrix_(1);
	ASSERT_NO_THROW(tMatrix - tMatrix_);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix <int> tMatrix(1);
	TMatrix <int> tMatrix_(2);
	ASSERT_ANY_THROW(tMatrix - tMatrix_);
}

