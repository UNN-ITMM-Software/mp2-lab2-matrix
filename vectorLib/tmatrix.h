// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#pragma once
#include <iostream>

using namespace std;

const int MAX_MATRIX_SIZE = 10000;


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s);

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept;

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val);

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v);

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m);
  TDynamicMatrix operator-(const TDynamicMatrix& m);
  TDynamicMatrix operator*(const TDynamicMatrix& m);

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v);
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v);
};