#include "tmatrix.h"
#include <gtest.h>
#include "test_tVector.h"

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<int> v(5);
  for (int i = 0; i < 5; i++)
    v[i] = i + 1;
  TDynamicVector<int> b(v);
  EXPECT_EQ(true, b == v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(5);
  for (int i = 0; i < 5; i++)
    v[i] = i + 2;
  TDynamicVector<int> b(v);
  int* a = &(v[0]);
  int* c = &(b[0]);
  EXPECT_EQ(false, a == c);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(5);
  ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(5);
  ASSERT_ANY_THROW(v.at(5));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(5);
  v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4; v[4] = 5;
  v = v;
  ASSERT_NO_THROW();
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> a(5), b(5);
  a[0] = 0;
  a[1] = 1;
  b = a;
  EXPECT_EQ(0, b[0]);
  EXPECT_EQ(1, b[1]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> a(4), b(6);
  a = b;
  EXPECT_EQ(6, a.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> a(4), b(6);
  b[0] = 0;
  b[5] = 5;
  a = b;
  EXPECT_EQ(0, a[0]);
  EXPECT_EQ(5, a[5]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> a(5), b(5);
  a[0] = 0;
  b[0] = 0;
  EXPECT_EQ(true, a == b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(5);
  EXPECT_EQ(true, v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> a(4), b(6);
  EXPECT_EQ(false, a == b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(5);
  v[0] = 0;
  v = v + 1;
  EXPECT_EQ(1, v[0]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(5);
  v[0] = 0;
  v = v - 1;
  EXPECT_EQ(-1, v[0]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v(5);
  v[0] = 1;
  v = v * 5;
  EXPECT_EQ(5, v[0]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> a(5), b(5);
  a[0] = 0;
  b[0] = 1;
  a = a + b;
  EXPECT_EQ(1, a[0]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(4), b(6);
  ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> a(5), b(5);
  a[0] = 0;
  b[0] = 1;
  a = a - b;
  EXPECT_EQ(-1, a[0]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(4), b(6);
  ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> a(4), b(4);
  a[0] = 2; a[1] = 3; a[2] = 5; a[3] = 7;
  b[0] = 4; b[1] = 1; b[2] = 2; b[3] = 9;
  EXPECT_EQ(84, a * b);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(4), b(6);
  for (int i = 0; i < 4; i++)
    a[i] = i + 1;
  for (int i = 0; i < 6; i++)
    b[i] = i + 2;

  ASSERT_ANY_THROW(a * b);
}

TEST(TDynamicVector, can_use_vector_iterator)
{
  int n = 3;
  TDynamicVector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = i + 1;

  TDynamicVector<int> b = a;

  TDynamicVector<int> c;

  c = a + b;

  std::cout << c << std::endl;

  for (auto i = c.begin(); i != c.end(); ++i)
    std::cout << *i << " ";
  std::cout << std::endl;
}