// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП 
// 
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001 
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015) 
// 
// Верхнетреугольная матрица - реализация на основе шаблона вектора 

#ifndef __TMATRIX_H__ 
#define __TMATRIX_H__ 

#include <iostream> 

using namespace std;

const int MAX_VECTOR_SIZE = 1000;
const int MAX_MATRIX_SIZE = 100;

// Шаблон вектора 
template <class ValType>
class TVector
{
protected:
	ValType *pVector;
	int Size; // размер вектора 
	int StartIndex; // индекс первого элемента вектора 
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector &v); // конструктор копирования 
	~TVector();
	int GetSize() { return Size; } // размер вектора 
	int GetStartIndex() { return StartIndex; } // индекс первого элемента 
	ValType& operator[](int pos); // доступ 
	bool operator==(const TVector &v) const; // сравнение 
	bool operator!=(const TVector &v) const; // сравнение 
	TVector& operator=(const TVector &v); // присваивание 

										  // скалярные операции 
	TVector operator+(const ValType &val); // прибавить скаляр 
	TVector operator-(const ValType &val); // вычесть скаляр 
	TVector operator*(const ValType &val); // умножить на скаляр 

										   // векторные операции 
	TVector operator+(const TVector &v); // сложение 
	TVector operator-(const TVector &v); // вычитание 
	ValType operator*(const TVector &v); // скалярное произведение

										 // ввод-вывод 
	friend istream& operator >> (istream &in, TVector &v)
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
	if ((s >= 0) && (s < MAX_VECTOR_SIZE) && (si >= 0)) //&& (si <= s))
		{
			pVector = new ValType[s];
			Size = s;
			StartIndex = si;
		}
	
	else throw "Неверно заданы параметры";
	
}

template <class ValType> //конструктор копирования 
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	pVector = new ValType[v.Size];
	Size = v.Size;
	StartIndex = v.StartIndex;
	for (int i=0; i<Size; i++) 
		pVector[i] = v.pVector[i];
}

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
}

template <class ValType> // доступ 
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos>=StartIndex)||(pos<(Size-1))||(pos>=0))
	{
		return pVector[pos - StartIndex];
	}
	else throw "Неверно задан индекс";
}

template <class ValType> // сравнение 
bool TVector<ValType>::operator==(const TVector &v) const
{
	bool result = true;
	if (this == &v) return result;
	if ((StartIndex != v.StartIndex) || (Size != v.Size)) result = false;
	else for (int i = 0; i < Size; i++)
	{
		if (pVector[i] != v.pVector[i])
		{
			result = false;
			break;
		}
	}
	return result;
}

template <class ValType> // сравнение 
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !(this == &v);
}

template <class ValType> // присваивание 
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this != &v)
	{
		if (Size != v.Size)
		{
			delete[] pVector;
			pVector = new ValType[v.Size];
		}
		Size = v.Size;
		StartIndex = v.StartIndex;
		for (int i = 0;i<Size;i++)
			pVector[i] = v.pVector[i];
	}
	return *this;
}

template <class ValType> // прибавить скаляр 
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector temp(Size, StartIndex);
	for (int i = 0;i<Size;i++)
	{
		temp.pVector[i] = pVector[i] + val;
	}
	return temp;
}

template <class ValType> // вычесть скаляр 
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector temp(Size, StartIndex);
	for (int i = 0;i<Size;i++)
	{
		temp.pVector[i] = pVector[i] - val;
	}
	return temp;
}

template
<class ValType> // умножить на скаляр 
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector temp(Size, StartIndex);
	for (int i = 0;i<Size;i++)
	{
		temp.pVector[i] = pVector[i] * val;
	}
	return temp;
}

template <class ValType> // сложение 
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	TVector temp(Size, StartIndex);
	if ((StartIndex != v.StartIndex) || (Size != v.Size)) throw "Разные размеры";
		else
	{
		for (int i = 0; i < Size; i++)
		{
			temp.pVector[i] = pVector[i] + v.pVector[i];
		}
		return temp;
	}
}

template <class ValType> // вычитание 
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	TVector temp(Size, StartIndex);
	if ((StartIndex != v.StartIndex) || (Size != v.Size)) throw "Разные размеры";
	else
	{
		for (int i = 0; i < Size; i++)
		{
			temp.pVector[i] = pVector[i] - v.pVector[i];
		}
		return temp;
	}
}

