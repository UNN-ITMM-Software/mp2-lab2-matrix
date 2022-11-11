#pragma once
#include "Vector.h"

const int MAX_MATRIX_SIZE = 10000;

// Динамическая матрица - 
// шаблонная матрица на динамической памяти

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

public:

  TDynamicMatrix(size_t s = 1);

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TDynamicMatrix<T>& m) const noexcept;

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val);

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v);

  // матрично-матричные операции
  TDynamicMatrix<T> operator+(const TDynamicMatrix<T>& m);
  TDynamicMatrix<T> operator-(const TDynamicMatrix<T>& m);
  TDynamicMatrix<T> operator*(const TDynamicMatrix<T>& m);

  // ввод/вывод
  template<typename T>
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix<T>& v);

  template<typename T>
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix<T>& v);
};

template<typename T>
inline TDynamicMatrix<T>::TDynamicMatrix(size_t s) : TDynamicVector<TDynamicVector<T>>(s)
{
  if (s > MAX_MATRIX_SIZE) throw "s > MAX_MATRIX_SIZE";
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
  TDynamicMatrix(sz) res;
  for (int i = 0; i < sz; i++)
  {
    res.pMem[i] = pMem[i] * val;
  }

  return res;
}

template<typename T>
inline TDynamicVector<T> TDynamicMatrix<T>::operator*(const TDynamicVector<T>& v)
{

  TDynamicVector<T> res(sz);
  for (int i = 0; i < sz; i++)
  {
    res.pMem[i] = pMem[i] * v;
  }

  return res;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& m)
{
  if (this->sz != m.sz) throw "operator+(const TDynamicMatrix<T>& m) sz != m.sz";
  TDynamicMatrix<T> res(sz);
  for (int i = 0; i < sz; i++)
  {
    res.pMem[i] = pMem[i] + m.pMem[i];
  }

  return res;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& m)
{

  if (this->sz != m.sz) throw "operator-(const TDynamicMatrix<T>& m) sz != m.sz";
  TDynamicMatrix<T> res(sz);
  for (int i = 0; i < sz; i++)
  {
    res.pMem[i] = pMem[i] - m.pMem[i];
  }

  return res;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix<T>& m)
{
  if (this->sz != m.sz) throw "operator*(const TDynamicMatrix<T>& m) sz != m.sz";
  TDynamicMatrix<T> res(sz);
  for (int i = 0; i < this->sz; i++)
  {
    for (int j = 0; j < this->sz; j++)
    {
      res[i][j] = 0;
      for (int k = 0; k < this->sz; k++)
      {
        res[i][j] += this->pMem[i][k] * m.pMem[k][j];
      }
    }
  }
  return res;
}

template<typename T>
inline std::istream& operator>>(std::istream& istr, TDynamicMatrix<T>& v)
{
  std::cout << "Enter " << v.sz * v.sz << " values of Matrix: \n";
  for (int i = 0; i < v.sz; i++)
    for (int j = 0; j < v.sz; j++)
      istr >> v.pMem[i][j];
  return istr;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix<T>& v)
{
  for (int i = 0; i < v.sz; i++)
  {
    for (int j = 0; j < v.sz; j++)
      ostr << v.pMem[i][j] << '\t';
    std::cout << std::endl;
  }
  return ostr;
}