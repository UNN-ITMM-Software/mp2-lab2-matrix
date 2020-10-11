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
	ValType* pVector;
	int Size;       // размер вектора
	int StartIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector& v);                // конструктор копирования
	~TVector();
	int GetSize() { return Size; } // размер вектора
	int GetStartIndex() { return StartIndex; } // индекс первого элемента
	ValType& operator[](int pos);             // доступ
	bool operator==(const TVector& v) const;  // сравнение
	bool operator!=(const TVector& v) const;  // сравнение
	TVector& operator=(const TVector& v);     // присваивание

	// скалярные операции
	TVector<ValType>  operator+(const ValType& val);   // прибавить скаляр
	TVector<ValType>  operator-(const ValType& val);   // вычесть скаляр
	TVector<ValType>  operator*(const ValType& val);   // умножить на скаляр

	// векторные операции
	TVector<ValType>  operator+(const TVector<ValType>& v);     // сложение
	TVector<ValType>  operator-(const TVector<ValType>& v);     // вычитание
	ValType  operator*(const TVector<ValType>& v);     // скалярное произведение

	// ввод-вывод
	friend istream& operator>>(istream& is, TVector<ValType>& v)
	{
		for (int i = 0; i < v.Size; i++)
			is >> v.pVector[i];
		return is;
	}
	friend ostream& operator<<(ostream& os, const TVector<ValType>& v)
	{
		for (int i = 0; i < v.Size; i++)
			os << v.pVector[i] << ' ';
		return os;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	Size = s;
	StartIndex = si;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
	{
		pVector[i] = 0;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v)
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

	return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
	if (Size != v.Size)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < Size; i++)
		{
			if (pVector[i] != v.pVector[i])
			{
				return false;
			}
		}
		return true;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector& v) const
{
	if (Size != v.Size)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < Size; i++)
		{
			if (pVector[i] != v.pVector[i])
			{
				return true;
			}
		}
		return false;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
	if (this != &v)
	{
		if (Size != v.Size)
		{
			Size = v.Size;
			delete[]pVector;
			pVector = new ValType[Size];
		}
		StartIndex = v.StartIndex;
		for (int i = 0; i < Size; i++)
		{
			pVector[i] = v.pVector[i];
		}
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = val + pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = pVector[i] - val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = val * pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
	if (Size == v.Size)
	{
		TVector<ValType> res(v);
		for (int i = 0; i < Size; i++)
		{
			res.pVector[i] = pVector[i] + v.pVector[i];
		}
		return res;
	}
	else
		cout << "different size";
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
	if (Size == v.Size)
	{
		TVector<ValType> res(v);
		for (int i = 0; i < Size; i++)
		{
			res.pVector[i] = pVector[i] - v.pVector[i];
		}
		return res;
	}
	else
		cout << "different size";
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
	if (Size == v.Size)
	{
		ValType sum = 0;
		for (int i = 0; i < Size; i++)
		{
			sum += pVector[i] * v.pVector[i];
		}
		return sum;
	}
	else
		cout << "different size";
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 5);
	TMatrix(const TMatrix& mt);
	TMatrix(const TVector<TVector<ValType> >& mt);
	bool operator==(const TMatrix& mt) const;
	bool operator!=(const TMatrix& mt) const;
	TMatrix& operator= (const TMatrix& mt);
	TMatrix  operator+ (const TMatrix& mt);
	TMatrix  operator- (const TMatrix& mt);


	friend istream& operator>>(istream& in, TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
		{
			TVector<ValType> vec = mt.pVector[i];
			for (int j = 0; j < 2 * mt.pVector[i].GetStartIndex(); j++)
			{
				out << " ";
			}
			out << mt.pVector[i] << endl;
		}
		return out;
	}

};

template <class ValType>
TMatrix<ValType>::TMatrix(int s = 5) : TVector<TVector<ValType> >(s)
{
	for (int i = 0; i < Size; i++)
	{
		TVector<ValType> a(Size - i, i);
		pVector[i] = a;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
	if (Size != mt.Size)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < Size; i++)
		{
			if (pVector[i] != mt.pVector[i])
			{
				return false;
			}
		}
		return true;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
	if (Size != mt.Size)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < Size; i++)
		{
			if (pVector[i] != mt.pVector[i])
			{
				return true;
			}
		}
		return false;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
	if (this != &mt)
	{
		if (Size != mt.Size)
		{
			delete[]pVector;
			Size = mt.Size;
			pVector = new TVector<ValType>[Size];
		}
		for (int i = 0; i < Size; i++)
		{
			pVector[i] = mt.pVector[i];
		}
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
	if (Size == mt.Size)
	{
		TMatrix<ValType> res(mt);
		for (int i = 0; i < Size; i++)
		{
			res.pVector[i] = mt.pVector[i] + pVector[i];
		}
		return res;
	}
	else
	{
		cout << "Invalid array size";
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	if (Size == mt.Size)
	{
		TMatrix<ValType> res(mt);
		for (int i = 0; i < Size; i++)
		{
			res.pVector[i] = pVector[i] - mt.pVector[i];
		}
		return res;
	}
	else
	{
		cout << "Invalid array size";
	}
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
