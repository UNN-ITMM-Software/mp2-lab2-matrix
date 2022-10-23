// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

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
