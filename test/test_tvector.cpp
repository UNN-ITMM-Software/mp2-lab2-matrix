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
	TVector<int> tVector(3);
	TVector<int> tVector_(tVector);
	EXPECT_TRUE(tVector == tVector_);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> tVector(3);
	TVector<int> tVector_(tVector);
	EXPECT_TRUE(&tVector != &tVector_);
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
	TVector<int> v(1);
	ASSERT_ANY_THROW(v[-1]);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(1);
	ASSERT_ANY_THROW(v[2]);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> v(1);
	ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> v(1);
	TVector<int> v_(1);
	ASSERT_NO_THROW(v = v_);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> v(1);
	TVector<int> v_(2);
	v = v_;
	EXPECT_TRUE(v.GetSize() == v_.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> v(1);
	TVector<int> v_(2);
	ASSERT_NO_THROW(v = v_);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> v(1);
	TVector<int> v_(v);
	EXPECT_TRUE(v == v_);
}

TEST(TVector, compare_vector_with_itself_return_true)
{

	TVector<int> v(1);
	EXPECT_TRUE(v == v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> v(1);
	TVector<int> v_(2);
	EXPECT_FALSE(v == v_);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v(1);
	ASSERT_NO_THROW(v + 2);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v(1);
	ASSERT_NO_THROW(v - 2);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v(1);
	ASSERT_NO_THROW(v*2);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
  TVector<int> v(1);
  TVector<int> v_(1);
  ASSERT_NO_THROW(v + v_);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
  TVector<int> v(1);
  TVector<int> v_(2);
  ASSERT_ANY_THROW(v + v_);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
  TVector<int> v(1);
  TVector<int> v_(2);
  ASSERT_ANY_THROW(v - v_);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
  TVector<int> v(1);
  TVector<int> v_(2);
  ASSERT_ANY_THROW(v - v_);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
  TVector<int> v(1);
  TVector<int> v_(2);
  ASSERT_ANY_THROW(v * v_);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
  TVector<int> v(1);
  TVector<int> v_(2);
  ASSERT_ANY_THROW(v * v_);
}

