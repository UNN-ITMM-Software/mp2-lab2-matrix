#pragma once
#include "Vector.h"

const int MAX_TR_MATRIX_SIZE = 15000;

// Динамическая нижне-треугольная матрица - 
// шаблонная матрица на динамической памяти

template<typename T>
class TTriangularDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

public:

  TTriangularDynamicMatrix(size_t s = 1);
  virtual ~TTriangularDynamicMatrix();

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TTriangularDynamicMatrix<T>& m) const noexcept;
  bool operator!=(const TTriangularDynamicMatrix<T>& m) const noexcept;

  // матрично-скалярные операции
  TTriangularDynamicMatrix<T> operator*(const T& val);

  // матрично-матричные операции
  TTriangularDynamicMatrix<T> operator+(const TTriangularDynamicMatrix<T>& m);
  TTriangularDynamicMatrix<T> operator-(const TTriangularDynamicMatrix<T>& m);
  TTriangularDynamicMatrix<T> operator*(const TTriangularDynamicMatrix<T>& m);

  // ввод/вывод
  template<typename T>
  friend std::istream& operator>>(std::istream& istr, TTriangularDynamicMatrix<T>& v);

  template<typename T>
  friend std::ostream& operator<<(std::ostream& ostr, const TTriangularDynamicMatrix<T>& v);
};

template<typename T>
inline TTriangularDynamicMatrix<T>::TTriangularDynamicMatrix(size_t s) : TDynamicVector<TDynamicVector<T>>(s)
{
  if (s > MAX_TR_MATRIX_SIZE) throw "s > MAX_MATRIX_SIZE";
  //if (s > 0)
  //{
  //  sz = s;
  //  pMem = new TDynamicVector<T>[sz];
  //  for (int i = 0; i < sz; i++)
  //  {
  //    pMem[i] = TDynamicVector<T>(i + 1);
  //  }
  //}
  sz = s;
  pMem = new TDynamicVector<T>[sz];
  for (int i = 0; i < sz; i++)
  {
    pMem[i] = TDynamicVector<T>(i + 1);
  }
}

template<typename T>
inline TTriangularDynamicMatrix<T>::~TTriangularDynamicMatrix()
{
}

template<typename T>
inline bool TTriangularDynamicMatrix<T>::operator==(const TTriangularDynamicMatrix<T>& m) const noexcept
{
  if (sz != m.sz) return false;
  for (int i = 0; i < sz; i++)
  {
    if (pMem[i] != m.pMem[i]) return false;
  }
  return true;
}

template<typename T>
inline bool TTriangularDynamicMatrix<T>::operator!=(const TTriangularDynamicMatrix<T>& m) const noexcept
{
  return !(this->operator==(m));
}

template<typename T>
inline TTriangularDynamicMatrix<T> TTriangularDynamicMatrix<T>::operator*(const T& val)
{
  TTriangularDynamicMatrix(sz) res;
  for (int i = 0; i < sz; i++)
  {
    res.pMem[i] = pMem[i] * val;
  }

  return res;
}


template<typename T>
inline TTriangularDynamicMatrix<T> TTriangularDynamicMatrix<T>::operator+(const TTriangularDynamicMatrix<T>& m)
{
  if (this->sz != m.sz) throw "operator+(const TTriangularDynamicMatrix<T>& m) sz != m.sz";
  TTriangularDynamicMatrix<T> res(sz);
  for (int i = 0; i < sz; i++)
  {
    res.pMem[i] = pMem[i] + m.pMem[i];
  }

  return res;
}

template<typename T>
inline TTriangularDynamicMatrix<T> TTriangularDynamicMatrix<T>::operator-(const TTriangularDynamicMatrix<T>& m)
{
  if (this->sz != m.sz) throw "operator-(const TTriangularDynamicMatrix<T>& m) sz != m.sz";
  TTriangularDynamicMatrix<T> res(sz);
  for (int i = 0; i < sz; i++)
  {
    res.pMem[i] = pMem[i] - m.pMem[i];
  }

  return res;
}

template<typename T>
inline TTriangularDynamicMatrix<T> TTriangularDynamicMatrix<T>::operator*(const TTriangularDynamicMatrix<T>& m)
{
  if (sz != m.sz) throw "operator*(const TTriangularDynamicMatrix<T>& m) sz != m.sz";
  TTriangularDynamicMatrix<T> res(m.sz);
  for (int i = 0; i < sz; i++)
    for (int j = 0; j < sz; j++)
    {
      if (j <= i)
      {
        res[i][j] = 0;
        for (int k = 0; k < sz; k++)
        {
          if ((k <= i) && (k >= j))
          {
            res[i][j] += this->pMem[i][k] * m[k][j];
          }
        }
      }
    }

  return res;
}

template<typename T>
inline std::istream& operator>>(std::istream& istr, TTriangularDynamicMatrix<T>& v)
{
  for (int i = 0; i < v.sz; i++)
    for (int j = 0; j < v.sz; j++)
      if (j <= i)
        istr >> v.pMem[i][j];
  return istr;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& ostr, const TTriangularDynamicMatrix<T>& v)
{
  for (int i = 0; i < v.sz; i++)
  {
    for (int j = 0; j < v.sz; j++)
      if (j <= i)
        ostr << v.pMem[i][j] << "\t";
    ostr << std::endl;
  }
  return ostr;
}
