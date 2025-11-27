#include "tmatrix.h"
#include <gtest.h>

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
    for (size_t i = 0; i < 5; i++)
        v[i] = i * 2 + 1;

    TDynamicVector<int> v1(v);
    EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    TDynamicVector<int> v1(v);
    v[0] = 100;

    EXPECT_NE(100, v1[0]);
    EXPECT_EQ(1, v1[0]);
}

TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(4);
    EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
    TDynamicVector<int> v(4);
    v[0] = 4;
    EXPECT_EQ(4, v[0]);

    v[1] = 10;
    EXPECT_EQ(10, v[1]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(3);
    ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(3);
    ASSERT_ANY_THROW(v.at(5));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    ASSERT_NO_THROW(v = v);

    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v1(3), v2(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v1(3), v2(5);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    v2 = v1;

    EXPECT_EQ(3, v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v1(3), v2(5);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    v2 = v1;

    EXPECT_EQ(v1, v2);
    EXPECT_EQ(3, v2.size());
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v1(3), v2(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 1; v2[1] = 2; v2[2] = 3;

    EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v1(3), v2(5);
    EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(3), expected(3);
    v[0] = 1; v[1] = 2; v[2] = 3;
    expected[0] = 4; expected[1] = 5; expected[2] = 6;

    TDynamicVector<int> result = v + 3;
    EXPECT_EQ(expected, result);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(3), expected(3);
    v[0] = 5; v[1] = 6; v[2] = 7;
    expected[0] = 2; expected[1] = 3; expected[2] = 4;

    TDynamicVector<int> result = v - 3;
    EXPECT_EQ(expected, result);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(3), expected(3);
    v[0] = 1; v[1] = 2; v[2] = 3;
    expected[0] = 2; expected[1] = 4; expected[2] = 6;

    TDynamicVector<int> result = v * 2;
    EXPECT_EQ(expected, result);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3), v2(3), expected(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;
    expected[0] = 5; expected[1] = 7; expected[2] = 9;

    TDynamicVector<int> result = v1 + v2;
    EXPECT_EQ(expected, result);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3), v2(5);
    ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3), v2(3), expected(3);
    v1[0] = 5; v1[1] = 7; v1[2] = 9;
    v2[0] = 1; v2[1] = 2; v2[2] = 3;
    expected[0] = 4; expected[1] = 5; expected[2] = 6;

    TDynamicVector<int> result = v1 - v2;
    EXPECT_EQ(expected, result);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3), v2(5);
    ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3), v2(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    int result = v1 * v2;
    EXPECT_EQ(32, result); 
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3), v2(5);
    ASSERT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVector, can_use_move_constructor)
{
    TDynamicVector<int> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    TDynamicVector<int> v2(std::move(v1));

    EXPECT_EQ(0, v1.size());
    EXPECT_EQ(3, v2.size());
    EXPECT_EQ(1, v2[0]);
    EXPECT_EQ(2, v2[1]);
    EXPECT_EQ(3, v2[2]);
}

TEST(TDynamicVector, can_use_move_assignment)
{
    TDynamicVector<int> v1(3), v2(2);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    v2 = std::move(v1);

    EXPECT_EQ(0, v1.size());
    EXPECT_EQ(3, v2.size());
    EXPECT_EQ(1, v2[0]);
    EXPECT_EQ(2, v2[1]);
    EXPECT_EQ(3, v2[2]);
}

TEST(TDynamicVector, can_use_swap)
{
    TDynamicVector<int> v1(3), v2(2);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5;

    swap(v1, v2);

    EXPECT_EQ(2, v1.size());
    EXPECT_EQ(3, v2.size());
    EXPECT_EQ(4, v1[0]);
    EXPECT_EQ(5, v1[1]);
    EXPECT_EQ(1, v2[0]);
    EXPECT_EQ(2, v2[1]);
    EXPECT_EQ(3, v2[2]);
}

TEST(TDynamicVector, input_output_operators_work)
{
    TDynamicVector<int> v(2);
    v[0] = 10;
    v[1] = 20;

    std::stringstream ss;
    ss << v;

    TDynamicVector<int> v2(2);
    ss >> v2;

    EXPECT_EQ(v, v2);
}

TEST(TDynamicVector, scalar_operations_with_double)
{
    TDynamicVector<double> v(2);
    v[0] = 1.5;
    v[1] = 2.5;

    TDynamicVector<double> result_add = v + 1.0;
    EXPECT_DOUBLE_EQ(2.5, result_add[0]);
    EXPECT_DOUBLE_EQ(3.5, result_add[1]);

    TDynamicVector<double> result_sub = v - 0.5;
    EXPECT_DOUBLE_EQ(1.0, result_sub[0]);
    EXPECT_DOUBLE_EQ(2.0, result_sub[1]);

    TDynamicVector<double> result_mul = v * 2.0;
    EXPECT_DOUBLE_EQ(3.0, result_mul[0]);
    EXPECT_DOUBLE_EQ(5.0, result_mul[1]);
}