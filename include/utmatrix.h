// Copyright 2016 AuthorName. All rights reserved.
// ННГУ, ВМК, Курс "Методы пр
// ограммирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual
// Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реал
// изация на основе шаблона вектора
#ifndef INCLUDE_UTMATRIX_H_
#define INCLUDE_UTMATRIX_H_
#include <iostream>
#include <cmath>
using std::endl;
using std::ostream;
using std::istream;
const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;
// Шаблон вектора
template <class ValType>
class TVector {
 protected:
    ValType *pVector;
    int Size;  // размер вектора
    int StartIndex;
    // индекс первого элемента вектора
    ValType neutralVal;

 public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector &v);  // конструктор копирования
    ~TVector();
    int GetSize()      { return Size;       }  // размер вектора
    int GetStartIndex() { return StartIndex; }
    // индекс первого элемента
    ValType& operator[](int pos);  // доступ
    bool operator==(const TVector &v) const;  // сравнение
    bool operator!=(const TVector &v) const;  // сравнение
    TVector& operator=(const TVector &v);  // присваивание
    // скалярные операции
    TVector  operator+(const ValType &val);  // прибавить скаляр
    TVector  operator-(const ValType &val);  // вычесть скаляр
    TVector  operator*(const ValType &val);
    // умножить на скаляр
    // векторные операции
    TVector  operator+(const TVector &v);  // сложение
    TVector  operator-(const TVector &v);  // вычитание
    ValType  operator*(const TVector &v);
    // скалярное произведение
    // ввод-вывод
    friend istream& operator>>(istream &in, TVector &v) {
      for (int i = 0; i < v.Size; i++)
        in >> v.pVector[i];
      return in;
    }
    friend ostream& operator<<(ostream &out, const TVector &v) {
      //for (int i = 0; i < v.StartIndex; i++)
      //  out << (ValType)0 << ' ';
      for (int i = 0; i < v.Size; i++)
        out << v.pVector[i] << ' ';
      return out;
    }
};
template <class ValType>
TVector<ValType>::TVector(int s, int si) {
  if (s > MAX_VECTOR_SIZE || s < 0 || si < 0 || si > MAX_VECTOR_SIZE)
    throw "Invalid arg(-s) in vector's constructor(int, int)";
  Size = s;
  StartIndex = si;
  pVector = new ValType[Size];
  for (int i = 0; i < s; i++)
    pVector[i] = (ValType)0;
} /*-------------------------------------------------------------------------*/
template <class ValType>
// конструктор копирования :: сделан
TVector<ValType>::TVector(const TVector<ValType> &v) {
  Size = v.Size;
  StartIndex = v.StartIndex;
  pVector = new ValType[Size];
  if (pVector == NULL)
    throw "Invalid allocating of mem for pVector in Vector(Vector&)";
  for (int i = 0; i < Size; i++)
    pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/
//++++++++
template <class ValType>
TVector<ValType>::~TVector() {
  delete[] pVector;
  Size = StartIndex = 0;
} /*-------------------------------------------------------------------------*/
//++++++++
template <class ValType>  // доступ
ValType& TVector<ValType>::operator[](int pos) {
  if (pos < 0 || pos >= Size+StartIndex)
    throw "Invalid index in operator[]";
  neutralVal = (ValType)0;
  if (pos < StartIndex)
    return neutralVal;
  return pVector[pos-StartIndex];
} /*-------------------------------------------------------------------------*/
//++++
template <class ValType>  // сравнение
bool TVector<ValType>::operator==(const TVector &v) const {
  if (Size != v.Size)
    return false;
  for (int i = 0; i < Size; i++)
    if (pVector[i] != v.pVector[i])
      return false;
  return true;
} /*-------------------------------------------------------------------------*/
//++++
template <class ValType>  // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const {
  if (Size != v.Size)
    return true;
  for (int i = 0; i < Size; i++)
    if (pVector[i] != v.pVector[i])
      return true;
  return false;
} /*-------------------------------------------------------------------------*/
// ++++
template <class ValType>  // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v) {
  if (pVector != v.pVector && Size != v.Size) {
    Size = v.Size;
    delete[] pVector;
    pVector = new ValType[Size];
    if (pVector == NULL)
      throw "Invalid allocation of memory while copying of pVector";
  }
  StartIndex = v.StartIndex;
  for (int i = 0; i < Size; i++)
    pVector[i] = v.pVector[i];
  return *this;
} /*-------------------------------------------------------------------------*/
//++++
template <class ValType>  // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val) {
  TVector<ValType> res(*this);
  for (int i = 0; i < Size; i++)
    res.pVector[i] += val;
  return res;
} /*-------------------------------------------------------------------------*/
//++++
template <class ValType>  // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val) {
  TVector<ValType> res(*this);
  for (int i = 0; i < Size; i++)
    res.pVector[i] -= val;
  /*
  ValType vNorm = 0;
  for (int i = 0; i < Size; i++)
    vNorm += pVector[i] * pVector[i];
  vNorm = sqrt(vNorm);
  return res - res *(val*1.0f/vNorm);
  */
  return res;
} /*-------------------------------------------------------------------------*/
//+++++
template <class ValType>  // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val) {
  TVector<ValType> res(*this);
  for (int i = 0; i < Size; i++)
    res.pVector[i] *= val;
  return res;
} /*-------------------------------------------------------------------------*/
//++++
template <class ValType>  // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v) {
  if (Size != v.Size)
    throw "Invalid addition: sizes aren't equal";
  TVector<ValType> res(*this);
  for (int i = 0; i < Size; i++)
    res.pVector[i] += v.pVector[i];
  return res;
} /*-------------------------------------------------------------------------*/
//+++++
template <class ValType>  // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v) {
  if (Size != v.Size)
    throw "Invalid subtraction: sizes aren't equal";
  TVector<ValType> res(*this);
  for (int i = 0; i < Size; i++)
    res.pVector[i] -= v.pVector[i];
  return res;
} /*-------------------------------------------------------------------------*/
//++++++++
template <class ValType>  // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v) {
  if (Size != v.Size)
    throw "Invalid scalar multiplication: sizes aren't equal";
  ValType sum = 0;
  for (int i = 0; i < Size; i++)
    sum += pVector[i] * v.pVector[i];
  return sum;
} /*-------------------------------------------------------------------------*/
// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> > {
    typedef TVector<TVector<ValType> > Base;

 public:
    explicit TMatrix(int s = 10);
    TMatrix(const TMatrix &mt);  // копирование
    TMatrix(const TVector<TVector<ValType> > &mt);
    // преобразование типа
    bool operator==(const TMatrix &mt) const;  // сравнение
    bool operator!=(const TMatrix &mt) const;  // сравнение
    TMatrix& operator= (const TMatrix &mt);  // присваивание
    TMatrix  operator+ (const TMatrix &mt);  // сложение
    TMatrix  operator- (const TMatrix &mt);  // вычитание
    // ввод / вывод
    friend istream& operator>>(istream &in, TMatrix &mt) {
      for (int i = 0; i < mt.Size; i++)
        in >> mt.pVector[i];
      return in;
    }
    friend ostream & operator<<(ostream &out, const TMatrix &mt) {
      for (int i = 0; i < mt.Size; i++)
        out << mt.pVector[i] << endl;
      return out;
    }
};
template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s) {
    if (s < 0 || s > MAX_MATRIX_SIZE)
        throw "Invalid making of TMatrix(int)";
  Base::Size = s;
  Base::StartIndex = 0;
  for (int i = 0; i < Base::Size; i++)
        Base::pVector[i] = TVector<ValType>(s-i, i);
} /*-------------------------------------------------------------------------*/
template <class ValType>  // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) : Base(mt) {
  Base::Size = mt.Size;
  Base::StartIndex = 0;
  for (int i = 0; i < Base::Size; i++)
    Base::pVector[i] = mt.pVector[i];
}
template <class ValType>
// конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >
&mt) : TVector<TVector<ValType> >(mt)
{}
template <class ValType>  // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const {
  return Base::pVector == mt.pVector;
  if (mt.Size != Base::Size)
    return false;
  for (int i = 0; i < Base::Size; i++)
    if (mt.pVector[i] != Base::pVector[i])
      return false;
  return true;
} /*-------------------------------------------------------------------------*/
template <class ValType>  // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const {
  return Base::operator==(mt.pVector);
  if (mt.Size != Base::Size)
    return true;
  for (int i = 0; i < Base::Size; i++)
    if (mt.pVector[i] != Base::pVector[i])
      return true;
  return false;
} /*-------------------------------------------------------------------------*/
template <class ValType>  // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt) {
  Base::StartIndex = mt.StartIndex;
  if (Base::pVector == mt.pVector)
    return *this;
  Base::Size = mt.Size;
  for (int i = 0; i < Base::Size; i++)
    Base::pVector[i] = mt.pVector[i];
  return *this;
} /*-------------------------------------------------------------------------*/
template <class ValType>  // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt) {
  TMatrix<ValType> sum(*this);
  if (mt.Size != Base::Size)
    throw "Ivalid matrix subtraction: sizes aren't equal";
  for (int i = 0; i < Base::Size; i++)
    sum.pVector[i] = Base::pVector[i] + mt.pVector[i];
  return sum;
} /*-------------------------------------------------------------------------*/
template <class ValType>  // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt) {
  TMatrix<ValType> sub(*this);
  Base::StartIndex = mt.StartIndex;
  if (mt.Size != Base::Size)
    throw "Ivalid matrix subtraction: sizes aren't equal";
  for (int i = 0; i < Base::Size; i++)
    sub.pVector[i] = Base::pVector[i] - mt.pVector[i];
  return sub;
} /*-------------------------------------------------------------------------*/
// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif  // INCLUDE_UTMATRIX_H_
