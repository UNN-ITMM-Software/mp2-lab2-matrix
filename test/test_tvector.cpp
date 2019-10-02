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
	TVector<int> A(13);
	TVector<int> B(A);

	EXPECT_EQ(A, B);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
  ADD_FAILURE(); // Шо значит етот тест?
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
  TVector<int> v(13);
  v[1] = 1;

  EXPECT_EQ(v[1],1);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> A(13);

	ASSERT_ANY_THROW(A[-1] = 0);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> A(13);

	ASSERT_ANY_THROW(A[14] = 0);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> A(13);

	ASSERT_NO_THROW(A = A);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> A(13), B(13);
	A = B;

	EXPECT_EQ(A, B);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> A(12), B(13);
	A = B;

	EXPECT_EQ(13, A.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> A(13), B(13);
	A = B;

	EXPECT_EQ(A, B);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> A(13), B(13);
	for (int i = 0; i < 13; i++)
		A[i] = B[i] = i;

	EXPECT_EQ(A, B);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> A(13);

	EXPECT_EQ(A, A);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> A(12), B(13);
	for (int i = 0; i < 12; i++)
		A[i] = B[i] = i;

	EXPECT_EQ(1, B!=A);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> A(13), B(13);
	for (int i = 0; i < 13; i++)
		A[i] = 13;

	EXPECT_EQ(A, B+13);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> A(13), B(13);
	for (int i = 0; i < 13; i++)
		A[i] = -13;

	EXPECT_EQ(A, B - 13);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
  TVector<int> A(13), B(13);
  for (int i = 0; i < 13; i++)
  {
	  A[i] = 5;
	  B[i] = 10;
  }

  EXPECT_EQ(B, A*2);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> A(13), B(13), Res1(13);
	for (int i = 0; i < 13; i++)
	{
		A[i] = 5;
		B[i] = 10;
		Res1[i] = 15;
	}

	EXPECT_EQ(A+B, Res1);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> A(13), B(26);

	ASSERT_ANY_THROW(A+B);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> A(13), B(13), Res1(13);
	for (int i = 0; i < 13; i++)
	{
		A[i] = 15;
		B[i] = 10;
		Res1[i] = 5;
	}

	EXPECT_EQ(A - B, Res1);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> A(13), B(26);

	ASSERT_ANY_THROW(A - B);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> A(13), B(13);
	int Result = 0;
	for (int i = 0; i < 13; i++)
	{
		A[i] = 5;
		B[i] = 3;
		Result += A[i] * B[i];
	}

	EXPECT_EQ(195, Result);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> A(13), B(26);

	ASSERT_ANY_THROW(A * B);
}

