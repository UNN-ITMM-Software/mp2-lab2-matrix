// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz < 0)
      throw "Err";
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
      throw "Err";
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    if (sz < 0)
      throw "Err";
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    pMem = nullptr;
    swap(*this, v);
  }
  ~TDynamicVector()
  {
    if (pMem != 0) 
    {
      delete[]pMem;
      pMem = 0;
    }
    sz = 0;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v)
      return *this;
    TDynamicVector tmp(v);
    swap(*this, tmp);
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    swap(*this, v);
    return*this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    if (pMem == 0)
      throw "Err";
    if ((ind < 0) || (ind >= sz))
      throw "Err";
    return this->pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return this->pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (pMem == 0)
      throw "Err";
    if ((ind < 0) || (ind >= sz))
      throw "Err";
    return this->pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (pMem == 0)
      throw "Err";
    if ((ind < 0) || (ind >= sz))
      throw "Err";
    return this->pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz)
      return false;
    for (int i = 0; i < sz; i++) 
    {
      if (pMem[i] != v.pMem[i])
        return false;
    }
    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz)
      return true;
    for (int i = 0; i < sz; i++)
    {
      if (pMem[i] != v.pMem[i])
        return true;
    }
    return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector result(sz);
    for (int i = 0; i < sz; i++) 
    {
      result.pMem[i] = pMem[i] + val;
    }
    return result;
  }
  TDynamicVector operator-(double val)
  {
    TDynamicVector result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] - val;
    }
    return result;
  }
  TDynamicVector operator*(double val)
  {
    TDynamicVector result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] * val;
    }
    return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw "Err";
    TDynamicVector result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] + v.pMem[i];
    }
    return result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw "Err";
    TDynamicVector result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] - v.pMem[i];
    }
    return result;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
    if (sz != v.sz)
      throw out_of_range("Vectors are different size");
    int res = 0;
    for (size_t i = 0; i < sz; i++)
      res += pMem[i] * v.pMem[i];
    return res;
     
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (sz > MAX_MATRIX_SIZE)
      throw "Err";
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    return TDynamicVector<TDynamicVector<T>>::operator == (m);
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
    TDynamicMatrix<T> result(sz);
    for (int i = 0; i < sz; i++) 
    {
      result.pMem[i] = pMem[i] * val;
    }
    return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    TDynamicVector<T> result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] * v;
    }
    return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    TDynamicMatrix<T> result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] + m.pMem[i];
    }
    return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    TDynamicMatrix<T> result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] - m.pMem[i];
    }
    return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    TDynamicMatrix result(sz);
    for (size_t i = 0; i < sz; i++) 
    {
      for (size_t j = 0; j < sz; j++) 
      {
        for (size_t k = 0; k < sz; k++) 
        {
          result.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
        }
      }
    }
    return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    istr >> v.sz;
    TDynamicMatrix temp(sz);
    for (int i = 0; i < sz; i++)
      for (int j = 0; j < sz; j++)
        istr >> temp[i][j];
    v = temp;
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (int i = 0; i < v.sz; i++)
    {
      for (int j = 0; j < v.sz; j++)
        ostr << v[i][j] << "\t";
      ostr << "\n";
    }
    return ostr;
  }
};

#endif

