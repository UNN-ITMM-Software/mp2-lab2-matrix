#include <../gtest/gtest.h> 
#include "MyVector.h"



TEST(TVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, can_create_vector_with_max_size)
{
	ASSERT_NO_THROW(TVector<int> v(MAX_VECTOR_SIZE));
}

TEST(TVector, can_create_vector_with_zero_size)
{
	ASSERT_NO_THROW(TVector<int> v(0));
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
	TVector<int>v1(10);
	TVector<int>v2(v1);
	EXPECT_EQ(v1, v2);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int>A(5);
	TVector<int>B(A);
	EXPECT_NE(A.GetVector(), B.GetVector());
}

TEST(TVector, can_set_and_get_element)
{
	TVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int>P(2);
	ASSERT_ANY_THROW(P[-1]);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int>A(10);
	TVector<int>B(12);
	EXPECT_NE(A, B);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int>A(3), B(3);
	A = A + 3;
	for (int i = B.GetStartIndex(); i < B.GetSize(); i++)
	{
		B[i] = 3;
	}
	EXPECT_EQ(A, B);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int>A(3), B(4);
	ASSERT_ANY_THROW(A + B);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int>A(4), B(5);

	ASSERT_ANY_THROW(A*B);
}
