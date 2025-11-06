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
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;

	TDynamicVector<int> v1(v);

	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;

	TDynamicVector<int> v1(v);
	v1[0] = 10;

	EXPECT_NE(v[0], v1[0]);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v1[0], 10);
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
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 3);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(3), v2(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;

	v2 = v1;

	EXPECT_EQ(v2[0], 1);
	EXPECT_EQ(v2[1], 2);
	EXPECT_EQ(v2[2], 3);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(3), v2(5);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;

	v2 = v1;

	EXPECT_EQ(v2.size(), 3);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(3), v2(5);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;

	v2 = v1;

	EXPECT_EQ(v2.size(), 3);
	EXPECT_EQ(v2[0], 1);
	EXPECT_EQ(v2[1], 2);
	EXPECT_EQ(v2[2], 3);
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
	expected[0] = 3; expected[1] = 4; expected[2] = 5;

	TDynamicVector<int> result = v + 2;

	EXPECT_EQ(result, expected);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3), expected(3);
	v[0] = 5; v[1] = 6; v[2] = 7;
	expected[0] = 3; expected[1] = 4; expected[2] = 5;

	TDynamicVector<int> result = v - 2;

	EXPECT_EQ(result, expected);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3), expected(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	expected[0] = 2; expected[1] = 4; expected[2] = 6;

	TDynamicVector<int> result = v * 2;

	EXPECT_EQ(result, expected);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), expected(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 4; v2[1] = 5; v2[2] = 6;
	expected[0] = 5; expected[1] = 7; expected[2] = 9;

	TDynamicVector<int> result = v1 + v2;

	EXPECT_EQ(result, expected);
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

	EXPECT_EQ(result, expected);
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
	int expected = 1 * 4 + 2 * 5 + 3 * 6; // 4 + 10 + 18 = 32

	EXPECT_EQ(result, expected);
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

	EXPECT_EQ(v2.size(), 3);
	EXPECT_EQ(v2[0], 1);
	EXPECT_EQ(v2[1], 2);
	EXPECT_EQ(v2[2], 3);
	EXPECT_EQ(v1.size(), 0); // После move исходный объект должен быть в валидном состоянии
}

TEST(TDynamicVector, can_use_move_assignment)
{
	TDynamicVector<int> v1(3), v2(5);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;

	v2 = std::move(v1);

	EXPECT_EQ(v2.size(), 3);
	EXPECT_EQ(v2[0], 1);
	EXPECT_EQ(v2[1], 2);
	EXPECT_EQ(v2[2], 3);
	EXPECT_EQ(v1.size(), 0); // После move исходный объект должен быть в валидном состоянии
}

TEST(TDynamicVector, can_create_vector_from_array)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);

	EXPECT_EQ(v.size(), 5);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 3);
	EXPECT_EQ(v[3], 4);
	EXPECT_EQ(v[4], 5);
}

TEST(TDynamicVector, can_use_swap)
{
	TDynamicVector<int> v1(3), v2(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 4; v2[1] = 5; v2[2] = 6;

	swap(v1, v2);

	EXPECT_EQ(v1[0], 4);
	EXPECT_EQ(v1[1], 5);
	EXPECT_EQ(v1[2], 6);
	EXPECT_EQ(v2[0], 1);
	EXPECT_EQ(v2[1], 2);
	EXPECT_EQ(v2[2], 3);
}

TEST(TDynamicVector, scalar_operations_create_new_vectors)
{
	TDynamicVector<int> v(2);
	v[0] = 1; v[1] = 2;

	TDynamicVector<int> result1 = v + 1;
	TDynamicVector<int> result2 = v - 1;
	TDynamicVector<int> result3 = v * 2;

	// Исходный вектор не должен измениться
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);

	// Результаты должны быть корректными
	EXPECT_EQ(result1[0], 2);
	EXPECT_EQ(result1[1], 3);
	EXPECT_EQ(result2[0], 0);
	EXPECT_EQ(result2[1], 1);
	EXPECT_EQ(result3[0], 2);
	EXPECT_EQ(result3[1], 4);
}

TEST(TDynamicVector, vector_operations_create_new_vectors)
{
	TDynamicVector<int> v1(2), v2(2);
	v1[0] = 1; v1[1] = 2;
	v2[0] = 3; v2[1] = 4;

	TDynamicVector<int> sum = v1 + v2;
	TDynamicVector<int> diff = v1 - v2;

	// Исходные векторы не должны измениться
	EXPECT_EQ(v1[0], 1);
	EXPECT_EQ(v1[1], 2);
	EXPECT_EQ(v2[0], 3);
	EXPECT_EQ(v2[1], 4);

	// Результаты должны быть корректными
	EXPECT_EQ(sum[0], 4);
	EXPECT_EQ(sum[1], 6);
	EXPECT_EQ(diff[0], -2);
	EXPECT_EQ(diff[1], -2);
}