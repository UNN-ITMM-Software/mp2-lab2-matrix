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
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
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
    for (int i = 0; i < v.StartIndex; i++)
      out << "0" << ' ';
	for (int j = v.StartIndex; j < v.Size; j++)
		out << pVector[j - v.StartIndex] << " ";
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((si < 0) && (s <= 0) && (s > MAX_VECTOR_SIZE)) {
		throw "error";
	}
	else {
		Size = s;
		StartIndex = si;
		pVector = new ValType[Size];
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++) {
		pVector[i] = v.pVector[i];
	}
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delet[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos >= 0) && (pos - StartIndex <= Size)) {
		if (pos >= StartIndex) {
			return pVector[pos - StartIndex];
		}
		else
			throw "error";
	}
	else
		throw "error";
	//return pVector()
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.Size) {
		return false;
	}
	if (StartIndex != v.StartIndex) {
		return false;
	}
	else
	{
		for (int i = 0; i < Size; i++) {
			if (pVector[i] != v.pVector[i]) {
				return false;
			}
		}
	}
	return try;

} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	if (Size == v.Size) {
		return false;
	}
	if (StartIndex == v.StartIndex) {
		return false;
	}
	else
	{
		for (int i = 0; i < Size; i++) {
			if (pVector[i] == v.pVector[i]) {
				return false;
			}
		}
	}
	return try;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (Size != v.Size) {
		delet[] pVector;
		pVector = new ValType(v.Size);
	}
	Size = v.Size;
	StartIndex = v.StartIndex;
	for (int i = 0; i < Size; i++) {
		pVector[i] = v.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector tmp(Size, StartIndex);
	for (int i = 0; i < Size; i++) {
		tmp.pVector[i] = tmp.pVector[i] + val;
	}
	return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector tmp(Size, StartIndex);
	for (int i = 0; i < Size; i++) {
		tmp.pVector[i] = tmp.pVector[i] - val;
	}
	return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector tmp(Size, StartIndex);
	for (int i = 0; i < Size; i++) {
		tmp.pVector[i] = tmp.pVector[i] * val;
	}
	return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size == v.Size) {
		TVector tmp(Size, StartIndex);
		for (int i = 0; i < Size; i++) {
			tmp.pVector = pVector[i] + v.pVector;
		}
		return tmp;
	}
	else
		throw "error";
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size == v.Size) {
		TVector tmp(Size, StartIndex);
		for (int i = 0; i < Size; i++) {
			tmp.pVector = pVector[i] - v.pVector;
		}
		return tmp;
	}
	else
		throw "error";
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (Size == v.Size) {
		ValType tmp = 0;
		for (int i = 0; i < Size; i++) {
			tmp = tmp + (pVector[i] * v.pVector);
		}
		return tmp;
	}
	else
		throw "error";
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
	if ((s < 0) || (s > MAX_MATRIX_SIZE)) {
		throw "error";
	}
	else
		for (int i = 0; i < s; i++) {
			pVector[i] = TVector<ValType>(s, i);
		}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt.Size) 
{
	Size = mt.Size;
	StarIndex = mt.StarIndex;
	for (int i = 0; i < Size; i++) {
		pVector[i] = mt.pVector;
	}
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt.Size) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	int tmp = 0;
	if (Size != mt.Size) {
		return false;
		for (int i = 0; i < Size; i++) {
			if (pVector[i] != mt.pVector)
				tmp++;
		}
		if (tmp != mt.Size) {
			return false;
		}
		else {
			return try;
		}
	else {
		return try;
	}
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	int tmp = 0;
	if (Size == mt.Size) {
		return false;
		for (int i = 0; i < Size; i++) {
			if (pVector[i] == mt.pVector)
				tmp++;
		}
		if (tmp == mt.Size) {
			return false;
		}
		else {
			return try;
		}
	else {
		return try;
	}
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	Size = mt.Size;
	TMatrix<ValType>(Size);
	for (int i = 0; i < Size; i++) {
		pVector[i] = mt.pVector;
	}
	return this*;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (Size == mt.Size) {
		TMatrix<ValType>tmp(Size);
		for (int i = 0; i < Size; i++) {
			tmp.pVector[i] = pVector[i] + mt.pVector[i];
		}
		return tmp;
	}
	else {
		throw "error";
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (Size == mt.Size) {
		TMatrix<ValType>tmp(Size);
		for (int i = 0; i < Size; i++) {
			tmp.pVector[i] = pVector[i] - mt.pVector[i];
		}
		return tmp;
	}
	else {
		throw "error";
	}
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
