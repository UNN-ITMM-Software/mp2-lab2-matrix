// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  virtual ~TVector();
  int GetSize()      const { return Size;       } // размер вектора
  int GetStartIndex()const { return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if (s < 0)               throw "size must be non-negative";
    if (MAX_VECTOR_SIZE < s) throw "size must be less than MAX_MATRIX_SIZE";
    if (si < 0)              throw "start index must be non-negative";

    this->Size = s;
    this->StartIndex = si;
    this->pVector = new ValType[s];

    for (int i = 0; i < this->Size; i++)
        this->pVector[i] = 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
    this->Size = v.Size;
    this->StartIndex = v.StartIndex;
    this->pVector = new ValType[v.Size];

    for (int i = 0; i < this->Size; i++)
        this->pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] this->pVector;
    this->pVector = NULL;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    if (pos < this->StartIndex || this->StartIndex + this->Size < pos)
        throw "invalid position";

    return this->pVector[pos - this->StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
    if (this->Size != v.Size)             return false;
    if (this->StartIndex != v.StartIndex) return false;

    for (int i = 0; i < Size; i++)
        if (pVector[i] != v.pVector[i])
            return false;

    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (this == &v) return *this;

    this->StartIndex = v.StartIndex;
    this->Size = v.Size;

    delete[] this->pVector;
    this->pVector = NULL;

    this->pVector = new ValType[this->Size];
    if (this->pVector == NULL)
        throw "cannot allocate memory";

    for (int i = 0; i < this->Size; i++)
        this->pVector[i] = v.pVector[i];

    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
    TVector<ValType> sum(this->Size - this->StartIndex, 0);

    for (int i = 0; i < sum.Size; i++)
        sum.pVector[i] = this->pVector[i] + val;

    return sum;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
    TVector<ValType> sub(this->Size - this->StartIndex, 0);

    for (int i = 0; i < sub.Size; i++)
        sub.pVector[i] = this->pVector[i] - val;

    return sub;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
    TVector<ValType> mul(this->Size - this->StartIndex, 0);

    for (int i = 0; i < mul.Size; i++)
        mul.pVector[i] = this->pVector[i] * val;

    return mul;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
    if (this->GetSize()       != v.GetSize())       throw "vectors must have equal sizes";
    if (this->GetStartIndex() != v.GetStartIndex()) throw "vectors must have equal start index";

    TVector<ValType> sum(this->GetSize(), this->GetStartIndex());

    for (int i = 0; i < sum.GetSize(); i++)
        sum.pVector[i] = this->pVector[i] + v.pVector[i];

    return sum;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
    if (this->GetSize()       != v.GetSize())       throw "vectors must have equal sizes";
    if (this->GetStartIndex() != v.GetStartIndex()) throw "vectors must have equal start index";

    TVector<ValType> sub(this->GetSize(), this->GetStartIndex());

    for (int i = 0; i < sub.GetSize(); i++)
        sub.pVector[i] = this->pVector[i] - v.pVector[i];

    return sub;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
    if (this->GetSize()       != v.GetSize())       throw "vectors must have equal sizes";
    if (this->GetStartIndex() != v.GetStartIndex()) throw "vectors must have equal start index";

    ValType dot = 0;

    for (int i = 0; i < v.GetSize(); i++)
        dot += this->pVector[i] * v.pVector[i];

    return dot;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
    if (s < 0)               throw "size must be non-negative";
    if (MAX_MATRIX_SIZE < s) throw "size must be less or equal MAX_MATRIX_SIZE";

    for (int i = 0; i < s; i++)
        this->pVector[i] = TVector<ValType>(s - i, i);
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    if (this->Size != mt.Size) return false;

    for (int i = 0; i < this->Size; i++)
        if (this->pVector[i] != mt.pVector[i])
            return false;

    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !(*this==mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
    if (this == &mt) return *this;

    this->Size = mt.GetSize();

    delete[] this->pVector;
    this->pVector = NULL;
    this->pVector = new TVector<ValType>[mt.GetSize()];

    this->StartIndex = mt.GetStartIndex();

    for (int i = 0; i < this->Size; i++)
        this->pVector[i] = mt.pVector[i];

    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    if (this->Size != mt.Size) throw "matrix must be equal size";

    TMatrix<ValType> sum(this->Size);
    for (int i = 0; i < this->Size; i++)
        sum[i] = this->pVector[i] + mt.pVector[i];

    return sum;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    if (this->Size != mt.Size) throw "matrix must be equal size";

    TMatrix<ValType> sub(this->Size);
    for (int i = 0; i < this->Size; i++)
        sub[i] = this->pVector[i] - mt.pVector[i];

    return sub;
} /*-------------------------------------------------------------------------*/
#endif
