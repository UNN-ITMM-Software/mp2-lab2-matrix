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
//
TEST(TVector, copied_vector_is_equal_to_source_one)
{
  const int Size = 5;
  
  TVector<int>sv(Size);
  for(int i = 0; i < Size;i++)
	  sv[i] = i;


   TVector<int>cv(sv);

  
   EXPECT_EQ(sv,cv);

    
}
//
TEST(TVector, copied_vector_has_its_own_memory)
{
  const int Size = 10;
  TVector<int>*sv = new TVector<int>(Size);
  TVector<int>cv(*sv);

  delete sv;

  ASSERT_NO_THROW(cv[Size - 1]);


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
//
TEST(TVector, throws_when_set_element_with_negative_index)
{
  TVector<int>v(10);

  ASSERT_ANY_THROW(v[-5] = 6);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
  
  TVector<int>v(10);

  ASSERT_ANY_THROW(v[10] = 6);
}

TEST(TVector, can_assign_vector_to_itself)
{
  TVector<int>v1(5);
  ASSERT_NO_THROW(v1 = v1);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
  TVector<int>v1(5);
  TVector<int>v2(5);

  for(int i = 0 ; i <5;i++){
	  v1[i] = i;
	  v2[i] = i*i;
  }

  v1 = v2;
  EXPECT_EQ(v1,v2);
}
//
TEST(TVector, assign_operator_change_vector_size)
{
  TVector<int>v1(10);
  TVector<int>v2(5);

  v1 = v2;

  EXPECT_EQ(v1.GetSize(),v2.GetSize());
 
}

TEST(TVector, can_assign_vectors_of_different_size)
{
  TVector<int>v1(10);
  TVector<int>v2(5);

  for(int i = 0 ; i <5;i++){
	  v1[i] = i;
	  v2[i] = i*i;
  }
  v1 = v2;

  EXPECT_EQ(v1,v2);

  
}

TEST(TVector, compare_equal_vectors_return_true)
{
  TVector<int>v1(5);
  TVector<int>v2(5);

  for(int i = 0 ; i <5;i++){
	  v1[i] = i;
	  v2[i] = i;
  }

  EXPECT_EQ(v1 == v2 , true);

}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int>v1(5);
    for(int i = 0 ; i <5;i++)
	  v1[i] = i;

	EXPECT_EQ(v1 == v1,true);


  
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int>v(6);
	TVector<int>v1(10);
	EXPECT_NE(v,v1);
}
//
TEST(TVector, can_add_scalar_to_vector)
{
  
	TVector<int>v(5);

	for (int i = 0; i < 5; i++)
		v[i] = 0;

	

	v = v + 5;


	for(int i = 0; i < 5;i++)
		EXPECT_EQ(v[i],5);

}

TEST(TVector, can_subtract_scalar_from_vector)
{
  TVector<int>v(5);

  for (int i = 0; i < 5; i++)
	  v[i] = 0;


	v = v - 5;

	for(int i = 0; i < 5;i++)
		EXPECT_EQ(v[i],-5);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
  TVector<int> v(6);
  for (int i = 0; i < 6; i++)
  	  v[i] = 1;
	  
  int sc = 2;
   v = v * sc;
   for (int i = 0; i < 6; i++)
	 EXPECT_EQ(v[i], 2);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
  TVector<int>v(5), v1(5), res(5);
  for (int i = 0; i < 5; i++)
  {
	  v[i] = 1;
	  v1[i] = i;
  }
  res = v + v1;
  for (int i = 0; i < 5; i++)
	EXPECT_EQ(res[i], i+1); 
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
  TVector <int> v(5), v1(3);
  ASSERT_ANY_THROW(v + v1);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
  TVector<int>v(5), v1(5), res(5);
  for (int i = 0; i < 5; i++)
  {
	  v[i] = 1;
	  v1[i] = i;
  }
  res = v - v1;
  for (int i = 0; i < 5; i++)
	EXPECT_EQ(res[i], 1 - i );   
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
  TVector <int> v(5), v1(3);
  ASSERT_ANY_THROW(v - v1);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
   TVector<int> v(6);
  TVector<int> v1(6);
  for (int i = 0; i < 6; i++)
  {
	  v[i] = 1;
	  v1[i] = i;
  }
  int res;
  res = v * v1; 
  EXPECT_EQ(res, 15);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
 TVector <int> v(5), v1(3);
  ASSERT_ANY_THROW(v * v1);
}
