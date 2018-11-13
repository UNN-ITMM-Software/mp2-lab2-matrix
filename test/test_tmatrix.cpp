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
	TMatrix<int>  m0(2), m;
	m0[0][0] = 1;
	m0[0][1] = 2;
	m0[1][1] = 1;
	m = m0;

	EXPECT_EQ(m0, m);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> b;
	TMatrix<int> *m = new TMatrix<int>;
	(*m)[0][0] = 1;
	(*m)[0][1] = 2;
	(*m)[1][1] = 1;
	b = *m;
	delete m;
	EXPECT_EQ(1, b[0][0]);
	EXPECT_EQ(2, b[0][1]);
}

TEST(TMatrix, can_get_size)
{
	const int size = 3;
	TMatrix<int> a(size);
	EXPECT_EQ(size, a.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> a(2);
	EXPECT_NO_THROW(a[0][0] = 1);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> a(2);
	EXPECT_ANY_THROW(a[-1][0] = 1);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> a(2);
	EXPECT_ANY_THROW(a[MAX_MATRIX_SIZE][0] = 1);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> a(2);
	a[0][0] = 1;
	a[0][1] = 2;
	a[1][1] = 3;
	EXPECT_NO_THROW(a = a);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> a(2), b(2);
	a[0][0] = 1;
	a[0][1] = 2;
	a[1][1] = 3;
	b = a;
	EXPECT_NO_THROW(b = a);
	EXPECT_EQ(a[0][1], b[0][1]);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> a(2), b(3);
	a[0][0] = 1;
	a[0][1] = 2;
	a[1][1] = 3;
	b = a;
	EXPECT_EQ(b.GetSize(), a.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> a(2), b(1);
	a[0][0] = 1;
	a[0][1] = 1;
	a[1][1] = 1;
	b = a;
	EXPECT_NO_THROW(b = a);
	EXPECT_EQ(a[0][1], b[0][1]);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> a(2);
	a[0][0] = 1;
	a[0][1] = 2;
	a[1][1] = 3;
	TMatrix<int> b(a);
	EXPECT_EQ(1, a == b);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> a(2);
	a[0][0] = 1;
	a[0][1] = 2;
	a[1][1] = 3;
	EXPECT_EQ(1, a == a);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> a(2);
	TMatrix<int> b(3);
	EXPECT_EQ(0, a == b);
}

TEST(TMatrix, can_add_matrices_with_equal_size)   /// фикс оператор + и -
{
	const int n = 10;
	TMatrix<int> a(n), b(n), c(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			a[i][j] = i * 2 + j * 3;
			b[i][j] = i * 4 + j * 2;
			c[i][j] = 6 * i + 5 * j;
		}
	}
	EXPECT_NO_THROW(a + b);
	EXPECT_EQ(c, a + b);

}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> a(2), b(3);
	EXPECT_ANY_THROW(a + b);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size) /// фикс оператор + и -
{
	const int n = 3;
	TMatrix<int> a(n), b(n), c(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			b[i][j] = i * 2;
			a[i][j] = j * 3;
			c[i][j] = 3 * j - 2 * i;
		}
	}
	EXPECT_NO_THROW(a - b);
	EXPECT_EQ(c, a - b);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> a(2), b(3);
	EXPECT_ANY_THROW(a - b);
}
