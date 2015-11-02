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
	int size = 2;
	TVector<int> a(size);
	a[0] = 1;
	a[1] = 2;
	TVector<int> b=a;
	EXPECT_EQ(1, b[0]);
	EXPECT_EQ(2, b[1]);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	int size = 3;
	TVector<int> a(size);
	TVector<int> b=a;

	EXPECT_NE(&a, &b);
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

TEST(TVector, can_get_element_less_then_start_index) {
	TVector<int> v(2, 1);

	EXPECT_EQ(0, v[0]);
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	int size = 3;
	TVector<int> a(size);

	ASSERT_ANY_THROW(a[-1] = 0);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	int size = 3;
	TVector<int> a(size);

	ASSERT_ANY_THROW(a[MAX_VECTOR_SIZE+1] = 0);
}

TEST(TVector, can_assign_vector_to_itself)
{
	int size = 2;
	TVector<int> a(size);
	a[0] = 1;
	a[1] = 2;
	a = a;
	EXPECT_EQ(1, a[0]);
	EXPECT_EQ(2, a[1]);
	EXPECT_TRUE(a==a);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	int size = 3;
	TVector<int> a(size), b(size);
	for (int i = 0; i < size; i++) {
		a[i] = i;
	}
	b = a;

	EXPECT_EQ(0, b[0]);
	EXPECT_EQ(1, b[1]);
	EXPECT_EQ(2, b[2]);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> a(3);
	a = TVector<int>(4);

	EXPECT_EQ(4, a.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> a(3), b(2);
	b = a;

	EXPECT_EQ(3, b.GetSize());
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> a(2), b(2);
	a[0] = 0;
	a[1] = 1;
	b[0] = 0;
	b[1] = 1;

	EXPECT_TRUE(a == b);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> a(2);

	EXPECT_TRUE(a == a);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> a(2), b(4);
	if (a == b)
	{
		
	}
	EXPECT_NE(a, b);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> a(2);
	int b = 2;
	a[0] = 0;
	a[1] = 1;
	a = a+b;

	EXPECT_EQ(2, a[0]);
	EXPECT_EQ(3, a[1]);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> a(2);
	int b = 2;
	a[0] = 0;
	a[1] = 1;
	a = a-b;

	EXPECT_EQ(-2, a[0]);
	EXPECT_EQ(-1, a[1]);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> a(2);
	int b = 2;
	a[0] = 0;
	a[1] = 1;
	a = a*b;
	
	EXPECT_EQ(0, a[0]);
	EXPECT_EQ(2, a[1]);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> a(2), b(2);
	TVector<int> actual(2);
	TVector<int> expected(2);
	a[0] = 1;
	a[1] = 2;

	b[0] = 1;
	b[1] = 2;

	actual = a + b;

	expected[0] = 2;
	expected[1] = 4;

	EXPECT_EQ(expected, actual);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> a(2), b(3);
	
	ASSERT_ANY_THROW(a+b);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> a(2), b(2);
	TVector<int> actual(2);
	TVector<int> expected(2);
	a[0] = 2;
	a[1] = 4;

	b[0] = 1;
	b[1] = 3;

	actual = a - b;

	expected[0] = 1;
	expected[1] = 1;

	EXPECT_EQ(expected, actual);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> a(2), b(3);

	ASSERT_ANY_THROW(a - b);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> a(2), b(2);
	int actual;
	int expected;
	a[0] = 2;
	a[1] = 4;

	b[0] = 1;
	b[1] = 3;

	actual = a * b;

	expected = 14;

	EXPECT_EQ(expected, actual);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> a(2), b(3);

	ASSERT_ANY_THROW(a*b);
}

