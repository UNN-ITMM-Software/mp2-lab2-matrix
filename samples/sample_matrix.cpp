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
	int i, j, n;

	setlocale(LC_ALL, "Russian");
	cout << "Тестирование программ поддержки представления треугольных матриц"
	<< endl;
	for (i = 0; i < 5; i++)
		for (j = i; j < 5; j++ )
		{
			a[i][j] =  i * 10 + j;
			b[i][j] = (i * 10 + j) * 100;
		}
	c = a + b;
	cout << "Matrix a = " << endl << a << endl;
	cout << "Matrix b = " << endl << b << endl;
	cout << "Matrix c = a + b" << endl << c << endl;

	cout << "Введите размер матрицы: ";
	cin >> n;
	TMatrix<int> m1(n), m2(n), s(n);

	cout << endl << "Введите верхнетреугольную матрицу матрицу m1: " << endl;
	cin >> m1;
	cout << endl << "Введите верхнетреугольную матрицу матрицу m2: " << endl;
	cin >> m2;

	cout << endl << "Матрица m1:" << endl;
	for (i = 0; i < n; i++)
	{
		for (j = i; j < n; j++)
		{
			cout << m1[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << "Матрица m2:" << endl;
	for (i = 0; i < n; i++)
	{
		for (j = i; j < n; j++)
		{
			cout << m2[i][j] << " ";
		}
		cout << endl;
	}

	if (m1 == m2)
		cout << "Матрицы m1 и m2 равны" << endl << endl;
	else
		cout << "Матрицы m1 и m2 не равны" << endl << endl;

	s = m1 + m2;
	cout << "m1 + m2 = " << endl << s << endl;

	s = m1 - m2;
	cout << "m1 - m2 = " << endl << s << endl;
}
//---------------------------------------------------------------------------
