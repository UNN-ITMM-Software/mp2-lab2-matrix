#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <utility>
#include <string>

using namespace std;


const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;


//*    ---класс Вектор---
template <class ValType>
class TVector
{
protected:
  ValType* pVector;
  int Size;       // размер 
  int StartIndex; // индекс 
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector& v);                 // копирования
  ~TVector();                                // деструктор
  int GetSize() { return Size; }             // получить размер
  int GetStartIndex() { return StartIndex; } // получить индекс первого элемента
  ValType& operator[](int pos);              // индекс 
  bool operator==(const TVector& v) const;   // сравнение
  bool operator!=(const TVector& v) const;   // сравнение
  TVector& operator=(const TVector& v);      // присваивание

  TVector  operator+(const ValType& val);    // прибавить скаляр
  TVector  operator-(const ValType& val);    // вычесть скаляр
  TVector  operator*(const ValType& val);    // умножить на скаляр

  TVector  operator+(const TVector& v);      // сложение
  TVector  operator-(const TVector& v);      // вычитание
  ValType  operator*(const TVector& v);      // скалярное произведение

  friend istream& operator>>(istream& in, TVector& v)  //ввод
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }

  friend ostream& operator<<(ostream& out, const TVector& v) //вывод
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si)
{
  if ((s < 1) || (s > MAX_VECTOR_SIZE) || (si < 0) || (si > MAX_MATRIX_SIZE - 1))
    throw string("Wrong arguments");
  pVector = new ValType[s]{};
}

template <class ValType>
TVector<ValType>::TVector(const TVector<ValType>& v)
{
  Size = v.Size;
  StartIndex = v.StartIndex;
  pVector = new ValType[Size];
  for (int i = 0; i < Size; i++)
    pVector[i] = v.pVector[i];
}

template <class ValType>
TVector<ValType>::~TVector()
{
  delete[] pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos)
{
  pos -= StartIndex;
  if ((pos < 0) || (pos >= Size))
    throw string("Wrong argument");
  return pVector[pos];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const
{
  if (this == &v)
    return true;
  if (Size != v.Size)
    return false;
  if (StartIndex != v.StartIndex)
    return false;
  for (int i = 0; i < Size; i++) {
    if (pVector[i] != v.pVector[i])
      return false;
  }
  return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const
{
  return !(*this == v);
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
  if (this == &v)
    return *this;
  if (Size != v.Size) {
    ValType* tmp = new ValType[v.Size];
    delete[] pVector;
    pVector = tmp;
    Size = v.Size;
  }
  StartIndex = v.StartIndex;
  for (int i = 0; i < Size; i++)
    pVector[i] = v.pVector[i];
  return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
  TVector<ValType> out(Size, StartIndex);
  for (int i = 0; i < Size; i++)
    out.pVector[i] = pVector[i] + val;
  return out;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
  TVector<ValType> out(Size, StartIndex);
  for (int i = 0; i < Size; i++)
    out.pVector[i] = pVector[i] - val;
  return out;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
  TVector<ValType> out(Size, StartIndex);
  for (int i = 0; i < Size; i++)
    out.pVector[i] = pVector[i] * val;
  return out;

}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
  if ((Size != v.Size) || (StartIndex != v.StartIndex))
    throw string("Different size of TVector's");
  TVector<ValType> out(Size, StartIndex);
  for (int i = 0; i < Size; i++)
    out.pVector[i] = pVector[i] + v.pVector[i];
  return out;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
  if ((Size != v.Size) || (StartIndex != v.StartIndex))
    throw string("Different size of TVector's");
  TVector<ValType> out(Size, StartIndex);
  for (int i = 0; i < Size; i++)
    out.pVector[i] = pVector[i] - v.pVector[i];
  return out;

}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
  if ((Size != v.Size) || (StartIndex != v.StartIndex))
    throw string("Different size of TVector's");
  ValType sum = 0;
  for (int i = 0; i < Size; i++)
    sum += pVector[i] * v.pVector[i];
  return sum;
}


//*           ---Верхнетреугольная матрица---
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           // констуктор
  TMatrix(const TMatrix& mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> >& mt); // преобразование типа
  bool operator==(const TMatrix& mt) const;      // сравнение
  bool operator!=(const TMatrix& mt) const;      // сравнение
  TMatrix& operator= (const TMatrix& mt);        // присваивание
  TMatrix  operator+ (const TMatrix& mt);        // сложение
  TMatrix  operator- (const TMatrix& mt);        // вычитание

  friend istream& operator>>(istream& in, TMatrix& mt) //ввод
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }

  friend ostream& operator<<(ostream& out, const TMatrix& mt) //вывод
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s)
{
  if ((s < 1) || (s > MAX_MATRIX_SIZE))
    throw string("Wrong argument");
  for (int i = 0; i < s; i++) {
    TVector<ValType> tmp(s - i, i);
    this->pVector[i] = tmp;
  }
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
  TVector<TVector<ValType> >(mt) {}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
  TVector<TVector<ValType> >(mt) {}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
  return TVector<TVector<ValType>>:: operator==(mt);
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
  return !(*this == mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
  if (this == &mt)
    return *this;
  TVector<ValType>* tmp = new TVector<ValType>[mt.Size];
  delete[] this->pVector;
  this->pVector = tmp;
  this->Size = mt.Size;
  for (int i = 0; i < this->Size; i++) {
    this->pVector[i] = mt.pVector[i];
  }
  return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
  return TVector<TVector<ValType>>:: operator+(mt);
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
  return TVector<TVector<ValType>>:: operator-(mt);
}

#endif