#include "tmatrix.h"
#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(3);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m[i][j] = i * 3 + j;

    TDynamicMatrix<int> m1(m);
    EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(3);
    TDynamicMatrix<int> m1(m);

    m[0][0] = 100;
    EXPECT_NE(m[0][0], m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(5);
    EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(3);
    m[1][1] = 42;
    EXPECT_EQ(42, m[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(3);
    ASSERT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(3);
    ASSERT_ANY_THROW(m.at(5));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(3);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m[i][j] = i * 3 + j;

    ASSERT_NO_THROW(m = m);

    TDynamicMatrix<int> expected(3);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            expected[i][j] = i * 3 + j;

    EXPECT_EQ(expected, m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(3), m2(3);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m1[i][j] = i * 3 + j;

    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(3), m2(5);
    m2 = m1;
    EXPECT_EQ(3, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(3), m2(5);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m1[i][j] = i * 3 + j;

    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(3), m2(3);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++) {
            m1[i][j] = i * 3 + j;
            m2[i][j] = i * 3 + j;
        }

    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(3);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m[i][j] = i * 3 + j;

    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(3), m2(5);
    EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2), expected(2);

    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    m2[0][0] = 5; m2[0][1] = 6;
    m2[1][0] = 7; m2[1][1] = 8;

    expected[0][0] = 6; expected[0][1] = 8;
    expected[1][0] = 10; expected[1][1] = 12;

    TDynamicMatrix<int> result = m1 + m2;
    EXPECT_EQ(expected, result);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(3);
    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2), expected(2);

    m1[0][0] = 5; m1[0][1] = 6;
    m1[1][0] = 7; m1[1][1] = 8;

    m2[0][0] = 1; m2[0][1] = 2;
    m2[1][0] = 3; m2[1][1] = 4;

    expected[0][0] = 4; expected[0][1] = 4;
    expected[1][0] = 4; expected[1][1] = 4;

    TDynamicMatrix<int> result = m1 - m2;
    EXPECT_EQ(expected, result);
}

TEST(TDynamicMatrix, cant_subtract_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(3);
    ASSERT_ANY_THROW(m1 - m2);
}
/////////////////////////////////////////////////////////////////////////////////
// треугольная матрица

TEST(TUpperTriangularMatrix, BasicOperations) {
    // создание
    TUpperTriangularMatrix<int> m(3);
    EXPECT_EQ(3, m.size());

    // запись и чтение
    m.at(0, 0) = 1; m.at(0, 1) = 2; m.at(0, 2) = 3;
    m.at(1, 1) = 4; m.at(1, 2) = 5;
    m.at(2, 2) = 6;

    EXPECT_EQ(1, m.at(0, 0));
    EXPECT_EQ(4, m.at(1, 1));
    EXPECT_EQ(6, m.at(2, 2));
}

TEST(TUpperTriangularMatrix, AccessValidation) {
    TUpperTriangularMatrix<int> m(2);

    // валидный доступ
    EXPECT_NO_THROW(m.at(0, 0));
    EXPECT_NO_THROW(m.at(0, 1));
    EXPECT_NO_THROW(m.at(1, 1));

    // невалидный доступ (нижний треугольник)
    EXPECT_ANY_THROW(m.at(1, 0));
}

TEST(TUpperTriangularMatrix, ErrorHandling) {
    EXPECT_ANY_THROW(TUpperTriangularMatrix<int> m(0)); 

    TUpperTriangularMatrix<int> m(2);
    TDynamicVector<int> v(3);
    EXPECT_ANY_THROW(m * v); 
}
// тесты для ленточной матрицы
TEST(TBandMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TBandMatrix<int> m(5, 2));
}

TEST(TBandMatrix, throws_when_create_matrix_with_zero_length)
{
    ASSERT_ANY_THROW(TBandMatrix<int> m(0, 1));
}

TEST(TBandMatrix, throws_when_bandwidth_too_large)
{
    ASSERT_ANY_THROW(TBandMatrix<int> m(3, 3));
}

TEST(TBandMatrix, can_set_and_get_element_in_band)
{
    TBandMatrix<int> m(5, 1);
    ASSERT_NO_THROW(m.at(2, 2) = 42);
    EXPECT_EQ(42, m.at(2, 2));

    ASSERT_NO_THROW(m.at(2, 3) = 10);
    EXPECT_EQ(10, m.at(2, 3));
}

