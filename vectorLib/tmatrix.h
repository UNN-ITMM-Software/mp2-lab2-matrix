// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#pragma once
#include "tVector.h"

using namespace std;

const int MAX_MATRIX_SIZE = 10000;

// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
  
public:
  TDynamicMatrix(size_t s = 1);

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept;

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val);

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v);

  // матрично-матричные операции
  TDynamicMatrix<T> operator+(const TDynamicMatrix<T>& m);
  TDynamicMatrix<T> operator-(const TDynamicMatrix<T>& m);
  TDynamicMatrix<T> operator*(const TDynamicMatrix<T>& m);

  // ввод/вывод
  template<typename T>
  friend istream& operator>>(istream& istr, TDynamicMatrix& v);
  template<typename T>
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v);
};

template<typename T>
inline TDynamicMatrix<T>::TDynamicMatrix(size_t s) : TDynamicVector<TDynamicVector<T>>(s)
{
  if (s > MAX_MATRIX_SIZE || s < 0) throw "TDynamicMatrix(size_t s) s > MAX_MATRIX_SIZE || s < 0";
  for (size_t i = 0; i < sz; i++)
    pMem[i] = TDynamicVector<T>(sz);
}

template<typename T>
inline bool TDynamicMatrix<T>::operator==(const TDynamicMatrix<T>& m) const noexcept
{
  return TDynamicVector<TDynamicVector<T>>::operator == (m);
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const T& val)
{
  TDynamicMatrix(sz) result;
  for (int i = 0; i < sz; i++)
    result.pMem[i] = pMem[i] * val;
  return result;
}

template<typename T>
inline TDynamicVector<T> TDynamicMatrix<T>::operator*(const TDynamicVector<T>& v)
{
  TDynamicVector<T> result(sz);
  for (int i = 0; i < sz; i++)
    result.pMem[i] = pMem[i] * v;
  return result;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& m)
{
  if (this->sz != m.sz) throw "operator+(const TDynamicMatrix<T>& m) sz != m.sz";

  TDynamicMatrix<T> result(sz);
  for (int i = 0; i < sz; i++)
    result.pMem[i] = pMem[i] + m.pMem[i];
  return result;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& m)
{
  if (this->sz != m.sz) throw "operator-(const TDynamicMatrix<T>& m) sz != m.sz";

  TDynamicMatrix<T> result(sz);
  for (int i = 0; i < sz; i++)
    result.pMem[i] = pMem[i] - m.pMem[i];
  return result;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix<T>& m)
{
  if (this->sz != m.sz) throw "operator*(const TDynamicMatrix<T>& m) sz != m.sz";

  TDynamicMatrix<T> result(sz);
  for (int i = 0; i < this->sz; i++)
    for (int j = 0; j < this->sz; j++)
    {
      result[i][j] = 0;
      for (int k = 0; k < this->sz; k++)
        result[i][j] += this->pMem[i][k] * m.pMem[k][j];
    }
  return result;
}

template<typename T>
inline istream& operator>>(istream& istr, TDynamicMatrix<T>& v)
{
  std::cout << "Enter " << v.sz * v.sz << " values of Matrix: \n";
  for (int i = 0; i < v.sz; i++)
    for (int j = 0; j < v.sz; j++)
      istr >> v.pMem[i][j];
  return istr;
} 

template<typename T>
inline ostream& operator<<(ostream& ostr, const TDynamicMatrix<T>& v)
{
  //const int sz = v.sz;
  //for (int i = 0; i < sz; i++)
  //{
  //  for (int j = 0; j < sz; j++)
  //    ostr << v.pMem[i][j] << '\t';
  //  std::cout << std::endl;
  //}
  return ostr;
}