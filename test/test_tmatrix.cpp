// Copyright 2016 AuthorName. All rights reserved.
#include "utmatrix.h"
#include <gtest.h>
TEST(TMatrix, can_create_matrix_with_positive_length) {
  ASSERT_NO_THROW(TMatrix<int> m(5));
}
TEST(TMatrix, cant_create_too_large_matrix) {
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}
TEST(TMatrix, throws_when_create_matrix_with_negative_length) {
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}
TEST(TMatrix, can_create_copied_matrix) {
  TMatrix<int> m(5);
  ASSERT_NO_THROW(TMatrix<int> m1(m));
}
TEST(TMatrix, copied_matrix_is_equal_to_source_one) {
  TMatrix<int> matr(5), copyM;
  matr[1][1] = 199;
  TMatrix<int> copyMatr(matr);
  EXPECT_TRUE(matr[1][1] == copyMatr[1][1]);
}
TEST(TMatrix, copied_matrix_has_its_own_memory) {
  TMatrix<int> matr(5);
  TMatrix<int> copyMatr(5);
  copyMatr[1][1] = 199;
  EXPECT_TRUE(matr[1][1] != copyMatr[1][1]);
}
TEST(TMatrix, can_get_size) {
  TMatrix<int> matr(10);
  ASSERT_NO_THROW(matr.GetSize());
}
TEST(TMatrix, can_set_and_get_element) {
  TMatrix<int> matr(10);
  ASSERT_NO_THROW(matr[0][0] = 7);
  ASSERT_NO_THROW(matr[0][0]);
}
TEST(TMatrix, throws_when_set_element_with_negative_index) {
  TMatrix<int> matr(10);
  ASSERT_ANY_THROW(matr[-4][5]);
}
TEST(TMatrix, throws_when_set_element_with_too_large_index) {
  TMatrix<int> matr(10);
  ASSERT_ANY_THROW(matr[20][5] = 10);
}
TEST(TMatrix, can_assign_matrix_to_itself) {
  TMatrix<int> matr(10);
  matr[3][6] = 7;
  ASSERT_NO_THROW(matr = matr);
}
TEST(TMatrix, can_assign_matrices_of_equal_size) {
  TMatrix<int> matr(10), assignable(10);
  matr[4][4] = 12;
  ASSERT_NO_THROW(assignable = matr);
}
TEST(TMatrix, assign_operator_change_matrix_size) {
  TMatrix<int> matr(10), assignable(5);
  EXPECT_NE(matr.GetSize(), assignable.GetSize());
  ASSERT_NO_THROW(assignable = matr);
  EXPECT_EQ(matr.GetSize(), assignable.GetSize());
}
TEST(TMatrix, can_assign_matrices_of_different_size) {
  TMatrix<int> matr(10), assignable(5);
  ASSERT_NO_THROW(assignable = matr);
}
TEST(TMatrix, compare_equal_matrices_return_true) {
  TMatrix<int> matr(10),  assignable(5);
  matr[5][5] = 3829;
  assignable = matr;
  EXPECT_TRUE(assignable == matr);
}
TEST(TMatrix, compare_matrix_with_itself_return_true) {
  TMatrix<int> matr(10);
  matr[5][5] = 3829;
  EXPECT_TRUE(matr == matr);
}
TEST(TMatrix, matrices_with_different_size_are_not_equal) {
  TMatrix<int> matr(10),  assignable(5);
  matr[1][1] = assignable[1][1] = 3829;
  EXPECT_TRUE(assignable != matr);
}
TEST(TMatrix, can_add_matrices_with_equal_size) {
  TMatrix<int> matr(10), sub(10);
  matr[7][7] = 7;
  ASSERT_NO_THROW(matr - sub);
}
TEST(TMatrix, cant_add_matrices_with_not_equal_size) {
  TMatrix<int> matr(10),  assignable(5);
  matr[1][1] = assignable[1][1] = 3829;
  ASSERT_ANY_THROW(assignable + matr);
}
TEST(TMatrix, can_subtract_matrices_with_equal_size) {
  TMatrix<int> matr(10), sub(10);
  matr[7][7] = 7;
  ASSERT_NO_THROW(matr - sub);
}
TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size) {
  TMatrix<int> matr(10),  assignable(5);
  matr[1][1] = assignable[1][1] = 3829;
  ASSERT_ANY_THROW(assignable = assignable - matr);
}
