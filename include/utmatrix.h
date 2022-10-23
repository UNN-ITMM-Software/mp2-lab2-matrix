// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TMatrix_H__
#define __TMatrix_H__


#include <iostream>
#include <algorithm>

typedef unsigned int uint;
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
// шаблонный вектор на динамической памяти

template <class Type>
class TVector
{
protected:
    Type* pVector;
    int Size;       // размер вектора
    int StartIndex; // индекс первого элемента вектора
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);                
    ~TVector();
    int GetSize() { return Size; } 
    int GetStartIndex() { return StartIndex; } 
    Type& operator[](int pos);             

    bool operator==(const TVector& v) const;  //сравнение
    bool operator!=(const TVector& v) const;  

    TVector& operator=(const TVector& v);     //приравнивание

    // скалярные операции (with const)
    TVector  operator+(const Type& val);   // прибавить скаляр
    TVector  operator-(const Type& val);   // вычесть скаляр
    TVector  operator*(const Type& val);   // умножить на скаляр

    // векторные операции
    TVector  operator+(const TVector& v);     // сложение
    TVector  operator-(const TVector& v);     // вычитание
    Type  operator*(const TVector& v);     // скалярное произведение

    // ввод/вывод
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

template <class Type>
TVector<Type>::TVector(int s, int si)
{
    if (s < 0 || s > MAX_VECTOR_SIZE || si < 0 || si > MAX_VECTOR_SIZE)
        throw "Out of bounds of vector dimension when creating a vector";
    this->Size = s;
    StartIndex = si;
    pVector = new Type[Size];
    for (int i = 0; i < Size; i++)
        pVector[i] = 0;
} 

template <class Type> //конструктор копирования
TVector<Type>::TVector(const TVector<Type>& v)
{
    Size = v.Size;
    pVector = new Type[v.Size];
    StartIndex = v.StartIndex;
    for (int i = 0; i < Size; i++)
        this->pVector[i] = v.pVector[i];
} 

template <class Type>
TVector<Type>::~TVector()
{
    delete[]this->pVector;
} 

template <class Type> // доступ
Type& TVector<Type>::operator[](int pos)
{
    if (pos < StartIndex || pos > StartIndex + Size - 1)
        throw "Pos out of range getting a value by index";
    else
        return pVector[pos - StartIndex];
} 

template <class Type> // сравнение
bool TVector<Type>::operator==(const TVector& v) const
{
    
    if (Size != v.Size) return false;
    if (StartIndex != v.StartIndex) return false;
    for (int i = 0; i < Size; i++) {
        if (pVector[i] != v.pVector[i])
            return false;
    }

    return true;
} 

template <class Type> // сравнение
bool TVector<Type>::operator!=(const TVector& v) const
{
    return !(*this == v);
} 

template <class Type> // присваивание
TVector<Type>& TVector<Type>::operator=(const TVector& v)
{
    if (this != &v) {
        if (Size != v.Size) {
            delete[] pVector;
            Size = v.Size;
            pVector = new Type[Size];
        }
        StartIndex = v.StartIndex;
        for (int i = 0; i < Size; i++)
            pVector[i] = v.pVector[i];
    }
    return *this;
} 

template <class Type> // прибавить скаляр
TVector<Type> TVector<Type>::operator+(const Type& val)
{
    TVector<Type> result(*this);
    for (int i = 0; i < Size; i++)
        result.pVector[i] += val;
    return result;
} 

template <class Type> // вычесть скаляр
TVector<Type> TVector<Type>::operator-(const Type& val)
{
    TVector<Type> result(*this);
    for (int i = 0; i < Size; i++)
        result.pVector[i] -= val;
    return result;
} 

template <class Type> // умножить на скаляр
TVector<Type> TVector<Type>::operator*(const Type& val)
{
    TVector<Type> result(*this);
    for (int i = 0; i < Size; i++)
        result.pVector[i] *= val;
    return result;
} 

template <class Type> // сложение
TVector<Type> TVector<Type>::operator+(const TVector<Type>& v)
{
    if (this->Size + this->StartIndex != v.Size + v.StartIndex)
        throw "Can't add vectors with not equal sizes";

    uint size_diff, result_size = max(this->Size, v.Size);
    uint result_si = min(this->StartIndex, v.StartIndex);

    TVector<Type> result(result_size, result_si);
    if (result_size > Size) {
        size_diff = v.Size - Size;
        for (int i = 0; i < size_diff; i++) {
            result.pVector[i] = v.pVector[i];
        }
        for (int i = 0; i < Size; i++) {
            result.pVector[i + size_diff] = pVector[i] + v.pVector[i + size_diff];
        }
        }
    else {
        size_diff = Size - v.Size;
        for (int i = 0; i < size_diff; i++) {
            result.pVector[i] = this->pVector[i];
        }
        for (int i = 0; i < v.Size; i++) {
            result.pVector[i + size_diff] = pVector[i + size_diff] + v.pVector[i];
        }
    }

    return result;
} 

