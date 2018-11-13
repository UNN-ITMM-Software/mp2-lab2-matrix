#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
	ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
	TVector<int> v(10);

	ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> a(3), b;
	a[0] = 3;
	a[1] = 0;
	a[2] = 0;
	b = a;
	EXPECT_EQ(a, b);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> b;
	TVector<int> *a = new TVector<int>;

	(*a)[0] = 1;
	(*a)[1] = 2;
	(*a)[2] = 3;
	b = (*a);
	delete a;

	EXPECT_EQ(1, b[0]);
	EXPECT_EQ(3, b[2]);
}

TEST(TVector, can_get_size)
{
	TVector<int> v(4);

	EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
	TVector<int> v(4, 2);

	EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
	TVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> a(2);
	EXPECT_ANY_THROW(a[-1] = 3);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> a(3);
	EXPECT_ANY_THROW(a[MAX_VECTOR_SIZE] = 3);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> a(2);
	a[0] = 3;
	a[1] = 2;
	EXPECT_NO_THROW(a = a);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> a(2);
	a[0] = 1;
	a[1] = 2;
	TVector<int> b(2);
	EXPECT_NO_THROW(a = b);
	EXPECT_EQ(a[0], b[0]);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> a(3), b(1);
	b = a;
	EXPECT_EQ(b.GetSize(), 3);
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> a(1), b(2);
	EXPECT_NO_THROW(a = b);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> a(3), b(3);
	a[0] = 4;
	a[1] = 3;
	a[2] = 2;
	b = a;
	EXPECT_EQ(1, a == b);
	EXPECT_EQ(a[2], b[2]);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> a(1);
	a[0] = 3;
	EXPECT_EQ(1, a == a);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> a(1), b(2);
	EXPECT_NE(1, a == b);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> a(2), c;
	a[0] = 1;
	a[1] = 3;
	c = a + 1;
	EXPECT_NO_THROW(a + 1);
	EXPECT_EQ(c, a + 1);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> a(2), c;
	a[0] = 1;
	a[1] = 2;
	c = a - 1;
	EXPECT_NO_THROW(a - 1);
	EXPECT_EQ(c, a - 1);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> a(2), c;
	a[0] = 1;
	a[1] = 2;
	c = a * 2;
	EXPECT_NO_THROW(a * 2);
	EXPECT_EQ(c, a * 2);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	const int n = 10;
	TVector<int> a(n), b(n), c(n);
	for (int i = 0; i < n; i++)
	{
		a[i] = i + 3;
		b[i] = i * 10;
		c[i] = 11 * i + 3;
	}
	EXPECT_NO_THROW(a + b);
	EXPECT_EQ(c, a + b);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> a(1), b(2);
	a[0] = 1;
	b[0] = 2;
	b[1] = 3;
	EXPECT_ANY_THROW(a + b);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	const int n = 10;
	TVector<int> a(n), b(n), c(n);
	for (int i = 0; i < n; i++)
	{
		b[i] = i + 3;
		a[i] = i * 10;
		c[i] = 9 * i - 3;
	}
	EXPECT_NO_THROW(a - b);
	EXPECT_EQ(c, a - b);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> a(1), b(2);
	a[0] = 1;
	b[0] = 2;
	b[1] = 3;
	EXPECT_ANY_THROW(a - b);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	const int n = 10;
	int c = 0;
	TVector<int> a(n), b(n);
	for (int i = 0; i < n; i++)
	{
		a[i] = i + 3;
		b[i] = i * 10;
		c += (i + 3)*(i * 10);
	}
	EXPECT_NO_THROW(a + b);
	EXPECT_EQ(c, a * b);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> a(2), b(1);
	a[0] = 3;
	a[1] = 3;
	b[0] = 2;
	EXPECT_ANY_THROW(a * b);
}