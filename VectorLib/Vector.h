#pragma once

#include <iostream>

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
  TDynamicVector<T> operator-(double val);
  TDynamicVector<T> operator*(double val);

  // векторные операции
  TDynamicVector<T> operator+(const TDynamicVector<T>& v);
  TDynamicVector<T> operator-(const TDynamicVector<T>& v);
  T operator*(const TDynamicVector<T>& v);

  friend void swap(TDynamicVector<T>& lhs, TDynamicVector<T>& rhs) noexcept;

  // ввод/вывод
  template<typename T>
  friend std::istream& operator>>(std::istream& istr, TDynamicVector<T>& v);

  template<typename T>
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector<T>& v);

  TVectorIterator<T> begin();
  TVectorIterator<T> end();
};

template<typename T>
inline TDynamicVector<T>::TDynamicVector(size_t size)
{
  if (size <= 0 || size > MAX_VECTOR_SIZE) throw "TDynamicVector(size_t size) size <= 0 || size > MAX_VECTOR_SIZE";
  sz = size;
  pMem = new T[sz];
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(T* arr, size_t s)
{
  if (size <= 0) throw "TDynamicVector(T* arr, size_t s) size <= 0";
  if (arr == nullptr) throw "TDynamicVector(T* arr, size_t s) arr == 0";
  sz = s;
  pMem = new T[sz];
  for (int i = 0; i < sz; i++)
  {
    pMem[i] = arr[i];
  }
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(const TDynamicVector<T>& v)
{
  if (v.pMem == nullptr)
  {
    sz = 0;
    pMem = nullptr;
  }
  else
  {
    sz = v.sz;
    pMem = new T[sz];
    for (int i = 0; i < sz; i++)
    {
      pMem[i] = v.pMem[i];
    }
  }
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(TDynamicVector<T>&& v) noexcept
{
  pMem = v.pMem;
  sz = v.sz;

  v.sz = 0;
  v.pMem = nullptr;
}

template<typename T>
inline TDynamicVector<T>::~TDynamicVector()
{
  if (pMem != nullptr) delete[] pMem;
  sz = 0;
}

template<typename T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector<T>& v)
{
  if (this == &v) return *this;
  if (pMem != nullptr) delete[] pMem;
  if (v.pMem == nullptr)
  {
    sz = 0;
    pMem = nullptr;
  }
  else
  {
    sz = v.sz;
    pMem = new T[sz];
    for (int i = 0; i < sz; i++)
    {
      pMem[i] = v.pMem[i];
    }
  }

  return *this;
}

template<typename T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(TDynamicVector<T>&& v) noexcept
{
  if (pMem != nullptr) delete[] pMem;

  pMem = v.pMem;
  sz = v.sz;

  v.pMem = nullptr;
  v.sz = 0;
  return *this;
}

template<typename T>
inline size_t TDynamicVector<T>::size() const noexcept
{
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
  if (pMem == nullptr) throw "opertator[] pMem == nullptr";
  if (ind < 0 || ind >= sz) throw "opertator[] out of range";
  return pMem[ind];
}

template<typename T>
inline const T& TDynamicVector<T>::at(size_t ind) const
{
  if (pMem == nullptr) throw "opertator[] pMem == nullptr";
  if (ind < 0 || ind >= sz) throw "opertator[] out of range";
  return pMem[ind];
}

template<typename T>
inline bool TDynamicVector<T>::operator==(const TDynamicVector<T>& v) const noexcept
{
  if (sz != v.sz) return false;
  for (int i = 0; i < sz; i++)
  {
    if (pMem[i] != v.pMem[i]) return false;
  }
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
  if (pMem == nullptr) throw "operator+(T val) pMem == nullptr";
  TDynamicVector tmp(*this);
  for (int i = 0; i < sz; i++)
  {
    tmp.pMem[i] += val;
  }
  return tmp;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(double val)
{
  if (pMem == nullptr) throw "operator-(double val) pMem == nullptr";
  TDynamicVector<T> tmp(*this);
  for (int i = 0; i < sz; i++)
  {
    tmp.pMem[i] -= val;
  }
  return tmp;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator*(double val)
{
  if (pMem == nullptr) throw "operator*(double val) pMem == nullptr";
  TDynamicVector<T> tmp(*this);
  for (int i = 0; i < sz; i++)
  {
    tmp.pMem[i] *= val;
  }
  return tmp;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector<T>& v)
{
  if (pMem == nullptr) throw "operator+(const TDynamicVector& v) pMem == nullptr";
  if (sz != v.sz) throw "operator+(const TDynamicVector& v) sz != v.sz";
  TDynamicVector<T> tmp(*this);
  for (int i = 0; i < sz; i++)
  {
    tmp.pMem[i] += v.pMem[i];
  }
  return tmp;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector<T>& v)
{
  if (pMem == nullptr) throw "operator-(const TDynamicVector& v) pMem == nullptr";
  if (sz != v.sz) throw "operator-(const TDynamicVector& v) sz != v.sz";
  TDynamicVector<T> tmp(*this);
  for (int i = 0; i < sz; i++)
  {
    tmp.pMem[i] -= v.pMem[i];
  }
  return tmp;
}

template<typename T>
inline T TDynamicVector<T>::operator*(const TDynamicVector<T>& v)
{
  if (pMem == nullptr) throw "operator*(const TDynamicVector& v) pMem == nullptr";
  if (sz != v.sz) throw "operator*(const TDynamicVector& v) sz != v.sz";
  T res = 0;
  for (int i = 0; i < sz; i++)
  {
    res += pMem[i] * v.pMem[i];
  }
  return res;
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

template<typename T>
void swap(TDynamicVector<T>& lhs, TDynamicVector<T>& rhs) noexcept
{
  std::swap(lhs.sz, rhs.sz);
  std::swap(lhs.pMem, rhs.pMem);
}

template<typename T>
std::istream& operator>>(std::istream& istr, TDynamicVector<T>& v)
{
  for (size_t i = 0; i < v.sz; i++)
    istr >> v.pMem[i]; // требуется оператор>> для типа T
  return istr;
}
template<typename T>
std::ostream& operator<<(std::ostream& ostr, const TDynamicVector<T>& v)
{
  for (size_t i = 0; i < v.sz; i++)
    ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
  return ostr;
}

//==============================================================================================================//

template<typename T>
class TVectorIterator
{
public:

  TVectorIterator(TDynamicVector<T>& v);
  TVectorIterator(TDynamicVector<T>& v, int ind);
  TVectorIterator(TVectorIterator<T>& p);

  bool operator == (const TVectorIterator<T>& v);
  bool operator != (const TVectorIterator<T>& v);

  TVectorIterator<T> operator++ ();
  TVectorIterator<T> operator-- ();

  T& operator* ();

private:

  TDynamicVector<T>& vector;
  int index;
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