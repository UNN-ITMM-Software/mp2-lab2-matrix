// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

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
    ValType* pVector = nullptr;
    int Size;       // размер вектора
    int StartIndex; // индекс первого элемента вектора
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);                // конструктор копирования
    ~TVector();
    int GetSize() const                       // размер вектора
    {
	    return Size;
    } 
    int GetStartIndex() const                 // индекс первого элемента
    {
	    return StartIndex;
    } 
    ValType& operator[](int pos);             // доступ
    bool operator==(const TVector& v) const;  // сравнение
    bool operator!=(const TVector& v) const;  // сравнение
    TVector& operator=(const TVector& v);     // присваивание

    // скалярные операции
    TVector  operator+(const ValType& val);   // прибавить скаляр
    TVector  operator-(const ValType& val);   // вычесть скаляр
    TVector  operator*(const ValType& val);   // умножить на скаляр

    // векторные операции
    TVector  operator+(const TVector& v);     // сложение
    TVector  operator-(const TVector& v);     // вычитание
    ValType  operator*(const TVector& v);     // скалярное произведение

    // ввод-вывод
    friend istream& operator>>(istream& in, TVector& v)
    {
        for (int i = 0; i < v.Size; i++)
            in >> v.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TVector& v)
    {
        for (int i = 0; i < v.Size; i++)
            out << v.pVector[i] << ' ';
        return out;
    }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if (s < 0 || s > MAX_VECTOR_SIZE || si < 0)
        throw "incorrect data for vector creation";
    Size = s;
    StartIndex = si;
    pVector = new ValType[s];
    for (int i = 0; i < Size; i++)
    {
        pVector[i] = 0;
    }
}
/*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v)
{
    Size = v.Size;
    StartIndex = v.StartIndex;
    delete pVector;
    pVector = new ValType[Size];
    for (int i = 0; i < Size; ++i)
    {
        pVector[i] = v.pVector[i];
    }
}
/*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
    pVector = nullptr;
}
/*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    if (pos > (StartIndex + Size) || pos < StartIndex)
        throw "index is out of bounds";
    return pVector[pos - StartIndex];
}
/*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
    if (this == &v)
        return true;
    if (Size != v.Size)
        return false;
    for (size_t i = 0; i < Size; i++)
        if (pVector[i] != v.pVector[i])
            return false;
    return true;
}
/*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector& v) const
{
    return !(*this == v);
}
/*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (this == &v)
        return *this;
	if(v.Size != Size)
	{
        delete[] pVector;
        pVector = new ValType[v.Size];
	}
    Size = v.Size;
    StartIndex = v.StartIndex;
	for(size_t i = 0; i < Size; ++i)
	{
        pVector[i] = v.pVector[i];
	}
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
    TVector<ValType> tmp(*this);
    for (int i = 0; i < Size; i++)
    {
        tmp.pVector[i] += val;
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
    TVector<ValType> tmp(*this);
    for (int i = 0; i < Size; i++)
    {
        tmp.pVector[i] -= val;
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
    TVector<ValType> tmp(*this);
    for (int i = 0; i < Size; i++)
    {
        tmp.pVector[i] *= val;
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
    if (Size + StartIndex != v.Size + v.StartIndex)
        throw "lengths of vectors are different";
    TVector<ValType> tmp;
    if (Size > v.Size) {
        tmp.Size = Size;
        tmp.StartIndex = StartIndex;
        for (int i = 0; i < v.StartIndex - StartIndex; i++)             
        {
            tmp.pVector[i] = pVector[i];
        }
        for (int i = v.StartIndex - StartIndex; i < tmp.Size; ++i) 
        {
            tmp.pVector[i] = pVector[i] + v.pVector[i - v.StartIndex + StartIndex];
        }
    }
    else {
        tmp.Size = v.Size;
        tmp.StartIndex = v.StartIndex;
        for (int i = 0; i < StartIndex - v.StartIndex; i++)             
        {
            tmp.pVector[i] = v.pVector[i];
        }
        for (int i = StartIndex - v.StartIndex; i < tmp.Size; ++i) 
        {
            tmp.pVector[i] = v.pVector[i] + pVector[i - StartIndex + v.StartIndex];
        }
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
    if (Size + StartIndex != v.Size + v.StartIndex)
        throw "lengths of vectors are different";
    TVector<ValType> tmp;
    if (Size > v.Size) {
        tmp.Size = Size;
        tmp.StartIndex = StartIndex;
        for (int i = 0; i < v.StartIndex - StartIndex; i++)             
        {
            tmp.pVector[i] = pVector[i];
        }
        for (int i = v.StartIndex - StartIndex; i < tmp.Size; i++) 
        {
            tmp.pVector[i] = pVector[i] - v.pVector[i - v.StartIndex + StartIndex];
        }
    }
    else {
        tmp.Size = v.Size;
        tmp.StartIndex = v.StartIndex;
        for (int i = 0; i < StartIndex - v.StartIndex; i++)             
        {
            tmp.pVector[i] = v.pVector[i];
        }
        for (int i = StartIndex - v.StartIndex; i < tmp.Size; ++i) 
        {
            tmp.pVector[i] = v.pVector[i] - pVector[i - StartIndex + v.StartIndex];
        }
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
    if (Size + StartIndex != v.Size + v.StartIndex)
        throw "lengths of vectors are different";
    ValType tmp = 0;
    if (Size > v.Size) 
    {
        for (int i = 0; i < v.Size; i++)             
        {
            tmp += pVector[i + v.StartIndex - StartIndex] * v.pVector[i];
        }
    }
    else
    {
        for (int i = 0; i < Size; ++i)
        {
            tmp += pVector[i] * v.pVector[i + StartIndex - v.StartIndex];
        }
    }
    return tmp;
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
      {
          for (int j = 0; j < i; j++)
              out << 0 << ' ';
          out << mt.pVector[i] << endl;
      }
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s)
{
    if ((s <= 0) || (s > MAX_MATRIX_SIZE))
        throw ("negative size or very big size");
    for (int i = 0; i < s; i++)
        pVector[i] = TVector<ValType>(s - i, i);
}
/*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) : TVector<TVector<ValType> >(mt)
{
    Size = mt.Size;
    StartIndex = mt.StartIndex;
    pVector = new TVector<ValType>[Size];
    for (int i = 0; i < Size; i++)
        pVector[i] = mt.pVector[i];
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt){}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
    return TVector<TVector<ValType>>::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
    TVector<TVector<ValType>>::operator=(mt);
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    return TVector<TVector<ValType>>::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    return TVector<TVector<ValType>>::operator-(mt);
} /*-------------------------------------------------------------------------*/

#endif
