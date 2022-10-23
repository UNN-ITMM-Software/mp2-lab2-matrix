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
  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки представления треугольных матриц" << endl;
  
  int size;
  cout << "Enter size of matrices: ";
  cin >> size;

  TMatrix<int> A(size), B(size);
  cout << "Enter elements of matrix A (row by row):" << endl;
  for (int i = 0; i < size; i++)
	  for (int j = i; j < size; ++j)
	  {
		  cin >> A[i][j];
	  }

  cout << endl << "Enter elements of matrix B (row by row):" << endl;
  for (int i = 0; i < size; i++)
	  for (int j = i; j < size; ++j)
	  {
		  cin >> B[i][j];
	  }

  cout << "A+B:" << endl << A+B << endl;
  cout << "A-B:" << endl << A-B << endl;
}
//---------------------------------------------------------------------------
