#pragma once
#include "tVector.h"

const int MAX_BAND_MATRIX_SIZE = 10000;

// Динамическая ленточная матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TBandDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  size_t width = 0;
  
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

public:

  TBandDynamicMatrix(size_t s = 1, size_t width = 1);
  TBandDynamicMatrix(const TBandDynamicMatrix<T>& p);
  virtual ~TBandDynamicMatrix();

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  TBandDynamicMatrix<T>& operator=(const TBandDynamicMatrix<T>& p);

  TBandDynamicMatrix<T>& operator=(TBandDynamicMatrix<T>&& p);

  bool operator==(const TBandDynamicMatrix<T>& m) const noexcept;
  bool operator!=(const TBandDynamicMatrix<T>& m) const noexcept;

  TBandDynamicMatrix<T> operator*(const T& val);

  TBandDynamicMatrix<T> operator+(const TBandDynamicMatrix<T>& m);
  TBandDynamicMatrix<T> operator-(const TBandDynamicMatrix<T>& m);

  template<typename T>
  friend std::istream& operator>>(std::istream& istr, TBandDynamicMatrix<T>& v);

  template<typename T>
  friend std::ostream& operator<<(std::ostream& ostr, const TBandDynamicMatrix<T>& v);
};

template<typename T>
inline TBandDynamicMatrix<T>::TBandDynamicMatrix(size_t s, size_t width)
{
  if (s > MAX_LENT_MATRIX_SIZE || s <= 0) 
    throw "TBandDynamicMatrix(size_t s, size_t width) s > MAX_MATRIX_SIZE || s <= 0";
  if (width >= s || width < 1) 
    throw "TBandDynamicMatrix(size_t s, size_t width) width >= s || width < 1";
  
  this->sz = s;
  this->width = width;
  int tmp = 0;
  bool flag = true;
  pMem = new TDynamicVector<T>[this->width + this->width - 1];

  for (int i = 0; i < this->width + this->width - 1; i++)
  {
    if ((flag == true) && (tmp != (this->width)))
      tmp++;
    else
    {
      flag = false;
      tmp--;
    }

    pMem[i] = TDynamicVector<T>(this->sz - this->width + tmp);
  }
}

template<typename T>
inline TBandDynamicMatrix<T>::TBandDynamicMatrix(const TBandDynamicMatrix<T>& p) : TBandDynamicMatrix(p.sz, p.width)
{
  for (int i = 0; i < p.width + p.width - 1; i++)
    pMem[i] = p.pMem[i];
}

template<typename T>
inline TBandDynamicMatrix<T>::~TBandDynamicMatrix()
{
  width = 0;
}

template<typename T>
inline TBandDynamicMatrix<T>& TBandDynamicMatrix<T>::operator=(const TBandDynamicMatrix<T>& p)
{
  if (this == &p) return *this;
  if (pMem != nullptr) this->~TLentDynamicMatrix();

  sz = p.sz;
  width = p.width;
  pMem = new TDynamicVector<T>[this->width + this->width - 1];

  for (int i = 0; i < this->width + this->width - 1; i++)
  {
    pMem[i] = TDynamicVector<T>(p.pMem[i].size());
    pMem[i] = p.pMem[i];
  }

  return *this;
}

template<typename T>
inline TBandDynamicMatrix<T>& TBandDynamicMatrix<T>::operator=(TBandDynamicMatrix<T>&& p)
{
  if (pMem != nullptr) this->~TLentDynamicMatrix();

  sz = p.sz;
  width = p.width;
  pMem = p.pMem;
  
  for (int i = 0; i < width + width - 1; i++)
    pMem[i] = p.pMem[i];

  p.pMem = nullptr;
  p.sz = 0;
  p.width = 0;

  return *this;
}

template<typename T>
inline bool TBandDynamicMatrix<T>::operator==(const TBandDynamicMatrix<T>& m) const noexcept
{
  if (sz != m.sz || width != m.width) return false;
  for (int i = 0; i < this->width + this->width - 1; i++)
    if (pMem[i] != m.pMem[i]) return false;
  return true;
}

template<typename T>
inline bool TBandDynamicMatrix<T>::operator!=(const TBandDynamicMatrix<T>& m) const noexcept
{
  return !(this->operator==(m));
}

template<typename T>
inline TBandDynamicMatrix<T> TBandDynamicMatrix<T>::operator*(const T& val)
{
  TLentDynamicMatrix(sz, width) result;
  for (int i = 0; i < this->width + this->width - 1; i++)
    result.pMem[i] = pMem[i] * val;
  return result;
}

template<typename T>
inline TBandDynamicMatrix<T> TBandDynamicMatrix<T>::operator+(const TBandDynamicMatrix<T>& m)
{
  if (this->sz != m.sz || this->width != m.width) throw "operator+(const TLentDynamicMatrix<T>& m) sz != m.sz || width != m.width";

  TLentDynamicMatrix<T> result(sz, width);
  for (int i = 0; i < this->width + this->width - 1; i++)
    result.pMem[i] = pMem[i] + m.pMem[i];
  return result;
}

template<typename T>
inline TBandDynamicMatrix<T> TBandDynamicMatrix<T>::operator-(const TBandDynamicMatrix<T>& m)
{
  if (this->sz != m.sz || this->width != m.width) throw "operator+(const TLentDynamicMatrix<T>& m) sz != m.sz || width != m.width";

  TLentDynamicMatrix<T> result(sz, width);
  for (int i = 0; i < this->width + this->width - 1; i++)
    result.pMem[i] = pMem[i] - m.pMem[i];
  return result;
}

template<typename T>
inline std::istream& operator>>(std::istream& istr, TBandDynamicMatrix<T>& v)
{
  int tmp = 0;
  bool flag = true;
  v.pMem = new TDynamicVector<T>[v.width + v.width - 1];

  for (int i = 0; i < v.width + v.width - 1; i++)
  {
    if ((flag == true) && (tmp != (v.width)))
      tmp++;
    else
    {
      flag = false;
      tmp--;
    }

    v.pMem[i] = TDynamicVector<T>(v.sz - v.width + tmp);
    istr >> v.pMem[i];
  }

  return istr;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& ostr, const TBandDynamicMatrix<T>& v)
{
  for (int i = v.width - 1; i >= 0; i--)
    ostr << v.pMem[i][0] << "\t";
  ostr << std::endl;

  int c = v.width;
  while (c <= v.width + v.width - 2)
  {
    int i = c;
    int j = 0;

    while (i != v.width - 1)
    {
      ostr << v.pMem[i][j] << "\t";
      i--;
      j++;
    }

    while (i >= 0)
    {
      ostr << v.pMem[i][j] << "\t";
      i--;
    }
    ostr << std::endl;
    c++;
  }

  int tmp = v.pMem[0].size() - v.width;
  int s = 1;

  for (int k = 1; k <= v.sz - v.width; k++)
  {
    int i = v.width + v.width - 2;
    int j = k;
    for (int l = 0; l < k; l++)
      ostr << "\t";

    while (i != v.width - 1)
    {
      ostr << v.pMem[i][j] << "\t";
      i--;
      j++;
    }

    if (tmp != 0)
    {
      while (i >= 0)
      {
        ostr << v.pMem[i][j] << "\t";
        i--;
      }
      tmp--;
    }
    else
    {
      while (i >= s)
      {
        ostr << v.pMem[i][j] << "\t";
        i--;
      }
      s++;
    }
    ostr << std::endl;
  }

  return ostr;
}