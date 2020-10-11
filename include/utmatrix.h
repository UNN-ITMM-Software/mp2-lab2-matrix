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
  TVector(int s = 10, int si = 0);          // одновременно конструктор по умолчанию
                                            // и конструктор с параметрами
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  ValType* GetVector()const
  {
	  return pVector;
  }
  int GetSize() const{ return Size;       } // размер вектора
  int GetStartIndex()const{ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);       
  const ValType& operator[](int pos)const;// доступ
  bool operator==(const TVector &v)const;  // сравнение
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
	if ((s < 0)||(s>MAX_VECTOR_SIZE)||(si<0)) throw logic_error("negative size");
	pVector = new ValType[s];
	for (int i = si; i < s; i++)
	{
		pVector[i] = 0;
	}
	Size = s;
	StartIndex = si;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	pVector = new ValType[v.Size];
	for (int i = v.StartIndex; i < v.Size; i++)
	{
		pVector[i] = v.pVector[i];
	}
	Size = v.Size;
	StartIndex = v.StartIndex;
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[]pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos < 0)||(pos>(*this).GetStartIndex()+(*this).GetSize())) throw logic_error("negative index");
    return pVector[pos];
} /*-------------------------------------------------------------------------*/
template <class ValType> // доступ
const ValType& TVector<ValType>::operator[](int pos)const 
{
	if ((pos < 0) || (pos > (*this).GetStartIndex() + (*this).GetSize())) throw logic_error("negative index");
	return pVector[pos];
} /*-----------------

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (((*this).GetSize()==v.GetSize()) && ((*this).GetStartIndex()==v.GetStartIndex()))
	{
		for (int i = v.GetStartIndex(); i < v.GetSize(); i++)
		{
			if ((*this).GetVector()[i] != v.GetVector()[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}


template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return!(v==(*this));
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this==&v)
	{
		return (*this);
	}
	delete[](*this).pVector;
	pVector = new ValType[v.GetSize()];
	for (int i = v.GetStartIndex(); i < v.GetSize(); i++)
	{
		pVector[i] = v.GetVector()[i];
	}

	Size = v.GetSize();
	StartIndex = v.GetStartIndex();
	return (*this);
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{	
	TVector<ValType> res((*this));
	for (int i = res.GetStartIndex(); i < res.GetSize(); i++)
	{
		res[i] += val;
	}
    return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> res((*this));
	for (int i = res.GetStartIndex(); i < res.GetSize(); i++)
	{
		res[i] -= val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> res((*this));
	for (int i = res.GetStartIndex(); i < res.GetSize(); i++)
	{
		res[i] *= val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if ((*this).GetSize() != v.GetSize()) throw logic_error("not equal size");
	TVector<ValType> res((*this));
	for (int i = res.GetStartIndex(); i < res.GetSize(); i++)
	{
		res[i] += v.GetVector()[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if ((*this).GetSize() != v.GetSize()) throw logic_error("not equal size");
	TVector<ValType> res((*this));
	for (int i = res.GetStartIndex(); i < res.GetSize(); i++)
	{
		res[i] -= v.GetVector()[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if ((*this).GetSize() != v.GetSize()) throw logic_error("not equal size");
	ValType res=0;
	for (int i = v.GetStartIndex();i<v.GetSize(); i++)
	{
		res += v.GetVector()[i] * (*this).GetVector()[i];
	}
	return sqrt(res);
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
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if ((s<0) || (s > MAX_MATRIX_SIZE)) throw logic_error("incorrect parametr");
	for (int i = 0; i < s; i++)
	{
		TVector<ValType>Res(i+1);
		(*this)[i] = Res;
	}
}

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):TVector<TVector<ValType> >(mt)
{
	for (int i = 0; i < (*this).GetSize(); i++)
	{
		TVector<ValType>mt(mt[i]);
		(*this)[i] = mt;
	}
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):TVector<TVector<ValType> >(mt) 
{
	for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++)
	{
		TVector<ValType>ms(mt[i]);
		(*this)[i] = ms;
	}
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (((*this).GetStartIndex() == mt.GetStartIndex()) && ((*this).GetSize() == mt.GetSize()))
	{
		for (int i = mt.GetStartIndex(); i < mt.GetSize(); i++)
		{
			if ((*this).GetVector()[i] != mt.GetVector()[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !((*this) == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (&mt == this)
	{
		return (*this);
	}
	
	delete[]pVector;
	pVector = new TVector<ValType>[mt.GetSize()];

	(*this).Size = mt.GetSize();
	(*this).StartIndex = mt.GetStartIndex();
	for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++)
	{
		(*this)[i] = mt.GetVector()[i];
	}
	return (*this);

} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (mt.GetSize() != (*this).GetSize()) throw logic_error("incorrect size");
	TMatrix<ValType>Res(*this);
	for (int i = Res.GetStartIndex(); i < Res.GetSize(); i++)
	{
		Res[i] = (*this).GetVector()[i] + mt.GetVector()[i];
	}
	return Res;
	
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (mt.GetSize() != (*this).GetSize()) throw logic_error("incorrect size");
	TMatrix<ValType>Res(*this);
	for (int i = Res.GetStartIndex(); i < Res.GetSize(); i++)
	{
		Res[i] = (*this)[i] - mt.GetVector()[i];
	}
	return Res;
} /*--------------------------------------------------s-----------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
