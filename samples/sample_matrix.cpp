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

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки представления треугольных матриц" << endl;
  cout << "Введите размер матриц:" << endl;
  int n;
  cin >> n;
  TMatrix <int> A(n), B(n);
  cout << "Введитее матрицу А:" << endl;
  cin >> A;
  cout << endl;
  cout << "Введите матрицу B:" << endl;
  cin >> B;
  cout << endl;
  cout << "1.Сложение матриц" << endl;
  cout << "2.Вычитание матрицы B из матрицы A (A-B)" << endl;
  cout << "3.Вычитание матрицы A из матрицы B (B-A)" << endl;
  int k;
  cout << endl;
  cin >> k;
  cout << endl;
  switch (k)
  {
  case 1:
  {
	  cout << "A+B=" << endl << endl << A + B << endl;
	  break;
  }
  case 2:
  {
	  cout << "A-B=" << endl << endl << A - B << endl;
	  break;
  }
  case 3:
  {
	  cout << "B-A=" << endl << endl << B - A << endl;
	  break;
  }
  }
}
//---------------------------------------------------------------------------
