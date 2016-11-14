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
 //
 TEST(TMatrix, copied_matrix_is_equal_to_source_one)
 {
 
 	TMatrix<int> M(5);
 
 	for (int i = 0; i < 5; i++)
 		M[i][i] = i;
 
 	TMatrix<int> MC(M);
 
 
 
 	EXPECT_EQ(M, MC);
 }
 //
 TEST(TMatrix, copied_matrix_has_its_own_memory)
 {
 	  const int Size = 10;
 	  TMatrix<int>*sm = new TMatrix<int>(Size);
 	  TMatrix<int>cm(*sm);
 	
 	  delete sm;
 	
 	  ASSERT_NO_THROW(cm[0][0]);
 }
 
 TEST(TMatrix, can_get_size)
 {
 	TMatrix<int> M(5);
 	EXPECT_EQ(M.GetSize(), 5);
 }
 
 TEST(TMatrix, can_set_and_get_element)
 {
 	TMatrix<int> M(5);
 
 	M[0][0] = 1;
 
 	EXPECT_EQ(M[0][0], 1);
   
 }
 
 TEST(TMatrix, throws_when_set_element_with_negative_index)
 {
 	TMatrix<int> M(5);
 
 	ASSERT_ANY_THROW(M[-2][-5]);
 }
 
 TEST(TMatrix, throws_when_set_element_with_too_large_index)
 {
 	TMatrix<int> M(5);
 
 	ASSERT_ANY_THROW(M[10][7]);
 }
 
 TEST(TMatrix, can_assign_matrix_to_itself)
 {
 	TMatrix<int> M(5);
 	ASSERT_NO_THROW(M = M);
 }
 
 TEST(TMatrix, can_assign_matrices_of_equal_size)
 {
 	TMatrix<int> M(5), M2(5);
 
 	for (int i = 0; i < 5; i++)
 		M[i][i] = i;
 
 	M2 = M;
 
 	EXPECT_EQ(M2, M);
 
 	
   
 }
 
 TEST(TMatrix, assign_operator_change_matrix_size)
 {
 	{
 		TMatrix<int>m1(10);
 		TMatrix<int>m2(5);
 
 		m1 = m2;
 
 		EXPECT_EQ(m1.GetSize(), m2.GetSize());
 	}
 }
 
 TEST(TMatrix, can_assign_matrices_of_different_size)
 {
 	TMatrix<int>m1(10);
 	TMatrix<int>m2(5);
 
 	for (int i = 0; i < 5; i++)
 		m2[i][i] = i;
 
 	m1 = m2;
 
 	EXPECT_EQ(m1, m2);
 
 
 }
 
 TEST(TMatrix, compare_equal_matrices_return_true)
 {
 	TMatrix<int>m1(5);
 	TMatrix<int>m2(5);
 
 	for (int i = 0; i < 5; i++) {
 		m2[i][i] = i;
 		m1[i][i] = i;
 
 	}
 
 	EXPECT_EQ(m1 == m2, true);
   
 }
 
 TEST(TMatrix, compare_matrix_with_itself_return_true)
 {
 	TMatrix<int>M(5);
 
 	EXPECT_EQ(M == M,true);
 }
 
 TEST(TMatrix, matrices_with_different_size_are_not_equal)
 {
 	TMatrix<int>m1(5);
 	TMatrix<int>m2(10);
 
 	EXPECT_NE(m1, m2);
   
 }
 
 TEST(TMatrix, can_add_matrices_with_equal_size)
 {
 	TMatrix<int>m1(5);
 	TMatrix<int>m2(5);
 	TMatrix<int>res(5);
 
 	for (int i = 0; i < 5; i++) {
 		m2[i][i] = 2;
 		m1[i][i] = 1;
 		
 
	}
 
 	res = m1 + m2;
 
 	for (int i = 0; i < 5; i++) {
 		EXPECT_EQ(res[i][i],3);
 	}
 
 
 }
 
 TEST(TMatrix, cant_add_matrices_with_not_equal_size)
 {
 	TMatrix<int>m1(5);
 	TMatrix<int>m2(10);
 
 	ASSERT_ANY_THROW(m1 + m2);
 }
 
 TEST(TMatrix, can_subtract_matrices_with_equal_size)
 {
 
 	TMatrix<int>m1(5);
 	TMatrix<int>m2(5);
 	TMatrix<int>res(5);
 
 	for (int i = 0; i < 5; i++) {
 		m2[i][i] = 2;
 		m1[i][i] = 1;
 
 
 	}
 
 	res = m1 - m2;
 
 	for (int i = 0; i < 5; i++) {
 		EXPECT_EQ(res[i][i], -1);
 	}
 
   
 }
 
 TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
 {
 	TMatrix<int>m1(5);
 	TMatrix<int>m2(10);
 
 	ASSERT_ANY_THROW(m1 - m2);
 }
 