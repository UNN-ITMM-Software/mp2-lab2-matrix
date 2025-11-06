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
  ADD_FAILURE();
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_get_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  ADD_FAILURE();
}