template <class Type> // вычитание
TVector<Type> TVector<Type>::operator-(const TVector<Type>& v)
{
    if (this->Size + this->StartIndex != v.Size + v.StartIndex)
        throw "Can't subtract vectors with not equal sizes";

    uint size_diff, result_size = max(this->Size, v.Size);
    uint result_si = min(this->StartIndex, v.StartIndex);

    TVector<Type> result(result_size, result_si);
    if (result_size > Size) {
        size_diff = v.Size - Size;
        for (int i = 0; i < size_diff; i++) {
            result.pVector[i] =  /*(-1)*/ v.pVector[i] * (-1);
        }
        for (int i = 0; i < Size; i++) {
            result.pVector[i + size_diff] = pVector[i] - v.pVector[i + size_diff];
        }
    }
    else {
        size_diff = Size - v.Size;
        for (int i = 0; i < size_diff; i++) {
            result.pVector[i] = this->pVector[i];
        }
        for (int i = 0; i < v.Size; i++) {
            result.pVector[i + size_diff] = pVector[i + size_diff] - v.pVector[i];
        }
    }

    return result;
} 

template <class Type> // скалярное произведение
Type TVector<Type>::operator*(const TVector<Type>& v)
{
    if (this->Size + this->StartIndex != v.Size + v.StartIndex)
        throw "Can't scalar multiply vectors with not equal sizes";

    uint size_diff;
    Type scalar = 0;
    if (this->Size > v.Size) {
        size_diff = this->Size - v.Size;
        for (int i = 0; i < v.Size; i++) {
            scalar += pVector[i + size_diff] * pVector[i];
        }
    }
    else {
        size_diff = v.Size - this->Size;
        for (int i = 0; i < this->Size; i++) {
            scalar += pVector[i] * v.pVector[i];
        }
    }

    return scalar;
} 


// Верхнетреугольная матрица
template <class Type>
class TMatrix : public TVector<TVector<Type> >
{
public:
    TMatrix(int s = 10);
    TMatrix(const TMatrix& mt);                    // копирование
    TMatrix(const TVector<TVector<Type> >& mt); // преобразование типа

    bool operator==(const TMatrix& mt) const;      // сравнение
    bool operator!=(const TMatrix& mt) const;      // сравнение

    TMatrix& operator= (const TMatrix& mt);        // присваивание
    TMatrix  operator+ (const TMatrix& mt);        // сложение
    TMatrix  operator- (const TMatrix& mt);        // вычитание

    // ввод / вывод
    friend istream& operator>>(istream& in, TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            in >> mt.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            out << mt.pVector[i] << endl;
        return out;
    }
};

template <class Type>
TMatrix<Type>::TMatrix(int s) : TVector<TVector<Type> >(s)
{
    if (s < 0 || s > MAX_MATRIX_SIZE)
        throw "Out of bounds of matrix dimension when creating a matrix";
    for (int i = 0; i < s; i++) {
        TVector<Type> elem(s - i, i);
        pVector[i] = elem;
    }
} 

template <class Type> // конструктор копирования
TMatrix<Type>::TMatrix(const TMatrix<Type>& mt) :
    TVector<TVector<Type> >(mt) {}

template <class Type> // конструктор преобразования типа
TMatrix<Type>::TMatrix(const TVector<TVector<Type> >& mt) :
    TVector<TVector<Type> >(mt) {}

template <class Type> // сравнение
bool TMatrix<Type>::operator==(const TMatrix<Type>& mt) const
{
    return TVector< TVector<Type> >::operator==(mt);
} 

template <class Type> // сравнение
bool TMatrix<Type>::operator!=(const TMatrix<Type>& mt) const
{
    return !(*this == mt);
} 

template <class Type> // присваивание
TMatrix<Type>& TMatrix<Type>::operator=(const TMatrix<Type>& mt)
{
    TVector< TVector<Type> >::operator=(mt);
    return *this;
} 

template <class Type> // сложение
TMatrix<Type> TMatrix<Type>::operator+(const TMatrix<Type>& mt)
{
    return TVector< TVector<Type> >::operator+(mt);
} 

template <class Type> // вычитание
TMatrix<Type> TMatrix<Type>::operator-(const TMatrix<Type>& mt)
{
    return TVector< TVector<Type> >::operator-(mt);
} 

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
