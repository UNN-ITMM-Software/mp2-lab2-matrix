// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

void main()
{
	TMatrix<int> a(5), b(5), c(5);
	int i, j;
	size_t size;

	cout << "Input size of upper triangular matrices: ";
	cin >> size;

	TMatrix<int> A(size), B(size);

	cout << "For example: \n 1 2 3\n 0 4 5\n 0 0 6" << endl;
	cout << "Was inputed as 1 2 3 4 5 6" << endl;

	cout << "Input first upper triangular matrix:" << endl;
	cin >> A;
	cout << "Input second upper triangular matrix:" << endl;
	cin >> B;

	setlocale(LC_ALL, "Russian");
	cout << "Тестирование программ поддержки представления треугольных матриц"
		<< endl;
	for (i = 0; i < 5; i++)
		for (j = i; j < 5; j++)
		{
			a[i][j] = i * 10 + j;
			b[i][j] = (i * 10 + j) * 100;
		}
	c = a + b;
	cout << "Matrix a = " << endl << a << endl;
	cout << "Matrix b = " << endl << b << endl;
	cout << "Matrix c = a + b" << endl << c << endl;
	TMatrix<int> C = A + B, D = A - B;
	cout << "Matrix A + B:" << endl << C << endl;
	cout << "Matrix A - B:" << endl << D << endl;
}
