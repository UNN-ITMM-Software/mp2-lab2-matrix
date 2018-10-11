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
	ValType * pVector;
	int size;       // размер вектора
	int startIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector &v);                // конструктор копирования
	~TVector();
	int GetSize() { return size; } // размер вектора
	int GetStartIndex() { return startIndex; } // индекс первого элемента
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
		for (int i = 0; i < v.size; i++)
			in >> v.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream &out, const TVector &v)
	{
		for (int i = 0; i < v.size; i++)
			out << v.pVector[i] << ' ';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) {
	if (s > MAX_VECTOR_SIZE || s < 0 || si < 0)
		throw "Creating vector error!";

	pVector = new ValType[s];
	size = s;
	startIndex = si;
	for (int i = 0; i < size; ++i)
		pVector[i] = 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v) {
	size = v.size;
	startIndex = v.startIndex;

	pVector = new ValType[this->size];

	for (int i = 0; i < v.size; ++i)
		pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector() {
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos) {
	if (pos < 0 || pos > MAX_MATRIX_SIZE)
		throw "Unexisting value";
	return pVector[pos];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const {
	if (this->size != v.size)
		return false;

	if (this == &v)
		return true;

	for (int i = 0; i < this->size; ++i)
		if (pVector[i] != v.pVector[i])
			return false;

	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const {
	return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v) {
	if (this == &v)
		return *this;

	if (this->size != v.size) {
		delete[] pVector;
		pVector = new ValType[v.size];
	}

	this->size = v.size;
	this->startIndex = v.startIndex;

	for (int i = 0; i < this->size; ++i)
		pVector[i] = v.pVector[i];

	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val) {
	TVector<ValType> temp(*this);

	for (int i = 0; i < this->size; ++i)
		temp.pVector[i] += val;

	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val) {
	TVector<ValType> temp(*this);

	for (int i = 0; i < this->size; ++i)
		temp.pVector[i] -= val;

	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val) {
	TVector<ValType> temp(*this);

	for (int i = 0; i < this->size; ++i)
		temp.pVector[i] *= val;

	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v) {
	if (this->size != v.size)
		throw "Size error!";

	TVector<ValType> temp(*this);

	for (int i = 0; i < this->size; ++i)
		temp.pVector[i] += v.pVector[i];

	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v) {
	if (this->size != v.size)
		throw "Size error!";

	TVector<ValType> temp(*this);

	for (int i = 0; i < this->size; ++i)
		temp.pVector[i] -= v.pVector[i];

	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v) {
	if (this->size != v.size)
		throw "Size error!";

	ValType temp = 0;
	for (int i = 0; i < this->size; ++i)
		temp += pVector[i] * v.pVector[i];
	return temp;
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
	TVector<ValType>& operator[](int pos);
	TMatrix& operator= (const TMatrix &mt);        // присваивание
	TMatrix  operator+ (const TMatrix &mt);        // сложение
	TMatrix  operator- (const TMatrix &mt);        // вычитание
												   // ввод / вывод
	friend istream& operator>>(istream &in, TMatrix &mt)
	{
		for (int i = 0; i < mt.size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream & operator<<(ostream &out, const TMatrix &mt)
	{
		for (int i = 0; i < mt.size; i++)
		{
			for (int j = 0; j < i; j++)// цикл для отступа
			{
				out << "  ";
			}
			out << mt.pVector[i] << endl;
		}
		return out;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s) {
	if (s > MAX_MATRIX_SIZE || s < 0)
		throw "Creating matrix error!";

	for (int i = 0; i < size; i++)
		this->pVector[i] = TVector<ValType>(s, i);
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) :
	TVector<TVector<ValType> >(mt) {
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) :
	TVector<TVector<ValType> >(mt) {
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const {
	if (this->size != mt.size)
		return false;
	if (this == &mt)
		return true;
	for (int i = 0; i < size; ++i)
		if (this->pVector[i] != mt.pVector[i])
			return false;
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const {
	return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template<class ValType>
TVector<ValType>& TMatrix<ValType>::operator[](int pos) {
	if(pos < 0 || pos > MAX_MATRIX_SIZE)
			throw "Unexisting value";
	return this->pVector[pos];
}

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt) {
	if (&mt == this)
		return *this;

	if (this->size != mt.size) {
		delete[] pVector;
		pVector = new TVector<ValType>[mt.size];
	}

	this->size = mt.size;
	this->startIndex = mt.startIndex;

	for (int i = 0; i < this->size; i++)
		this->pVector[i] = mt.pVector[i];

	return *this;
} /*-------------------------------------------------------------------------*/
  //
template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt) {
	if (this->size != mt.size)
		throw "Size error!";

	TMatrix temp(this->size);
	for (int i = 0; i < this->size; ++i)
		temp.pVector[i] = this->pVector[i] + mt.pVector[i];

	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt) {
	if (this->size != mt.size)
		throw "Size error!";

	TMatrix temp(this->size);
	for (int i = 0; i < this->size; ++i)
		temp.pVector[i] = this->pVector[i] - mt.pVector[i];

	return temp;
}

//TVector О3 Л2 П4 С6
//TMatrix О2 Л2 П3 С3
#endif
