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
    TVector <int> v(2);
    v[0] = 1;
    v[1] = 2;
    TVector<int>a = v;
    EXPECT_EQ(1, a[0]);
    EXPECT_EQ(2, a[1]);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
    TVector <int> v(2);
    TVector <int> a=v;
    EXPECT_NE(&a, &v);
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
    EXPECT_ANY_THROW(v[-1]=0);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
    TVector<int> v(4);
    EXPECT_ANY_THROW(v[MAX_VECTOR_SIZE+1] = 0);
}

TEST(TVector, can_assign_vector_to_itself)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    v = v;
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_TRUE(v == v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    TVector<int> b=v;
    EXPECT_EQ(1, b[0]);
    EXPECT_EQ(2, b[1]);
}

TEST(TVector, assign_operator_change_vector_size)
{
    TVector<int> v(2);
    v= TVector<int>(3);
    EXPECT_EQ(3, v.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
    TVector<int> v(2);
    TVector<int> w(3);
    v = w;
    EXPECT_EQ(3, v.GetSize());
}

TEST(TVector, compare_equal_vectors_return_true)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    TVector<int> w(2);
    w[0] = 1;
    w[1] = 2;
    EXPECT_EQ(w, v);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    EXPECT_TRUE(v==v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
    TVector<int> v(2);
    TVector<int> w(3);
    if (v==w){}
    EXPECT_NE(v, w);
}

TEST(TVector, can_add_scalar_to_vector)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    int a = 1;
    v = v + a;
    EXPECT_EQ(2, v[0]);
    EXPECT_EQ(3, v[1]);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    int a = 1;
    v = v - a;
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(1, v[1]);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    int a = 2;
    v = v * a;
    EXPECT_EQ(2, v[0]);
    EXPECT_EQ(4, v[1]);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    TVector<int> w(2);
    w[0] = 2;
    w[1] = 1;
    TVector<int> res(2);
    res = v + w;
    TVector<int> poo(2);
    poo[0] = 3;
    poo[1] = 3;
    EXPECT_EQ(poo, res);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
    TVector<int> v(2), w(1);
    ASSERT_ANY_THROW(v + w);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    TVector<int> w(2);
    w[0] = 1;
    w[1] = 1;
    TVector<int> res(2);
    res = v - w;
    TVector<int> poo(2);
    poo[0] = 0;
    poo[1] = 1;
    EXPECT_EQ(poo, res);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
    TVector<int> v(2), w(1);
    ASSERT_ANY_THROW(v - w);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    TVector<int> w(2);
    w[0] = 2;
    w[1] = 1;
    int res;
    res = v * w;
    int poo;
    poo = 4;
    EXPECT_EQ(poo, res);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
    TVector<int> v(2), w(1);
    ASSERT_ANY_THROW(v *w);
}

