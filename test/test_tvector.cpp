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
	TVector<int> a(3);
	a[0] = 0;
	a[1] = 1;
	a[2] = -23;
	TVector<int> b(a);
	EXPECT_EQ(0, b[0]);
	EXPECT_EQ(1, b[1]);
	EXPECT_EQ(-23, b[2]);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> a(1);
	a[0] = 0;
	TVector<int> b(a);
	EXPECT_NE(&a[0], &b[0]);
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
	EXPECT_NO_THROW(v[0] = 4);
	EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(3);
	EXPECT_ANY_THROW(v[-1] = 0);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(3);
	EXPECT_ANY_THROW(v[4] = 0);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> v(2);
	v[0] = 0;
	v[1] = 7;
	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(0, v[0]);
	EXPECT_EQ(7, v[1]);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> a(2), b(2);
	a[0] = 0;
	a[1] = 7;
	EXPECT_NO_THROW(a = b);
	EXPECT_EQ(a[0], b[0]);
	EXPECT_EQ(a[1], b[1]);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> a(2), b(1);
	b = a;
	EXPECT_EQ(2, b.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> a(3), b(1);
	a[0] = 0;
	a[1] = 7;
	a[2] = -1;
	b = a;
	EXPECT_EQ(0, b[0]);
	EXPECT_EQ(7, b[1]);
	EXPECT_EQ(-1, b[2]);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> a(2), b(2);
	a[0] = b[0] = 0;
	a[1] = b[1] = 7;
	EXPECT_TRUE(a == b);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> v(2);
	v[0] = 0;
	v[1] = 7;
	EXPECT_TRUE(v == v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> a(2), b(3);
	a[0] = a[1] = b[0] = b[1] = b[2] = 0;
	EXPECT_FALSE(a == b);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v(2);
	v[0] = 0;
	v[1] = 7;
	v = v + 1;
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(8, v[1]);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v(2);
	v[0] = 0;
	v[1] = 7;
	v = v - 1;
	EXPECT_EQ(-1, v[0]);
	EXPECT_EQ(6, v[1]);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v(2);
	v[0] = -1;
	v[1] = 7;
	v = v * 3;
	EXPECT_EQ(-3, v[0]);
	EXPECT_EQ(21, v[1]);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> a(3), b(3), c(3);
	a[0] = 0;
	a[1] = 7;
	a[2] = -1;
	b[0] = 7;
	b[1] = -7;
	b[2] = 0;
	EXPECT_NO_THROW(a + b);
	c = a + b;
	EXPECT_EQ(7, c[0]);
	EXPECT_EQ(0, c[1]);
	EXPECT_EQ(-1, c[2]);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> a(1), b(2);
	a[0] = b[0] = b[1] = 0;
	ASSERT_ANY_THROW(a + b);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> a(3), b(3), c(3);
	a[0] = 7;
	a[1] = 7;
	a[2] = 7;
	b[0] = 1;
	b[1] = 2;
	b[2] = 3;
	EXPECT_NO_THROW(a - b);
	c = a - b;
	EXPECT_EQ(6, c[0]);
	EXPECT_EQ(5, c[1]);
	EXPECT_EQ(4, c[2]);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> a(1), b(2);
	a[0] = b[0] = b[1] = 0;
	ASSERT_ANY_THROW(a - b);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> a(3), b(3);
	int c;
	a[0] = 7;
	a[1] = 0;
	a[2] = -1;
	b[0] = -1;
	b[1] = 7;
	b[2] = -1;
	EXPECT_NO_THROW(a * b);
	c = a * b;
	EXPECT_EQ(-6, c);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> a(1), b(2);
	a[0] = b[0] = b[1] = 0;
	ASSERT_ANY_THROW(a * b);
}

