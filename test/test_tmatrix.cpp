#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m1(4), m2(m1);
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m1(5);
	TMatrix<int> m2(m1);
	m1[0][0] = 1;
	m2[0][0] = 2;

	EXPECT_NE(&m1, &m2);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(5);

	EXPECT_EQ(m.GetSize(), 5);
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(5);
	m[0][0] = 5;

	EXPECT_EQ(5, m[0][0]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(4);
	ASSERT_ANY_THROW(m[-1][0]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(4);

	ASSERT_ANY_THROW(m[8][8]);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m1(2);
	m1[0][0] = 1;      
	m1[0][1] = 2;     
	m1[1][1] = 3;

	TMatrix<int> m2(m1);
	m1 = m1;
	EXPECT_EQ(m1, m2);
	
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> m1(5), m2(5);
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> m1(3), m2(5);
	m1 = m2;
	EXPECT_EQ(m1.GetSize(), 5);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> m1(3), m2(5);
	m1 = m2;
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m1(3), m2(3);
	
	m1[0][0] = 1;      
	m1[0][1] = 2;    
	m1[1][1] = 3;

	m2[0][0] = 1;      
	m2[0][1] = 2;    
	m2[1][1] = 3;

	ASSERT_TRUE(m1 == m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m(4);
	EXPECT_EQ(m, m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m1(5), m2(10);

	EXPECT_NE(m1, m2);
}
	
TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m1(2);
	TMatrix<int> m2(2);
	TMatrix<int> m3(2);
	TMatrix<int> add(2);

	m1[0][0] = 1;     
	m1[0][1] = 2;     
	m1[1][1] = 3;

	m2[0][0] = 4;     
	m2[0][1] = 5;    
	m2[1][1] = 6;

	m3[0][0] = 5;    
	m3[0][1] = 7;     
	m3[1][1] = 9;

	ASSERT_NO_THROW(m1 + m2);
	add = m1 + m2;
	EXPECT_EQ(add, m3);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m1(2), m2(3);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m1(2);
	TMatrix<int> m2(2);
	TMatrix<int> m3(2);
	TMatrix<int> add(2);

	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[1][1] = 3;

	m2[0][0] = 4;
	m2[0][1] = 5;
	m2[1][1] = 6;

	m3[0][0] = -3;
	m3[0][1] = -3;
	m3[1][1] = -3;

	ASSERT_NO_THROW(m1 - m2);
	add = m1 - m2;
	EXPECT_EQ(add, m3);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m1(2), m2(3);

	ASSERT_ANY_THROW(m1 - m2);
}

