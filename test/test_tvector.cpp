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
	TVector<int>P(2);
  ASSERT_ANY_THROW(P[-1]);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int>P(MAX_VECTOR_SIZE);
	ASSERT_ANY_THROW(P[MAX_VECTOR_SIZE]);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int>P(10);
	ASSERT_NO_THROW(P = P);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
  TVector<int>A(10);
  TVector<int>B(10);
  ASSERT_NO_THROW(A = B);
  EXPECT_EQ(A, B);
}

TEST(TVector, assign_operator_change_vector_size)
{
 TVector<int>A(3);
 TVector<int>B(4);
 A = B;
 EXPECT_EQ(A.GetSize(), B.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int>A(10);
	TVector<int>B(12);
	ASSERT_NO_THROW(A = B);
	EXPECT_EQ(A, B);
}

TEST(TVector, compare_equal_vectors_return_true)
{

	TVector<int>A(10);
	TVector<int>B(10);
	EXPECT_EQ(A, B);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int>A(10);
	EXPECT_EQ(A, A);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int>A(10);
	TVector<int>B(12);
	EXPECT_NE(A, B);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int>A(3),B(3);
	A = A + 3;
	for (int i = B.GetStartIndex(); i < B.GetSize(); i++)
	{
		B[i] = 3;
	}
	EXPECT_EQ(A, B);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int>A(3), B(3);
	A = A - 3;
	for (int i = B.GetStartIndex(); i < B.GetSize(); i++)
	{
		B[i] = -3;
	}
	EXPECT_EQ(A, B);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int>A(3), B(3);
	A = (A+1)*3;
	for (int i = B.GetStartIndex(); i < B.GetSize(); i++)
	{
		B[i] = 3;
	}
	EXPECT_EQ(A, B);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int>A(3), B(3),C(3);
	for (int i = 0; i < A.GetSize(); i++)
	{
		A[i] = i;
		B[i] = 2 * i;
		C[i] = 3 * i;
	}
	A = A + B;
	EXPECT_EQ(A, C);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int>A(3), B(4);
	ASSERT_ANY_THROW(A + B);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int>A(3), B(3), C(3);
	for (int i = 0; i < A.GetSize(); i++)
	{
		A[i] = i;
		B[i] = 2 * i;
		C[i] =  i;
	}
	B = B -A;
	EXPECT_EQ(A, C);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int>A(3), B(4);
	ASSERT_ANY_THROW(B-A);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<float>A(4), B(4);
	for (int i = 0; i < 4; i++)
	{
		A[i] = i;
		B[i] = i;
	}
	float sum = A * B;
	float sum1 = sqrt(14.0);
	EXPECT_EQ(sum1, sum);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int>A(4), B(5);
	
	ASSERT_ANY_THROW(A*B);
}

