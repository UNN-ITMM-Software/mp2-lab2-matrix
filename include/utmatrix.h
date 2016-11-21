﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
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
  int GetSize() const      { return Size;       } // размер вектора
  int GetStartIndex()const{ return StartIndex; } // индекс первого элемента
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
	if (s < 0) throw 'Neg';
	if (s > MAX_VECTOR_SIZE) throw 'Big';
	if (si < 0) throw 'Neg';
	pVector = new ValType[s];
	Size = s;
	StartIndex = si;
	for (int i = StartIndex; i < Size + StartIndex; i++)
		(*this)[i] = 0; //pVector[i]=0;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	pVector = new ValType[v.Size];
	Size = v.Size;
	StartIndex = v.StartIndex;
	for (int i = StartIndex; i < Size+StartIndex; i++)
		pVector[i] = v.pVector[i];

} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ координате вектора с конролем индекса
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos<0) {
		throw 'Neg';
	}
	if (pos >= StartIndex + Size) {
		throw 'Big';
	}
	if (pos<StartIndex) {
		//return *new ValType();
		throw 'Err';
	}
	return (pVector[pos]);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.Size) return false; //GetSize[i]
	if (StartIndex != v.StartIndex) return false;
	for (int i = 0; i < Size; i++)
	{
		if (pVector[i] != v.pVector[i]) return false;  //(*this[i]) != v[i]
	}
	return true;
		
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	/*if ((Size == v.GetSize()) && (StartIndex == v.GetStartUndex()))
	{
		for (int i = StartIndex; i < Size + StartIndex; i++)

			if ((*this[i]) != v[i])	return false;
			else return true;
	}
	else return false;*/
	return !(*this == v); //сравнение по всем полям size si коодинаты вектора
	//return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this != &v)
	{
		if (Size != v.Size) //GetSize
		{
			Size = v.Size;
			delete[] pVector;
			pVector = new ValType[v.Size];
		}
		StartIndex = v.StartIndex;
		for (int i = 0; i < Size; i++)
			//((*this)[i]) = v[i]; 
			pVector[i] = v.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType>tmp(Size, StartIndex); //без этого было
	for (int i = 0; i < Size; i++)
		tmp.pVector[i] = pVector[i] + val; //(*this)[i]=(*this)[i]+val
	return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType>tmp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		tmp.pVector[i] = pVector[i] - val;
	return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType>tmp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		tmp.pVector[i] = pVector[i]*val;
	return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	//if (GetSize() == v.GetSize() && GetStartIndex() == v.GetStartIndex())
	//{

	//	TVector<ValType> RESULT(Size, StartIndex);

	//	for (int i = StartIndex; i < Size + StartIndex; i++) {
	//		RESULT.pVector[i] = (*this)[i]+v[i];
	//	}
	//	return RESULT;
	//}
	//throw 'DifL';

	if ((v.GetSize() != GetSize())||(GetStartIndex() != v.GetStartIndex())) throw 'DifL';
	TVector<ValType> RESULT(GetSize(), GetStartIndex());

	for (int i = 0; i < Size; i++) {
		RESULT.pVector[i] = pVector[i] + v.pVector[i];
	}
	return RESULT;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (GetSize() == v.GetSize() && GetStartIndex() == v.GetStartIndex())
	{
		TVector<ValType> RESULT(Size, StartIndex);

		for (int i = 0; i < Size ; i++) {
			RESULT.pVector[i] = pVector[i] - v.pVector[i]; //(*this)[i]-v[i]
		}
		return RESULT;
	}
	throw 'DifL'
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	//ValType RESULT = 0;
	if (GetSize() == v.GetSize() && GetStartIndex() == v.GetStartIndex())
	{
	ValType RESULT = 0;
	for (int i = 0; i < Size ; i++)
		RESULT = RESULT + pVector[i] * v.pVector[i];
	return RESULT;
	}
	throw 'DifL';
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

template <class ValType> //конструктор инициализатор
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	//try {
		if (s < 0) throw 'Neg';
		if (s > MAX_MATRIX_SIZE) throw 'Big';
		for (int i = 0; i < s; i++)
			pVector[i] = TVector<ValType>(s - i, i);  //втф
		//for (int i = 0; i < s; i++)
			//for (int j = (*this)[i].GetStartIndex(); j < (*this)[i].GetStartIndex() + (*this)[i].GetSize(); j++)  //(int j = pVector[i].GetStartIndex(); j < pVector[i].GetStartIndex() + p.Vector[i].GetSize(); j++)
				//pVector[i][j] = 0; 
	//}
	//catch (...)
	//{
		//cout << "Something went wrong in matrix constructor!!!" << endl;
	//}

} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа к TVector
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this == &mt) return true;  //а нужно ли это?
	if (Size != mt.Size) return false;

	for (int i = 0; i < Size; i++) 
		if (pVector[i] != mt.pVector[i])
			return false;
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this==m);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this != &mt)
	{
		if (Size != mt.Size)
		{
			delete[] pVector;
			pVector = new TVector<ValType>[mt.Size];
		}
		Size = mt.Size; 
		StartIndex = mt.StartIndex;
		for (int i = StartIndex; i < Size + StartIndex; i++)
			//((*this)[i]) = mt[i];
			pVector[i] = mt.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (Size!= mt.Size) 
		throw 'DifM';
	TMatrix<ValType> RESULT(Size);
	for (int i = 0; i < Size; i++)
	{
		RESULT[i] = pVector[i] + mt.pVector[i];
		//RESULT[i] = (*this)[i] + mt[i];
	}
	return RESULT;
	//return TVector<TVector<ValType> >::operator+(mt); //спросить как оно работает
} /*-------------------------------------------------------------------------*/


template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (GetSize() != mt.GetSize()) 
		throw 'DifM';
	TMatrix<ValType> result(Size);
	for (int i = 0; i < Size; i++)
		result[i] = (*this)[i] - mt[i];
	return result;
	//return TVector<TVector<ValType> >::operator-(mt); спросить как оно работает
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
