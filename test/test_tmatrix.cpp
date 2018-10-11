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
	for (int i = 0; i < 5; ++i)
		m[i] = 4;
	TMatrix<int> m1(m);
	EXPECT_EQ(m, m1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m(5);
	TMatrix<int> m1(m);
	EXPECT_NE(&m, &m1);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(5);
	EXPECT_EQ(5, m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(5);
	m[2] = 14;
	EXPECT_EQ(m[2], 14);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[-1] = 10);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[MAX_MATRIX_SIZE + 1] = 10);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	const int size = 2;
	TMatrix<int> a(size);
	for (int i = 0; i < size; ++i)
		a[i] = 1;
	a = a;
	EXPECT_EQ(a[0], 1);
	EXPECT_EQ(a[1], 1);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	const int size = 2;
	TMatrix<int> a(size), b(size);
	for (int i = 0; i < size; ++i)
		a[i] = 1;
	b = a;
	EXPECT_EQ(b[0],1);
	EXPECT_EQ(b[1], 1);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	const int size = 2, size1 = 3;
	TMatrix<int> a(size), b(size1);
	for (int i = 0; i < size; ++i)
		a[i] = 1;
	b = a;
	EXPECT_EQ(2, b.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	const int size = 2, size1 = 3;
	TMatrix<int> a(size), b(size1);
	for (int i = 0; i < size; ++i)
		a[i] = 1;

	b = a;
	EXPECT_EQ(a, b);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	const int size = 2;
	TMatrix<int> a(size), b(size);
	for (int i = 0; i < size; ++i) {
		a[i] = 1;
		b[i] = 1;
	}
	EXPECT_TRUE(a == b);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	const int size = 2;
	TMatrix<int> a(size);
	for (int i = 0; i < size; ++i)
		a[i] = 1;
	EXPECT_TRUE(a == a);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	const int size = 2;
	TMatrix<int> a(size), b(size + 1);
	for (int i = 0; i < size; ++i) {
		a[i] = 1;
		b[i] = 1;
	}
	EXPECT_TRUE(a != b);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TVector<int> o(2);
	TVector<int> o1(2);
	for (int i = 0; i < 2; ++i) {
		o[i] = 1;
		o1[i] = 2;
	}
	TMatrix<int> a(10);
	TMatrix<int> b(10);
	TMatrix<int> c(10);
	for (int i = 0; i < 10; ++i) {
		a[i] = TVector<int>(o);
		b[i] = TVector<int>(o);
		c[i] = TVector<int>(o1);
	}
	EXPECT_EQ(c, a + b);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> a(10);
	TMatrix<int> b(5);
	EXPECT_ANY_THROW(a + b);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TVector<int> o(5);
	TVector<int> o1(5);
	for (int i = 0; i < 5; ++i) {
		o[i] = 1;
		o1[i] = 2;
	}
	TMatrix<int> a(10);
	TMatrix<int> b(10);
	TMatrix<int> c(10);
	for (int i = 0; i < 10; ++i) {
		a[i] = TVector<int>(o1);
		b[i] = TVector<int>(o);
		c[i] = TVector<int>(o);
	}
	EXPECT_EQ(c, a - b);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> a(10);
	TMatrix<int> b(5);
	EXPECT_ANY_THROW(a - b);
}

