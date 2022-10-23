// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "tmatrix.h"

void main()
{
  setlocale(LC_ALL, "Russian");
  int A_size, B_size;
  cout << "Тестирование программ поддержки представления треугольных матриц" << endl;
  do {
    cout << "Ввeдите размер первой верхнетреугольной матрицы А: ";
    cin >> A_size;
    cout << "Введите размер первой верхнетреугольной матрицы В: ";
    cin >> B_size;
      if (A_size != B_size)
        cout << "Введите одинаковые размеры матриц А и В для следующих операций с ними" << endl << "*---------------------*" << endl;
    } 
  while (A_size != B_size);

  TMatrix<int> A(A_size), B(B_size);
  cout << "Ввод матрицы А построчно:" << endl;
  cin >> A;
  cout << "Ввод матрицы B построчно:" << endl;
  cin >> B;
  cout << "Введеные матрицы" << endl;
  cout << "A:" << endl << A << endl;
  cout << "B:" << endl << B << endl;

  TMatrix<int> C = A + B;
  cout << "Сложение" << endl;
  cout << "A + B:" << endl << C << endl;

  C = A - B;
  cout << "Разность" << endl;
  cout << "A - B:" << endl << C << endl;
}
