// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц


#include <iostream>
#include "tmatrix.h"
#include "types_of_matrix.h"
using namespace std;
//---------------------------------------------------------------------------

void main() {
    setlocale(LC_ALL, "Russian");
    cout << "1)База:" << endl;
    TDynamicMatrix<int> a(3), b(3), c(3);
    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++)
        {
            a[i][j] = i * 10 + j;
            b[i][j] = (i * 10 + j) * 100;
        }
    c = a + b;
    cout << "Matrix a = " << endl << a << endl;
    cout << "Matrix b = " << endl << b << endl;
    cout << "Matrix c = a + b" << endl << c << endl;


    cout << "2) Умножение ленточных матриц:" << endl;
    TGeneralBandMatrix<double> band1(3, 1, 1);
    TGeneralBandMatrix<double> band2(3, 1, 1);

    // Заполняем первую матрицу
    cout << "Заполняем матрицу A:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = max(0, i - 1); j <= min(2, i + 1); j++) {
            cout << "band1(" << i << "," << j << ") = " << (i * 3 + j + 1) << endl;
            band1(i, j) = i * 3 + j + 1;
        }
    }

    // Заполняем вторую матрицу
    cout << "\nЗаполняем матрицу B:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = max(0, i - 1); j <= min(2, i + 1); j++) {
            cout << "band2(" << i << "," << j << ") = " << ((i + 1) * (j + 1)) << endl;
            band2(i, j) = (i + 1) * (j + 1);
        }
    }

    cout << "\nЛенточная матрица A:" << endl;
    cout << band1 << endl;
    cout << "Ленточная матрица B:" << endl;
    cout << band2 << endl;
    try {
        TGeneralBandMatrix<double> band_result = band1 * band2;
        cout << "Результат умножения A * B:" << endl;
        cout << band_result << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка умножения: " << e.what() << endl;
    }

    cout << "3) Умножение симметричных матриц:" << endl;
    TSymmetricBandMatrix<double> sym1(3, 1);
    TSymmetricBandMatrix<double> sym2(3, 1);

    // Заполняем матрицы (только верхний треугольник)
    sym1(0, 0) = 1.0; sym1(0, 1) = 2.0;
    sym1(1, 1) = 3.0; sym1(1, 2) = 1.0;
    sym1(2, 2) = 2.0;

    sym2(0, 0) = 2.0; sym2(0, 1) = 1.0;
    sym2(1, 1) = 1.0; sym2(1, 2) = 3.0;
    sym2(2, 2) = 2.0;

    cout << "Симметричная матрица A:" << endl;
    cout << sym1 << endl;
    cout << "Симметричная матрица B:" << endl;
    cout << sym2 << endl;

    try {
        TSymmetricBandMatrix<double> sym_result = sym1 * sym2;
        cout << "Результат умножения A * B:" << endl;
        cout << sym_result << endl;

        // Проверка симметрии результата
        cout << "Проверка симметрии результата:" << endl;
        cout << "sym_result(0,1) = " << sym_result(0, 1) << ", sym_result(1,0) = " << sym_result(1, 0) << endl;
        cout << "sym_result(0,2) = " << sym_result(0, 2) << ", sym_result(2,0) = " << sym_result(2, 0) << endl;
        cout << "sym_result(1,2) = " << sym_result(1, 2) << ", sym_result(2,1) = " << sym_result(2, 1) << endl;

    }
    catch (const exception& e) {
        cout << "Ошибка умножения: " << e.what() << endl;
    }

    cout << "4) Умножение CSR матриц:" << endl;
    TCSRMatrix<double> csr1(3, 3);
    TCSRMatrix<double> csr2(3, 3);
    // Заполняем первую CSR матрицу
    csr1.set(0, 0, 1.0); csr1.set(0, 1, 2.0);
    csr1.set(1, 1, 3.0); csr1.set(1, 2, 1.0);
    csr1.set(2, 0, 2.0); csr1.set(2, 2, 1.0);
    // Заполняем вторую CSR матрицу
    csr2.set(0, 0, 2.0); csr2.set(0, 2, 1.0);
    csr2.set(1, 1, 1.0); csr2.set(1, 2, 3.0);
    csr2.set(2, 0, 1.0); csr2.set(2, 1, 2.0);
    cout << "CSR матрица A:" << endl;
    cout << csr1 << endl;
    cout << "CSR матрица B:" << endl;
    cout << csr2 << endl;
    try {
        TCSRMatrix<double> csr_result = csr1 * csr2;
        cout << "Результат умножения A * B:" << endl;
        cout << csr_result << endl;
        cout << "Количество ненулевых элементов в результате: " << csr_result.non_zeros() << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка умножения: " << e.what() << endl;
    }
}
//---------------------------------------------------------------------------