template <class ValType> // скалярное произведение 
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	int temp;
	if ((StartIndex != v.StartIndex) || (Size != v.Size)) throw "Разные размеры";
	else
	{
		for (int i = 0; i < Size; i++)
		{
			temp += pVector[i] * v.pVector[i];
		}
		return temp;
	}
}


// Верхнетреугольная матрица 
template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix &mt); // копирование 
	TMatrix(const TVector<TVector<ValType>> &mt); // преобразование типа 
	bool operator==(const TMatrix &mt) const; // сравнение 
	bool operator!=(const TMatrix &mt) const; // сравнение 
	TMatrix& operator= (const TMatrix &mt); // присваивание 
	TMatrix operator+ (const TMatrix &mt); // сложение 
	TMatrix operator- (const TMatrix &mt); // вычитание 
	TMatrix operator* ( TMatrix &mt);     // умножение 
	TMatrix operator/ ( TMatrix &mt);     // деление
	// ввод / вывод 
	friend istream& operator >> (istream &in, TMatrix &mt)
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
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s)
{
	if ((s>0)&&(s<MAX_MATRIX_SIZE))
	{
	for (int i = 0; i < s ; i++)
		pVector[i] = TVector<ValType>(s-i, i);
	}
	else throw "Неверно задан размер матрицы";
}

template <class ValType> // конструктор копирования 
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) :
	TVector<TVector<ValType>>(mt) {}

template <class ValType> // конструктор преобразования типа 
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>> &mt) :
	TVector<TVector<ValType>>(mt) {}

template <class ValType> // сравнение 
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	bool result = true;
	if (this == &mt) return result;

	if (Size != mt.Size) result = false;
	else for (int i = 0; i < Size; i++) {
		if (mt.pVector[i] != pVector[i])
			result = false;
	}

	return result;
}

template <class ValType> // сравнение 
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(this == &mt);
}

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
		for (int i = 0; i < Size; i++)
			pVector[i] = mt.pVector[i];
	}
	return *this;
}

template <class ValType> // сложение 
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType>>::operator+(mt);
}

template <class ValType> // вычитание 
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType>>::operator-(mt);
}

template <class ValType> // умножение
 TMatrix<ValType> TMatrix<ValType>::operator*(TMatrix<ValType> &mt)
 {

		TMatrix<ValType> tmp( mt.Size );
	

		for (int l = 0; l<Size; l++ )
				{


		for (int i = 0; i < Size-l; i++ )
		{
			 for (int j = i; j < Size-l; j++ )
			 {
				tmp[i][j] = 0;
				int count = i > j ? i : j;
				
 				for( int k = count; k < Size - l; k++ )
 				{
 					tmp[i][j] = tmp[i][j]  + ((*this)[i])[k] *  mt[k][j];
 				}
				
			 }
		}

		}
	

 	return tmp;
 }



 template <class ValType> // деление
 TMatrix<ValType> TMatrix<ValType>::operator/(TMatrix<ValType> &mt)
 {


	 
	 TMatrix<ValType> tmp( mt.Size );
	 	for (int i = 0; i < Size; i++ )
		{
			 for (int j = i; j < Size; j++ )
			 {
				 tmp[i][j] = ((*this)[i])[j];
			 }
		}



	 TMatrix<ValType> tmp2( mt.Size );
	  	for (int i = 0; i < Size; i++ )
		{
			 for (int j = i; j < Size; j++ )
			 {
				 tmp2[i][j] = 0;
			 }
		}

	 for (int i = 0; i < Size; i++ )
		{
				 tmp2[i][i] = 1;
		}

//diag
 for (int k = 0; k<Size ; k++)
 {

	 for (int j = 1; j<Size-k ; j++)
	 {
	 double a=tmp[k+j][k+j]/tmp[k][k+j];
	 for (int i = j; i<Size-k ; i++)
		{
			//tmp[k][i]=a;
			tmp[k][i+k]=tmp[k][i+k]-tmp[k+j][i+k]/a;
			tmp2[k][i+k]=tmp2[k][i+k]-tmp2[k+j][i+k]/a;
		}
	 }

 }
 //norm
  	for (int i = 0; i < Size; i++ )
		{
			 for (int j = i; j < Size; j++ )
			 {
				 tmp2[i][j] = tmp2[i][j]/tmp[i][i];
			 }
		}

	//return tmp*tmp2; //=E

	 return tmp2*mt;
 }

#endif