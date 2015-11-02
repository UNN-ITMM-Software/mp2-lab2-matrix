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
	TMatrix<int> m(3);

	m[1][1] = 1;

	TMatrix<int> m1(m);

	TMatrix<int> result(3);
	result[1][1] = 1;

	EXPECT_EQ(result, m1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m(3);
	m[1][1] = 1;

	TMatrix<int> m1(m);

	EXPECT_NE(&m, &m1);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> a(5);
	EXPECT_EQ(5, a.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(3);
	m[1][1] = 1;

	EXPECT_EQ(1, m[1][1]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(3);
	ASSERT_ANY_THROW(m[-1][-1]=0);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(3);
	ASSERT_ANY_THROW(m[MAX_VECTOR_SIZE+1][1] = 0);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m(3);
	m[0][0] = 1;
	m[1][1] = 2;
	m = m;
	EXPECT_EQ(1,m[0][0]);
	EXPECT_EQ(2, m[1][1]);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	int size = 3;
	TMatrix<int> a(size), b(size);
	for (int i = 0; i < size; i++) {
		a[i][i] = i;
	}
	b = a;

	EXPECT_EQ(0, b[0][0]);
	EXPECT_EQ(1, b[1][1]);
	EXPECT_EQ(2, b[2][2]);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> a(3);
	a = TMatrix<int>(4);

	EXPECT_EQ(4, a.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> a(3), b(2);
	b = a;

	EXPECT_EQ(3, b.GetSize());
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> a(3), b(3);
	EXPECT_TRUE(b == a);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> a(3);
	EXPECT_TRUE(a == a);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> a(3), b(2);
	EXPECT_FALSE(b == a);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> a(3);
	a[0][0] = 1;
	a[1][1] = 1;
	a[2][2] = 1;

	TMatrix<int> sum = a + a;

	TMatrix<int> result(3);
	result[0][0] = 2;
	result[1][1] = 2;
	result[2][2] = 2;
	EXPECT_EQ(result, sum);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> a(3),b(4);
	ASSERT_ANY_THROW(a+b);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> a(3), b(3);
	TMatrix<int> result(3);
	result[0][0] = 1;
	result[1][1] = 1;
	a[0][0] = 1;
	a[1][1] = 1;

	TMatrix<int> c = a - b;
	EXPECT_EQ(result, c);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> a(3), b(4);
	ASSERT_ANY_THROW(a - b);
}