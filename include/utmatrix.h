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
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((s + si) > MAX_VECTOR_SIZE)
	{
		throw ("Too_large_Size);
	}
	if (s <= 0)
	{
		throw ("Negative_Size");
	}
	if (si < 0)
	{
		throw ("Negative_StartIndex");
	}

	pVector = new ValType[s];
	Size = s;
	StartIndex = si;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
	{
		pVector[i] = v.pVector[i];
	}
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[]pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos >= 0 && pos - this->StartIndex <= this->Size)
	{
		if (pos >= StartIndex)
		{
			return pVector[pos - this->StartIndex];
		}
		else
		{
			throw "Wrong index";
		}
	}
	else
	{
		throw "Wrong index";
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
		int count = 0;
		if (Size == v.Size)
		{
			for (int i = 0; i < v.Size; i++)
			{
				if (pVector[i] == v.pVector[i])
				{
					count++;
				}
			}
			if (count == v.Size)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	this->Size = v.Size;
	this->pVector = new ValType[Size];
	for (int i = 0; i < v.Size; i++)
	{
		this->pVector[i] = v.pVector[i];
	}
	this->StartIndex = v.StartIndex;
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector <ValType>temp(Size + StartIndex, 0);
	for (int i = 0; i < temp.Size; i++)
		temp.pVector[i] = val;
	for (int i = StartIndex; i < temp.Size; i++)
	{
		temp.pVector[i] += pVector[i - StartIndex];
	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	return (this->operator+(-val));
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector <ValType>temp(*this);
	for (int i = 0; i < temp.Size; i++)
		temp.pVector[i] *= val;
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size + StartIndex != v.Size + v.StartIndex)
	{
		throw "Different length";
	}
	else
	{
		if (Size < v.Size)
		{
			TVector <ValType> a(v);
			for (int i = 0; i < Size; i++)
			{
				a.pVector[StartIndex - v.StartIndex + i] = a.pVector[StartIndex - v.StartIndex + i] + pVector[i];
			}
			return a;
		}
		else
		{
			TVector <ValType> a(*this);
			for (int i = 0; i < v.Size; i++)
			{
				a.pVector[v.StartIndex - StartIndex + i] = a.pVector[v.StartIndex - StartIndex + i] + v.pVector[i];
			}
			return a;
		}
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (StartIndex + Size != v.Size + v.StartIndex)
		throw "Not equal size of vectors";
	else
	{
		if (Size >= v.Size)
		{
			TVector<ValType> res(*this);
			for (int i = 0; i < v.Size; i++)
				res.pVector[i + v.StartIndex - StartIndex] = res.pVector[i + v.StartIndex - StartIndex] - v.pVector[i];
			return(res);
		}
		else
		{
			TVector<ValType> res(v);
			for (int i = 0; i < StartIndex - v.StartIndex; i++)
				res.pVector[i] = v.pVector[i] * (-1);
			for (int i = 0; i < Size; i++)
				res.pVector[i + StartIndex - v.StartIndex] = pVector[i] - v.pVector[i + StartIndex - v.StartIndex];
			return(res);
		}
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	int S = 0;
	if (Size + StartIndex == v.Size + v.StartIndex)
	{
		for (int i = 0; i < Size; i++)
			S += pVector[i] * v.pVector[i];
		return S;
	}
	else
	{
		throw "Different lengths";
	}
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
	Size = s;
	StartIndex = 0;
	if ((s <= MAX_MATRIX_SIZE) && (s > 0))
	{
		for (int i = 0; i < s; i++)
		{
			TVector<ValType> t(s - i, i);
			this->pVector[i] = t;
		}
	}
	else
	{
		throw " Wrong data";
	}
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
	return TVector<TVector<ValType>> :: operator== (mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return (!(*this == mt));
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	TVector<TVector<ValType>> :: operator= (mt);
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType>> :: operator+ (mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType>> :: operator- (mt);
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif