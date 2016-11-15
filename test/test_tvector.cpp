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
	TVector<int> f(10);
	f[4] = 7;
	TVector<int> s(f);
	EXPECT_EQ(f, s);
}

TEST(TVector, copied_vector_has_its_own_memory)
{	
	TVector<int> f(10);
	TVector<int> s(f);
	f[6] = 4;
	EXPECT_NE(f[6], s[6]);
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
	TVector<int> v(4);
	ASSERT_ANY_THROW(v[-1] = 7);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(4);
	ASSERT_ANY_THROW(v[7] = 7);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> v(4);
	ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> v1(4), v2(4);
	EXPECT_EQ(v1.GetSize(), v2.GetSize());
	v1[0] = 7;
	v2 = v1;
	EXPECT_EQ(v1.GetSize(), v2.GetSize());
	for(int i = 0; i < v1.GetSize(); i++)
		EXPECT_EQ(v1[i], v2[i]);
}

TEST(TVector, assign_operator_change_vector_size)
{
  	TVector<int> v1(7), v2(4);
	EXPECT_EQ(4, v2.GetSize());
	EXPECT_EQ(v1.GetSize(), 7);
	v1[0] = 7;
	v2 = v1;
	EXPECT_EQ(v1.GetSize(), v2.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
  	TVector<int> v1(7), v2(4);
	EXPECT_EQ(4, v2.GetSize());
	EXPECT_EQ(v1.GetSize(), 7);
	v1[0] = 7;
	v2 = v1;
	EXPECT_EQ(v1.GetSize(), v2.GetSize());
	for(int i = 0; i < v1.GetSize(); i++)
		EXPECT_EQ(v1[i], v2[i]);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> v1(4), v2(4);
	v2[0] = 14;
	v1 = v2;
	EXPECT_TRUE(v1 == v2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> v1(4);
	EXPECT_TRUE(v1 == v1);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> v1(4), v2(7);
	v2[0] = v1[0] = 14;
	EXPECT_FALSE(v1 == v2);
}

TEST(TVector, can_add_scalar_to_vector)
{
	const int vSize = 6, addVal = 7;
	TVector<int> v1(vSize), v2(vSize), res(vSize);
	for(int i = 0; i < v1.GetSize(); i++)
		v1[i] = i+1;
	v2 = v1;
	v1 = v1 + addVal;
	res = v1 - v2;
	for(int i = 0; i < res.GetSize(); i++)
		EXPECT_TRUE(addVal == res[i]);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	const int vSize = 6, addVal = 7;
	TVector<int> v1(vSize), v2(vSize), res(vSize);
	for(int i = 0; i < v1.GetSize(); i++)
		v1[i] = i+1;
	v2 = v1;
	v1 = v1 - addVal;
	res = v2 - v1;
	for(int i = 0; i < res.GetSize(); i++)
		EXPECT_EQ(addVal, res[i]);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	const int vSize = 6, mulVal = 7;
	TVector<int> v1(vSize), res(vSize);
	res = v1 * mulVal;
	for(int i = 0; i < res.GetSize(); i++)
		EXPECT_EQ(v1[i] * mulVal, res[i]);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	const int vSize = 6;
	TVector<int> v1(6), v2(6), res(6);
	for(int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i;
		v2[i] = 6 - i;
	}
	res = v1 + v2;
	for(int i = 0; i < res.GetSize(); i++)
		EXPECT_EQ(v1.GetSize(), res[i]);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> v1(4), v2(7), res(8);
	v1[0] = 2;
	v2[0] = 3;
	ASSERT_ANY_THROW(res = v1 + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	const int vSize = 6;
	TVector<int> v1(vSize), v2(vSize), res(vSize);
	for(int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = 0;
		v2[i] = i;
	}
	res = v2 - v1;
	for(int i = 0; i < res.GetSize(); i++)
		EXPECT_EQ(i, res[i]);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> v1(4), v2(7), res(8);
	v1[0] = 2;
	v2[0] = 3;
	ASSERT_ANY_THROW(res = v1 - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> v1(6), v2(6);
	int sum = 0;	
	for(int i = 0; i < 6; i++)
	{
		v1[i] = v2[i] = i; // 0*0 1*1 2*2 3*3
		sum += i*i; 
	}
	EXPECT_EQ(v1 * v2, sum);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v1(4), v2(7), res(8);
	v1[0] = 2;
	v2[0] = 3;
	ASSERT_ANY_THROW(res = v1 * v2);
}