TEST(TBandMatrix, throws_when_set_element_outside_band)
{
    TBandMatrix<int> m(5, 1);
    ASSERT_ANY_THROW(m.at(0, 2));
    ASSERT_ANY_THROW(m.at(2, 0));
}
/*
TEST(TBandMatrix, can_multiply_by_vector)
{
    TBandMatrix<int> m(3, 1);
    m.at(0, 0) = 1; m.at(0, 1) = 2;
    m.at(1, 0) = 3; m.at(1, 1) = 4; m.at(1, 2) = 5;
    m.at(2, 1) = 6; m.at(2, 2) = 7;

    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    TDynamicVector<int> result = m * v;
    EXPECT_EQ(5, result[0]);   // 1*1 + 2*2 = 5
    EXPECT_EQ(26, result[1]);  // 3*1 + 4*2 + 5*3 = 26
    EXPECT_EQ(32, result[2]);  // 6*2 + 7*3 = 32
}*/
//тесты для CSR матрицы
TEST(TCSRMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TCSRMatrix<int> m(5));
}

TEST(TCSRMatrix, throws_when_create_matrix_with_zero_length)
{
    ASSERT_ANY_THROW(TCSRMatrix<int> m(0));
}

TEST(TCSRMatrix, can_convert_from_dense_matrix)
{
    TDynamicMatrix<int> dense(3);
    dense[0][0] = 1; dense[0][2] = 2;
    dense[1][1] = 3;
    dense[2][0] = 4; dense[2][2] = 5;

    ASSERT_NO_THROW(TCSRMatrix<int> csr(dense));

    TCSRMatrix<int> csr(dense);
    EXPECT_EQ(3, csr.size());
    EXPECT_EQ(5, csr.nonZeros());
}

TEST(TCSRMatrix, can_multiply_by_vector)
{
    TDynamicMatrix<int> dense(3);
    dense[0][0] = 1; dense[0][2] = 2;
    dense[1][1] = 3;
    dense[2][0] = 4; dense[2][2] = 5;

    TCSRMatrix<int> csr(dense);
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    TDynamicVector<int> result = csr * v;
    EXPECT_EQ(7, result[0]);   
    EXPECT_EQ(6, result[1]);   
    EXPECT_EQ(19, result[2]);  
}

TEST(TCSRMatrix, can_get_element)
{
    TDynamicMatrix<int> dense(2);
    dense[0][0] = 1; dense[0][1] = 2;
    dense[1][1] = 3;

    TCSRMatrix<int> csr(dense);
    EXPECT_EQ(1, csr.at(0, 0));
    EXPECT_EQ(2, csr.at(0, 1));
    EXPECT_EQ(0, csr.at(1, 0)); // Нулевой элемент
    EXPECT_EQ(3, csr.at(1, 1));
}

TEST(TCSRMatrix, can_set_element)
{
    TCSRMatrix<int> csr(2);
    csr.set(0, 0, 1);
    csr.set(0, 1, 2);
    csr.set(1, 1, 3);

    EXPECT_EQ(1, csr.at(0, 0));
    EXPECT_EQ(2, csr.at(0, 1));
    EXPECT_EQ(3, csr.at(1, 1));

    // Установка нуля удаляет элемент
    csr.set(0, 1, 0);
    EXPECT_EQ(0, csr.at(0, 1));
}

TEST(TCSRMatrix, throws_when_set_element_with_invalid_index)
{
    TCSRMatrix<int> csr(2);
    ASSERT_ANY_THROW(csr.set(2, 0, 1));
    ASSERT_ANY_THROW(csr.set(0, 2, 1));
}

// Сравнение производительности разных форматов
TEST(MatrixFormats, multiplication_comparison)
{
    const size_t SIZE = 4; // Уменьшим размер для надежности

    // Плотная матрица
    TDynamicMatrix<int> dense(SIZE);
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            dense[i][j] = (i == j) ? 2 : ((abs((long)i - (long)j) == 1) ? 1 : 0);
        }
    }

    // ленточная матрица (трехдиагональная)
    TBandMatrix<int> band(SIZE, 1);
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            long diff = static_cast<long>(j) - static_cast<long>(i);
            if (diff >= -1 && diff <= 1) {
                if (i == j) band.at(i, j) = 2;
                else if (abs(diff) == 1) band.at(i, j) = 1;
            }
        }
    }

    // CSR матрица
    TCSRMatrix<int> csr(dense);

    TDynamicVector<int> v(SIZE);
    for (size_t i = 0; i < SIZE; i++) {
        v[i] = i + 1;
    }

    TDynamicVector<int> result_dense = dense * v;
    TDynamicVector<int> result_band = band * v;
    TDynamicVector<int> result_csr = csr * v;

    // отладочный вывод
    std::cout << "Dense result: ";
    for (size_t i = 0; i < SIZE; i++) std::cout << result_dense[i] << " ";
    std::cout << std::endl;

    std::cout << "Band result: ";
    for (size_t i = 0; i < SIZE; i++) std::cout << result_band[i] << " ";
    std::cout << std::endl;

    std::cout << "CSR result: ";
    for (size_t i = 0; i < SIZE; i++) std::cout << result_csr[i] << " ";
    std::cout << std::endl;

    for (size_t i = 0; i < SIZE; i++) {
        EXPECT_EQ(result_dense[i], result_band[i]);
        EXPECT_EQ(result_dense[i], result_csr[i]);
    }
}