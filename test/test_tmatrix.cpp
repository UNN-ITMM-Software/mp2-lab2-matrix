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
    TMatrix<double> expected(26);
    TMatrix<double> actual = expected;

    EXPECT_EQ(expected, actual);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
    TMatrix<double> expected(26);
    TMatrix<double> actual = expected;

    EXPECT_NE(&expected, &actual);
}

TEST(TMatrix, can_get_size)
{
    int expected = 26;

    TMatrix<double> matrix(expected);
    int actual = matrix.GetSize();

    EXPECT_EQ(expected, actual);
}

TEST(TMatrix, can_set_and_get_element)
{
    int expected = 26;

    TMatrix<int> matrix(26);
    matrix[7][7] = expected;

    EXPECT_EQ(expected, matrix[7][7]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
    TMatrix<double> matrix(26);

    ASSERT_ANY_THROW(matrix[-1][-1] = 26);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
    TMatrix<double> matrix(26);

    ASSERT_ANY_THROW(matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = 26);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
    TMatrix<double> matrix(26);

    ASSERT_NO_THROW(matrix == matrix);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
    int expected0 = 0;
    int expected1 = 1;
    int expected2 = 2;

    TMatrix<int> matrix0(26);
    TMatrix<int> matrix1(26);
    matrix0[0][0] = expected0;
    matrix0[1][1] = expected1;
    matrix0[2][2] = expected2;
    matrix1 = matrix0;

    int actual0 = matrix1[0][0];
    int actual1 = matrix1[1][1];
    int actual2 = matrix1[2][2];

    EXPECT_EQ(expected0, actual0);
    EXPECT_EQ(expected1, actual1);
    EXPECT_EQ(expected2, actual2);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
    int expected = 2671;

    TMatrix<double> matrix(26);
    matrix = TMatrix<double>(expected);
    int actual = matrix.GetSize();

    EXPECT_EQ(expected, actual);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
    int expected = 26;

    TMatrix<double> matrix0(13);
    TMatrix<double> matrix1(expected);
    matrix0 = matrix1;
    int actual = matrix0.GetSize();

    EXPECT_EQ(expected, actual);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
    TMatrix<int> expected(2);
    expected[0][0] = 0;
    expected[0][1] = 1;
    expected[1][1] = 2;

    TMatrix<int> actual(2);
    actual[0][0] = 0;
    actual[0][1] = 1;
    actual[1][1] = 2;

    EXPECT_EQ(expected, actual);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
    TMatrix<double> matrix(26);
    EXPECT_TRUE(matrix == matrix);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
    TMatrix<int> matrix0(26);
    TMatrix<int> matrix1(2671);

    EXPECT_NE(matrix0, matrix1);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
    TMatrix<int> expected(2);
    expected[0][0] = 0;
    expected[0][1] = 2;
    expected[1][1] = 4;

    TMatrix<int> a(2), b(2);
    a[0][0] = 0; b[0][0] = 0;
    a[0][1] = 1; b[0][1] = 1;
    a[1][1] = 2; b[1][1] = 2;
    TMatrix<int> actual = a + b;

    EXPECT_EQ(expected, actual);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
    TMatrix<int> a(2), b(1);
    ASSERT_ANY_THROW(a + b);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
    TMatrix<int> expected(2);
    expected[0][0] = -0;
    expected[0][1] = -1;
    expected[1][1] = -2;

    TMatrix<int> a(2), b(2);
    a[0][0] = 0; b[0][0] = 0;
    a[0][1] = 1; b[0][1] = 2;
    a[1][1] = 2; b[1][1] = 4;
    TMatrix<int> actual = a - b;

    EXPECT_EQ(expected, actual);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TMatrix<int> a(2), b(1);
    ASSERT_ANY_THROW(a - b);
}

