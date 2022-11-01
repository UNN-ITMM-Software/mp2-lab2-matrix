#pragma once
#include "Vector.h"

const int MAX_LENT_MATRIX_SIZE = 10000;

// Динамическая ленточная матрица - 
// шаблонная матрица на динамической памяти

template<typename T>
class TLentDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  size_t width = 0;

  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

public:

  TLentDynamicMatrix(size_t s = 1, size_t width = 1);
  TLentDynamicMatrix(const TLentDynamicMatrix<T>& p);
  virtual ~TLentDynamicMatrix();

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  // оператор присваивания
  TLentDynamicMatrix<T>& operator=(const TLentDynamicMatrix<T>& p);

  // оператор перемещения
  TLentDynamicMatrix<T>& operator=(TLentDynamicMatrix<T>&& p);

  // сравнение
  bool operator==(const TLentDynamicMatrix<T>& m) const noexcept;
  bool operator!=(const TLentDynamicMatrix<T>& m) const noexcept;

  // матрично-скалярные операции
  TLentDynamicMatrix<T> operator*(const T& val);

  // матрично-матричные операции
  TLentDynamicMatrix<T> operator+(const TLentDynamicMatrix<T>& m);
  TLentDynamicMatrix<T> operator-(const TLentDynamicMatrix<T>& m);

  // ввод/вывод
  template<typename T>
  friend std::istream& operator>>(std::istream& istr, TLentDynamicMatrix<T>& v);

  template<typename T>
  friend std::ostream& operator<<(std::ostream& ostr, const TLentDynamicMatrix<T>& v);
};

template<typename T>
inline TLentDynamicMatrix<T>::TLentDynamicMatrix(size_t s, size_t width)
{
  if (s > MAX_LENT_MATRIX_SIZE) throw "s > MAX_MATRIX_SIZE";
  if (width >= s) throw "width >= size";
  if (width < 1) throw "width < 1";
  if (s > 0)
  {
    sz = s;
    int tmp = 0;
    bool flag = true;
    this->width = width;
    pMem = new TDynamicVector<T>[this->width + this->width - 1];
    for (int i = 0; i < this->width + this->width - 1; i++)
    {
      if ((flag == true) && (tmp != (this->width)))
      {
        tmp++;
      }
      else
      {
        flag = false;
        tmp--;
      }
      pMem[i] = TDynamicVector<T>(this->sz - this->width + tmp);
    }
  }
  else throw "size <= 0";
}

template<typename T>
inline TLentDynamicMatrix<T>::TLentDynamicMatrix(const TLentDynamicMatrix<T>& p) : TLentDynamicMatrix(p.sz, p.width)
{
  for (int i = 0; i < p.width + p.width - 1; i++)
  {
    pMem[i] = p.pMem[i];
  }
}

template<typename T>
inline TLentDynamicMatrix<T>::~TLentDynamicMatrix()
{
  width = 0;
}


template<typename T>
inline TLentDynamicMatrix<T>& TLentDynamicMatrix<T>::operator=(const TLentDynamicMatrix<T>& p)
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
inline TLentDynamicMatrix<T>& TLentDynamicMatrix<T>::operator=(TLentDynamicMatrix<T>&& p)
{
  if (pMem != nullptr) this->~TLentDynamicMatrix();
  sz = p.sz;
  width = p.width;
  pMem = p.pMem;
  for (int i = 0; i < width + width - 1; i++)
  {
    pMem[i] = p.pMem[i];
  }
  p.pMem = nullptr;
  p.sz = 0;
  p.width = 0;
  return *this;
}

template<typename T>
inline bool TLentDynamicMatrix<T>::operator==(const TLentDynamicMatrix<T>& m) const noexcept
{
  if ((sz != m.sz) || (width != m.width)) return false;
  for (int i = 0; i < this->width + this->width - 1; i++)
  {
    if (pMem[i] != m.pMem[i]) return false;
  }
  return true;
}

template<typename T>
inline bool TLentDynamicMatrix<T>::operator!=(const TLentDynamicMatrix<T>& m) const noexcept
{
  return !(this->operator==(m));
}

template<typename T>
inline TLentDynamicMatrix<T> TLentDynamicMatrix<T>::operator*(const T& val)
{
  TLentDynamicMatrix(sz, width) res;
  for (int i = 0; i < this->width + this->width - 1; i++)
  {
    res.pMem[i] = pMem[i] * val;
  }

  return res;
}

template<typename T>
inline TLentDynamicMatrix<T> TLentDynamicMatrix<T>::operator+(const TLentDynamicMatrix<T>& m)
{
  if ((this->sz != m.sz) || (this->width != m.width)) throw "operator+(const TLentDynamicMatrix<T>& m) sz != m.sz || width != m.width";
  TLentDynamicMatrix<T> res(sz, width);
  for (int i = 0; i < this->width + this->width - 1; i++)
  {
    res.pMem[i] = pMem[i] + m.pMem[i];
  }

  return res;
}

template<typename T>
inline TLentDynamicMatrix<T> TLentDynamicMatrix<T>::operator-(const TLentDynamicMatrix<T>& m)
{
  if ((this->sz != m.sz) || (this->width != m.width)) throw "operator-(const TLentDynamicMatrix<T>& m) sz != m.sz || width != m.width";
  TLentDynamicMatrix<T> res(sz, width);
  for (int i = 0; i < this->width + this->width - 1; i++)
  {
    res.pMem[i] = pMem[i] - m.pMem[i];
  }

  return res;
}

template<typename T>
inline std::istream& operator>>(std::istream& istr, TLentDynamicMatrix<T>& v)
{
  int tmp = 0;
  bool flag = true;
  v.pMem = new TDynamicVector<T>[v.width + v.width - 1];
  for (int i = 0; i < v.width + v.width - 1; i++)
  {
    if ((flag == true) && (tmp != (v.width)))
    {
      tmp++;
    }
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
inline std::ostream& operator<<(std::ostream& ostr, const TLentDynamicMatrix<T>& v)
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
