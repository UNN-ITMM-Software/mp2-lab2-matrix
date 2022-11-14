// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#pragma once
#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;

template<typename T>
class TVectorIterator;


// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1);
  TDynamicVector(T* arr, size_t s);
  TDynamicVector(const TDynamicVector<T>& v);
  TDynamicVector(TDynamicVector<T>&& v) noexcept;
  ~TDynamicVector();
  TDynamicVector<T>& operator=(const TDynamicVector<T>& v);
  TDynamicVector<T>& operator=(TDynamicVector<T>&& v) noexcept;

  size_t size() const noexcept;

  // индексация
  T& operator[](size_t ind);
  const T& operator[](size_t ind) const;
  // индексация с контролем
  T& at(size_t ind);
  const T& at(size_t ind) const;

  // сравнение
  bool operator==(const TDynamicVector<T>& v) const noexcept;
  bool operator!=(const TDynamicVector<T>& v) const noexcept;

  // скалярные операции
  TDynamicVector<T> operator+(T val);
  TDynamicVector<T> operator-(T val);
  TDynamicVector<T> operator*(T val);

  // векторные операции
  TDynamicVector<T> operator+(const TDynamicVector<T>& v);
  TDynamicVector<T> operator-(const TDynamicVector<T>& v);
  T operator*(const TDynamicVector<T>& v) noexcept(noexcept(T()));

  friend void swap(TDynamicVector<T>& lhs, TDynamicVector<T>& rhs) noexcept;

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector<T>& v);
  friend ostream& operator<<(ostream& ostr, const TDynamicVector<T>& v);

  TVectorIterator<T> begin();
  TVectorIterator<T> end();
};

