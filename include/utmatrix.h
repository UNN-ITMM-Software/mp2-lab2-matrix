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
  int Size;       // размер вектора, Tamanho do vector
  int StartIndex; // индекс первого элемента вектора, index do primeiro elemento do vector
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора, tamanho do vector
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента, index do primeiro elemento
  ValType& operator[](int pos);             // доступ, disponivel
  bool operator==(const TVector &v) const;  // сравнение, comparacao
  bool operator!=(const TVector &v) const;  // сравнение, comparacao
  TVector& operator=(const TVector &v);     // присваивание, 

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение, soma
  TVector  operator-(const TVector &v);     // вычитание, subtracao
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
	StartIndex=si;
	Size=s;
	pVector=new ValType[s];
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size=v.Size;
	StartIndex=v.StartIndex;
	pVector=new ValType[Size];
	for(int i=0; i<Size; i++){
	pVector[i]=v.pVector[i];
	}

} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ disponivel
ValType& TVector<ValType>::operator[](int pos)
{
	return pVector[pos-StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение, comparacao
bool TVector<ValType>::operator==(const TVector &v) const
{
	  return !(this!=v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение, comparacao
bool TVector<ValType>::operator!=(const TVector &v) const
{
	if(size!=v.Size){
		return true ;
	}
	for (int i=0; i<size; i++)
	{
	if(pVector[i]!=v.Size[i])
		return true;
	}
	 return false;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	StartIndex=v.StartIndex;
	if(Size!=v.Size){
		Size=v.Size;
	delete[]pVector;
	pVector=new ValType[Size];
	}
	for(int i=0; i<Size; i++)
	{
		pVector[i]=v.pVector[i];
	}
	return*this;
	;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector res(Size, StartIndex);
	for(int i=0; i<Size; i++)
	{
	res.pVector[i]=pVector[i]+val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector res(Size, StartIndex);
	for(int i=0; i<Size; i++)
	{
	res.pVector[i]=pVector[i]-val;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector res(Size, StartIndex);
	for(int i=0; i<Size; i++)
	{
	res.pVector[i]=pVector[i]*val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	TVector<ValType> res(Size, StartIndex);
	for(int i=0; i<Size; i++)
	{
		res.pVector[i]=pVector[i]+v.pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	Tvector res(Size, StartIndex);
	for(int i=0; i<Size; i++)
	{
		res.pVector[i]=pVector-v.pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
ValType res=0;
for(int i=0; i<Size; i++)
{
  res= res + pVector[i]*v.pVector[i];
}
return res; 
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
private:
	TVector<ValType> *pVector;

public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  TVector<ValType>& operator [](const int i);
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
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s, 0)
{
	pVector=new TVector<ValType>[s];

	for (int i = 0; i < Size; i++)
	{
		pVector[i] = TVector<ValType> (Size-i, i);
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType>>(mt)
{
	Size=mt.Size;
	StartIndex=mt.StartIndex;
	pVector=new TVector<ValType>[Size];
	for(int i=0; i<Size;i++)
	{
		pVector[i]=mt.pVector[i];
	}

}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt)
{
	Size=mt.Size;
	StartIndex=mt.StartIndex;
	pVector=mt.pVector;
	
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
 return !(*this !=mt)

} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	if(Size!=mt.Size)
	{
		return true;
	}
	
	for(int i=0;i<Size;i++)
	{
		if(pVector[i]!=mt.pVector[i])
		{
	       return true;
		}
	}
	return false;
	
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	StartIndex=mt.StartIndex;
	if(Size!=mt.Size){
		Size=mt.Size;
	delete[]pVector;
	pVector=new TVector<ValType>[Size];
	}
	for(int i=0; i < Size; i++)
	{
		pVector[i]=mt.pVector[i];
	}
	return*this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	TMatrix<ValType>  res(Size);

	for(int i=0; i<Size; i++)
	{
		res.pVector[i]=pVector[i]+mt.pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	TMatrix<ValType>  res(Size);

	for(int i=0; i<Size; i++)
	{
		res.pVector[i]=pVector[i]-mt.pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>& TMatrix<ValType>::operator [](const int i)
{
	return pVector[i-StartIndex];
}
// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
