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

	TMatrix<int> m1(5);
	TMatrix<int> m2(m1);
	EXPECT_EQ (m1,m2);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix <int> m1(5);
	TMatrix <int> m2= m1;
	EXPECT_NE(&m1, &m2);
}

TEST(TMatrix, can_get_size)
{
	TMatrix <int> m(5);
	EXPECT_EQ(5, m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix <int> m(5);
	m[1][1] = 0;
	EXPECT_EQ(0, m[1][1]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix <int> m(5);
	ASSERT_ANY_THROW (m[-1][-1] = 5);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix <int> m(5);
	ASSERT_ANY_THROW (m[MAX_VECTOR_SIZE + 1][MAX_VECTOR_SIZE + 1] = 5);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix <int> m(2);
	//m[0][0] = 0;
	//m[0][1] = 1;
	//m[1][0] = 2;
	//m[1][1] = 3;
	//m = m;
	//EXPECT_EQ(0, m[0][0]);
	//EXPECT_EQ(1, m[0][1]);
	//EXPECT_EQ(2, m[1][0]);
	//EXPECT_EQ(3, m[1][1]);
	ASSERT_NO_THROW(m == m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix <int> m(2);
	m[0][0] = 0;
	m[0][1] = 1;
	//m[1][0] = 2;
	m[1][1] = 3;
	TMatrix <int> n(2);
	n = m;
	EXPECT_EQ(0, n[0][0]);
	EXPECT_EQ(1, n[0][1]);
	//EXPECT_EQ(2, n[1][0]);
	EXPECT_EQ(3, n[1][1]);

}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix <int> m(2);
	m = TMatrix <int>(3);
	EXPECT_EQ(3, m.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix <int> m(2);
	TMatrix <int> n(3);
	m= n;
	EXPECT_EQ(3, m.GetSize());
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m(2);
	m[0][0] = 0;
	m[0][1] = 1;
	//m[1][0] = 2;
	m[1][1] = 3;
	TMatrix<int> n(2);
	n[0][0] = 0;
	n[0][1] = 1;
	//n[1][0] = 2; //не нужно. тк верхнетреугольная матрица
	n[1][1] = 3;
	EXPECT_EQ(m, n);
	//EXPECT_TRUE(m==n);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m(2);
	//m[0][0] = 0;
	//m[0][1] = 1;
	//m[1][0] = 2;
	//m[1][1] = 3;
	EXPECT_TRUE(m == m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m(2);
	TMatrix<int> n(3);
	EXPECT_NE(m, n);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m(2);
	m[0][0] = 0;
	m[0][1] = 1;
	//m[1][0] = 2;
	m[1][1] = 3;
	TMatrix<int> n(2);
	n[0][0] = 0;
	n[0][1] = 1;
	//n[1][0] = 2;
	n[1][1] = 3;
	TMatrix<int> res(2);
	res = m + n;
	TMatrix<int> poo(2);
	poo[0][0] = 0;
	poo[0][1] = 2;
	//poo[1][0] = 4;
	poo[1][1] = 6;
	EXPECT_EQ(poo, res);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m(2), n(1);
	ASSERT_ANY_THROW(m + n);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m(2);
	m[0][0] = 0;
	m[0][1] = 1;
	//m[1][0] = 2;
	m[1][1] = 3;
	TMatrix<int> n(2);
	n[0][0] = 0;
	n[0][1] = 1;
	//n[1][0] = 2;
	n[1][1] = 3;
	TMatrix<int> res(2);
	res = m - n;
	TMatrix<int> poo(2);
	poo[0][0] = 0;
	poo[0][1] = 0;
	//poo[1][0] = 0;
	poo[1][1] = 0;
	EXPECT_EQ(poo, res);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m(2), n(1);
	ASSERT_ANY_THROW(m - n);
}



//умножение????????????????