template<typename T>
inline TDynamicVector<T>::TDynamicVector(size_t size)
{
  size(sz);
  pMem = new T[size];
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(T* arr, size_t s)
{
  size(s);

  if (arr == nullptr) throw "TDynamicVector arr == nullptr";
  pMem = new T[s];
  for (int i = 0; i < s; i++)
    pMem[i] = arr[i];
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(TDynamicVector<T>&& v) noexcept
{
  if (v.pMem == nullptr)
  {
    sz = 0;
    pMem = nullptr;
  }
  else
  {
    sz = v.sz;
    pMem = new T[size];

    for (int i = 0; i < sz; i++)
      pMem[i] = v.pMem[i];
  }
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(TDynamicVector<T>&& v) noexcept
{
  sz = v.sz;
  pMem = v.pMem;

  v.sz = 0;
  v.pMem = nullptr;
}

template<typename T>
inline TDynamicVector<T>::~TDynamicVector()
{
  if (pMem != nullptr)
  {
    delete[] pMem;
    sz = 0;
  }
}

template<typename T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector<T>& v)
{
  if (this != &v)
  {
    if (pMem != nullptr)
      delete{} pMem;

    if (v.pMem == nullptr)
    {
      sz = 0;
      pMem = nullptr;
    }
    else
    {
      sz = v.sz;
      pMem = new T[size];

      for (int i = 0; i < sz; i++)
        pMem[i] = v.pMem[i];
    }
  }

  return *this;
}

template<typename T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(TDynamicVector<T>&& v) noexcept
{
  if (this != &v)
  {
    if (pMem != nullptr)
      delete[] pMem;

    sz = v.sz;
    pMem = v.pMem;

    v.sz = 0;
    v.pMem = nullptr;
  }

  return *this;
}

template<typename T>
inline size_t TDynamicVector<T>::size() const noexcept
{
  if (size <= 0 || size > MAX_VECTOR_SIZE)
    throw "TDynamicVector(size_t size) size <= 0 || size > MAX_VECTOR_SIZE";
  return sz;
}

template<typename T>
inline T& TDynamicVector<T>::operator[](size_t ind)
{
  return pMem[ind];
}

template<typename T>
inline const T& TDynamicVector<T>::operator[](size_t ind) const
{
  return pMem[ind];
}

template<typename T>
inline T& TDynamicVector<T>::at(size_t ind)
{
  if (pMem == nullptr) throw "operator[] pMem == nullptr";
  if (ind >= sz || ind < 0) throw "operator[] ind >= sz || ind < 0";

  return pMem[ind];
}

template<typename T>
inline const T& TDynamicVector<T>::at(size_t ind) const
{
  if (pMem == nullptr) throw "operator[] pMem == nullptr";
  if (ind >= sz || ind < 0) throw "operator[] ind >= sz || ind < 0";

  return pMem[ind];
}

template<typename T>
inline bool TDynamicVector<T>::operator==(const TDynamicVector<T>& v) const noexcept
{
  if (sz != v.sz)
    return false;

  for (int i = 0; i < sz; i++)
    if (pMem[i] != v.pMem[i])
      return false;

  return true;
}

template<typename T>
inline bool TDynamicVector<T>::operator!=(const TDynamicVector<T>& v) const noexcept
{
  return !(this->operator==(v));
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator+(T val)
{
  if (sz != v.sz) throw ":operator+ sz != v.sz";

  TDynamicVector res(*this);

  for (int i = 0; i < sz; i++)
    res.pMem[i] += val;

  return res;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(T val)
{
  if (sz != v.sz) throw ":operator- sz != v.sz";

  TDynamicVector res(*this);

  for (int i = 0; i < sz; i++)
    res.pMem[i] -= val;

  return res;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator*(T val)
{
  if (sz != v.sz) throw ":operator* sz != v.sz";

  TDynamicVector res(*this);

  for (int i = 0; i < sz; i++)
    res.pMem[i] *= val;

  return res;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector<T>& v)
{
  if (sz != v.sz) throw ":operator+ sz != v.sz";

  TDynamicVector res(*this);

  for (int i = 0; i < sz; i++)
    res.pMem[i] += v.pMem[i];

  return res;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector<T>& v)
{
  if (sz != v.sz) throw ":operator- sz != v.sz";

  TDynamicVector res(*this);

  for (int i = 0; i < sz; i++)
    res.pMem[i] -= v.pMem[i];

  return res;
}

template<typename T>
inline T TDynamicVector<T>::operator*(const TDynamicVector<T>& v) noexcept(noexcept(T()))
{
  if (sz != v.sz) throw ":operator* sz != v.sz";

  T res(*this);

  for (int i = 0; i < sz; i++)
    res += pMem[i] * v.pMem[i];

  return res;
}

template<typename T>
void swap(TDynamicVector<T>& lhs, TDynamicVector<T>& rhs) noexcept
{
  std::swap(lhs.sz, rhs.sz);
  std::swap(lhs.pMem, rhs.pMem);
}

template<typename T>
istream& operator>>(istream& istr, TDynamicVector<T>& v)
{
  for (size_t i = 0; i < v.sz; i++)
    istr >> v.pMem[i];
  return istr;
}

template<typename T>
ostream& operator<<(ostream& ostr, const TDynamicVector<T>& v)
{
  for (size_t i = 0; i < v.sz; i++)
    ostr << v.pMem[i] << ' ';
  return ostr;
}

template<typename T>
inline TVectorIterator<T> TDynamicVector<T>::begin()
{
  return TVectorIterator<T>(*this);
}

template<typename T>
inline TVectorIterator<T> TDynamicVector<T>::end()
{
  return TVectorIterator<T>(*this, this->size());
}


//* ======================================================================== *\\

// TVectorIterator

template<typename T>
class TVectorIterator
{
private:
  TDynamicVector<T>& vector;
  int index;

public:
  TVectorIterator(TDynamicVector<T>& v);
  TVectorIterator(TDynamicVector<T>& v, int ind);
  TVectorIterator(TVectorIterator<T>& p);

  bool operator == (const TVectorIterator<T>& v);
  bool operator != (const TVectorIterator<T>& v);

  TVectorIterator<T> operator++ ();
  TVectorIterator<T> operator-- ();

  T& operator* ();
};

template<typename T>
inline TVectorIterator<T>::TVectorIterator(TDynamicVector<T>& v) : vector(v)
{
  index = 0;
}

template<typename T>
inline TVectorIterator<T>::TVectorIterator(TDynamicVector<T>& v, int ind) : vector(v)
{
  index = ind;
}

template<typename T>
inline TVectorIterator<T>::TVectorIterator(TVectorIterator<T>& p) : vector(p.vector), index(p.index)
{
}

template<typename T>
inline bool TVectorIterator<T>::operator==(const TVectorIterator<T>& v)
{
  if (&vector == &(v.vector) && index == v.index) return true;
  return false;
}

template<typename T>
inline bool TVectorIterator<T>::operator!=(const TVectorIterator<T>& v)
{
  return !(this->operator==(v));
}

template<typename T>
inline TVectorIterator<T> TVectorIterator<T>::operator++()
{
  this->index++;
  if (this->index > vector.size()) this->index = vector.size();
  return *this;
}

template<typename T>
inline TVectorIterator<T> TVectorIterator<T>::operator--()
{
  this->index--;
  if (this->index < 0) this->index = 0;
  return *this;
}

template<typename T>
inline T& TVectorIterator<T>::operator*()
{
  return vector.at(index);
}