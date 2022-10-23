
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
	ValType * pVector;
	int Size;       // размер вектора
	int StartIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector &v);                // конструктор копирования
	~TVector();
	int GetSize() { return Size; } // размер вектора
	int GetStartIndex() { return StartIndex; } // индекс первого элемента
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
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si)
{
	if (Size > MAX_VECTOR_SIZE || Size < 0 || StartIndex < 0 || StartIndex >= MAX_VECTOR_SIZE)
		throw "size or startIndex out of range";
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	copy(v.pVector, v.pVector + Size, pVector);
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos < 0) || (pos >= StartIndex + Size)) {
		throw "Going beyond the bounds of the array";
	}
	ValType null = 0;
	if (pos < StartIndex) {
		return null;
	}
	else
	{
		return pVector[pos - StartIndex];
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if ((this->Size == v.Size) && (this->StartIndex == v.StartIndex))
	{
		for (int i = 0; i < Size; i++)
		{
			if (this->pVector[i] != v.pVector[i])
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	if (*this == v)
		return 0;
	return 1;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (&v == this)
		return *this;
	delete[] pVector;
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	copy(v.pVector, v.pVector + Size, pVector);
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++) {
		res.pVector[i] += val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++) {
		res.pVector[i] = res.pVector[i] + ((-1)*val);
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++) {
		res.pVector[i] *= val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if ((this->Size + this->StartIndex) != (v.Size + v.StartIndex))
		throw "It is impossible to add vectors of different lengths";

	TVector<ValType> result(std::max(this->Size, v.Size), std::min(this->StartIndex, v.StartIndex));

	if (this->Size < result.Size)
	{
		unsigned int diff = v.StartIndex - this->StartIndex;

		for (int i = 0; i < diff; i++)
		{
			result.pVector[i] = v.pVector[i];
		}

		for (int i = 0; i < Size; i++)
		{
			result.pVector[i + diff] = v.pVector[i + diff] + pVector[i];
		}
	}
	else
	{
		unsigned int diff = this->StartIndex - v.StartIndex;

		for (int i = 0; i < diff; i++)
		{
			result.pVector[i] = pVector[i];
		}

		for (int i = 0; i < Size; i++)
		{
			result.pVector[i + diff] = pVector[i + diff] + v.pVector[i];
		}
	}
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if ((this->Size + this->StartIndex) != (v.Size + v.StartIndex))
		throw "It is impossible to subtract vectors of different lengths";

	TVector<ValType> result(std::max(this->Size, v.Size), std::min(this->StartIndex, v.StartIndex));

	if (this->Size < result.Size)
	{
		unsigned int diff = v.StartIndex - this->StartIndex;

		for (int i = 0; i < diff; i++)
		{
			result.pVector[i] = v.pVector[i] * (-1);
		}

		for (int i = 0; i < Size; i++)
		{
			result.pVector[i + diff] = pVector[i] - v.pVector[i + diff];
		}
	}
	else
	{
		unsigned int diff = this->StartIndex - v.StartIndex;

		for (int i = 0; i < diff; i++)
		{
			result.pVector[i] = pVector[i];
		}

		for (int i = 0; i < Size; i++)
		{
			result.pVector[i + diff] = pVector[i + diff] - v.pVector[i];
		}
	}
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
	if ((this->Size + this->StartIndex) != (v.Size + v.StartIndex))
		throw "It is impossible to multiply vectors of different lengths";

	ValType result;

	if (this->Size < result.Size)
	{
		unsigned int diff = v.StartIndex - this->StartIndex;

		for (int i = 0; i < Size; i++)
		{
			result = result + (pVector[i] * v.pVector[i + diff]);
		}
	}
	else
	{
		unsigned int diff = this->StartIndex - v.StartIndex;

		for (int i = 0; i < Size; i++)
		{
			result = result + (pVector[i + diff] * v.pVector[i]);
		}
	}
	return result;
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
	friend ostream & operator<<(ostream &out, const TMatrix &mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE)
		throw "Out of bounds when creating a vector";
	for (int i = 0; i < s; i++) {
		TVector<ValType> aux(s - i, i);
		pVector[i] = aux;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) :
	TVector<TVector<ValType> >(mt) {

}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	return TVector< TVector<ValType> >::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
	return (!(TVector<TVector<ValType> >:: operator==(mt)));
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
	return(TMatrix<ValType>(TVector<TVector<ValType>>:: operator=(mt)));
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
	return(TVector<TVector<ValType>>:: operator+(mt));
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	return(TVector<TVector<ValType>>:: operator-(mt));
} /*-------------------------------------------------------------------------*/

  // TVector О3 Л2 П4 С6
  // TMatrix О2 Л2 П3 С3
#endif
