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
  //virtual ~TVector();
  virtual ~TVector();
  int GetSize() const { return Size;       } // размер вектора
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
	Size = s;
	StartIndex = si;
	pVector = new ValType[s];
	for (int i = 0; i < Size; i++)
		//(*this)[i] = 0; 
		pVector[i]=0;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
    pVector = new ValType[v.Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];

} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	//cout << "vect" << endl;
	delete[] pVector;

} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ координате вектора с конролем индекса
ValType& TVector<ValType>::operator[](int pos)
{
	//if (pos<0) {
	//	throw 'Neg';
	//}
	//if (pos >= StartIndex + Size) {
	//	throw 'Big';
	//}
	//if (pos<StartIndex) {
	//	//return *new ValType();
	//	throw 'Err';
	//}
	//return (pVector[pos]);
	if ((pos >= StartIndex) && (pos < Size + StartIndex))
	{
		return pVector[pos - StartIndex];
	}
	else
		throw 'Er[]';
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
//
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
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this != &v)
	{
		StartIndex = v.StartIndex;
		if (Size != v.Size) //GetSize
		{
			Size = v.Size;
			delete[] pVector;
			pVector = new ValType[v.Size];
		}
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
	throw 'DifL';
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
  ~TMatrix(); //{ cout << "matr" << endl; }
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
		if (s < 0) throw 'Neg';
		if (s > MAX_MATRIX_SIZE) throw 'Big';
		for (int i = 0; i < s; i++)
			pVector[i] = *(new TVector<ValType>(s - i, i));  //delete????

} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа к TVector
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
	TVector<TVector<ValType> >(mt) {}



template <class Valtype>
TMatrix<Valtype>::~TMatrix()
{
	for (int i = 0; i < Size; i++)
		delete pVector[i];
	delete[]pVector;
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this == &mt) return true;
	if (Size != mt.Size) return false;

	for (int i = 0; i < Size; i++) 
		if (pVector[i] != mt.pVector[i])
			return false;
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this==mt);
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
		result[i] = pVector[i] - mt.pVector[i];
	return result;
	//return TVector<TVector<ValType> >::operator-(mt); спросить как оно работает
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif









//// ÍÍÃÓ, ÂÌÊ, Êóðñ "Ìåòîäû ïðîãðàììèðîâàíèÿ-2", Ñ++, ÎÎÏ
////
//// utmatrix.h - Copyright (c) Ãåðãåëü Â.Ï. 07.05.2001
////   Ïåðåðàáîòàíî äëÿ Microsoft Visual Studio 2008 Ñûñîåâûì À.Â. (21.04.2015)
////
//// Âåðõíåòðåóãîëüíàÿ ìàòðèöà - ðåàëèçàöèÿ íà îñíîâå øàáëîíà âåêòîðà
//
//#ifndef __TMATRIX_H__
//#define __TMATRIX_H__
//
//#include <iostream>
//
//using namespace std;
//
//const int MAX_VECTOR_SIZE = 100000000;
//const int MAX_MATRIX_SIZE = 10000;
//
//// Øàáëîí âåêòîðà
//template <class ValType>
//class TVector {
//protected:
//	ValType *pVector;
//	int Size;     // ðàçìåð âåêòîðà
//	int StartIndex; // èíäåêñ ïåðâîãî ýëåìåíòà âåêòîðà
//public:
//	TVector(int s = 10, int si = 0);
//	TVector(const TVector &v);        // êîíñòðóêòîð êîïèðîâàíèÿ
//	~TVector();
//	int GetSize() { return Size; } // ðàçìåð âåêòîðà
//	int GetStartIndex() { return StartIndex; } // èíäåêñ ïåðâîãî ýëåìåíòà
//	ValType& operator[](int pos);       // äîñòóï
//	bool operator==(const TVector &v) const;  // ñðàâíåíèå
//	bool operator!=(const TVector &v) const;  // ñðàâíåíèå
//	TVector& operator=(const TVector &v);   // ïðèñâàèâàíèå
//
//											// ñêàëÿðíûå îïåðàöèè
//	TVector  operator+(const ValType &val);   // ïðèáàâèòü ñêàëÿð
//	TVector  operator-(const ValType &val);   // âû÷åñòü ñêàëÿð
//	TVector  operator*(const ValType &val);   // óìíîæèòü íà ñêàëÿð
//
//											  // âåêòîðíûå îïåðàöèè
//	TVector  operator+(const TVector &v);   // ñëîæåíèå
//	TVector  operator-(const TVector &v);   // âû÷èòàíèå
//	ValType  operator*(const TVector &v);   // ñêàëÿðíîå ïðîèçâåäåíèå
//
//											// ââîä-âûâîä
//	friend istream& operator >> (istream &in, TVector &v) {
//		for (int i = 0; i < v.Size; i++)
//			in >> v.pVector[i];
//		return in;
//	}
//	friend ostream& operator<<(ostream &out, const TVector &v) {
//		for (int i = 0; i < v.Size; i++)
//			out << v.pVector[i] << ' ';
//		return out;
//	}
//};
//
//template <class ValType>
//TVector<ValType>::TVector(int s, int si) {
//	if (s < 0) throw 'Neg';
//	if (s > MAX_VECTOR_SIZE) throw 'Big';
//	if (si < 0) throw 'Neg';
//	Size = s;
//	StartIndex = si;
//	pVector = new ValType[s];
//	for (int i = 0; i < Size; i++)
//		pVector[i] = 0; //(*this)[i] = 0;
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> //êîíñòðóêòîð êîïèðîâàíèÿ
//TVector<ValType>::TVector(const TVector<ValType> &v) {
//	Size = v.Size;
//	StartIndex = v.StartIndex;
//	pVector = new ValType[Size];
//	for (int i = 0; i < Size; i++)
//		pVector[i] = v.pVector[i];
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType>
//TVector<ValType>::~TVector() {
//	delete[] pVector;
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // äîñòóï
//ValType& TVector<ValType>::operator[](int pos) {
//	/*if (pos<0) {
//	throw 'Neg';
//	}
//	if (pos >= StartIndex + Size) {
//	throw 'Big';
//	}
//	if (pos<StartIndex) {
//	throw 'Err';
//	}
//	return (pVector[pos]);*/
//
//	if ((pos >= StartIndex) && (pos < Size + StartIndex)) {
//		return pVector[pos - StartIndex];
//	}
//	else
//		throw "Error in []";
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // ñðàâíåíèå
//bool TVector<ValType>::operator==(const TVector &v) const {
//	if (Size != v.Size) return false; //GetSize[i]
//	if (StartIndex != v.StartIndex) return false;
//	for (int i = 0; i < Size; i++) {
//		if (pVector[i] != v.pVector[i])
//			return false;  //(*this[i]) != v[i]
//	}
//	return true;
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // ñðàâíåíèå
//bool TVector<ValType>::operator!=(const TVector &v) const {
//	return !(*this == v); //ñðàâíåíèå ïî âñåì ïîëÿì size si êîîäèíàòû âåêòîðà
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // ïðèñâàèâàíèå
//TVector<ValType>& TVector<ValType>::operator=(const TVector &v) {
//	if (this != &v) {
//		StartIndex = v.StartIndex;
//		if (Size != v.Size) //GetSize
//		{
//			Size = v.Size;
//			delete[] pVector;
//			pVector = new ValType[Size];
//		}
//
//		for (int i = 0; i < Size; i++)
//			pVector[i] = v.pVector[i];
//	}
//	return *this;
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // ïðèáàâèòü ñêàëÿð
//TVector<ValType> TVector<ValType>::operator+(const ValType &val) {
//	TVector<ValType> tmp(Size, StartIndex); //áåç ýòîãî áûëî
//	for (int i = 0; i < Size; i++)
//		tmp.pVector[i] = pVector[i] + val;
//	return tmp;
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // âû÷åñòü ñêàëÿð
//TVector<ValType> TVector<ValType>::operator-(const ValType &val) {
//	TVector<ValType> tmp(Size, StartIndex);
//	for (int i = 0; i < Size; i++)
//		tmp.pVector[i] = pVector[i] - val;
//	return tmp;
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // óìíîæèòü íà ñêàëÿð
//TVector<ValType> TVector<ValType>::operator*(const ValType &val) {
//	TVector<ValType> tmp(Size, StartIndex);
//	for (int i = 0; i < Size; i++)
//		tmp.pVector[i] = pVector[i] * val;
//	return tmp;
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // ñëîæåíèå
//TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v) {
//	if (Size != v.Size || StartIndex != v.StartIndex)
//		throw 'DifL';
//	TVector<ValType> result(Size, StartIndex);
//	for (int i = 0; i < Size; i++) {
//		result.pVector[i] = pVector[i] + v.pVector[i];
//	}
//	return result;
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // âû÷èòàíèå
//TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v) {
//
//	if (Size == v.Size && StartIndex == v.StartIndex) {
//		TVector<ValType> result(Size, StartIndex);
//		for (int i = 0; i < Size; i++) {
//			result.pVector[i] = pVector[i] - v.pVector[i]; //(*this)[i]-v[i]
//		}
//		return result;
//	}
//	throw 'DifL';
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // ñêàëÿðíîå ïðîèçâåäåíèå
//ValType TVector<ValType>::operator*(const TVector<ValType> &v) {
//	if (Size == v.Size) {
//		ValType result = 0;
//		for (int i = 0; i < Size; i++)
//			result = result + pVector[i] * v.pVector[i];
//		return result;
//	}
//	throw 'DifL';
//} /*-------------------------------------------------------------------------*/
//
//
//  // Âåðõíåòðåóãîëüíàÿ ìàòðèöà
//template <class ValType>
//class TMatrix : public TVector<TVector<ValType> > {
//public:
//	TMatrix(int s = 10);
//	TMatrix(const TMatrix &mt);          // êîïèðîâàíèå
//	TMatrix(const TVector<TVector<ValType> > &mt); // ïðåîáðàçîâàíèå òèïà
//	bool operator==(const TMatrix &mt) const;    // ñðàâíåíèå
//	bool operator!=(const TMatrix &mt) const;    // ñðàâíåíèå
//	TMatrix& operator= (const TMatrix &mt);    // ïðèñâàèâàíèå
//	TMatrix  operator+ (const TMatrix &mt);    // ñëîæåíèå
//	TMatrix  operator- (const TMatrix &mt);    // âû÷èòàíèå
//
//											   // ââîä / âûâîä
//	friend istream& operator >> (istream &in, TMatrix &mt) {
//		for (int i = 0; i < mt.Size; i++)
//			in >> mt.pVector[i];
//		return in;
//	}
//	friend ostream & operator<<(ostream &out, const TMatrix &mt) {
//		for (int i = 0; i < mt.Size; i++)
//			out << mt.pVector[i] << endl;
//		return out;
//	}
//};
//
//template <class ValType>
//TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s) {
//	if (s < 0) throw 'Neg';
//	if (s > MAX_MATRIX_SIZE) throw 'Big';
//	for (int i = 0; i < s; i++)
//		pVector[i] = *(new TVector<ValType>(s - i, i)); //âòô
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // êîíñòðóêòîð êîïèðîâàíèÿ
//TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) :
//	TVector<TVector<ValType> >(mt) {}
//
//template <class ValType> // êîíñòðóêòîð ïðåîáðàçîâàíèÿ òèïà
//TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) :
//	TVector<TVector<ValType> >(mt) {}
//
//template <class ValType> // ñðàâíåíèå
//bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const {
//	if (this == &mt) return true;  //à íóæíî ëè ýòî?
//	if (Size != mt.Size) return false;
//
//	for (int i = 0; i < Size; i++)
//		if (pVector[i] != mt.pVector[i])
//			return false;
//	return true;
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // ñðàâíåíèå
//bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const {
//	return !(*this == mt);
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // ïðèñâàèâàíèå
//TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt) {
//	if (this != &mt) {
//		if (Size != mt.Size) {
//			delete[] pVector;
//			pVector = new TVector<ValType>[mt.Size];
//		}
//		Size = mt.Size;
//		StartIndex = mt.StartIndex;
//		for (int i = StartIndex; i < Size + StartIndex; i++)
//			//((*this)[i]) = mt[i];
//			pVector[i] = mt.pVector[i];
//	}
//	return *this;
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // ñëîæåíèå
//TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt) {
//	if (Size != mt.Size)
//		throw 'DifM';
//	TMatrix<ValType> result(Size);
//	for (int i = 0; i < Size; i++) {
//		result[i] = pVector[i] + mt.pVector[i];
//	}
//	return result;
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // âû÷èòàíèå
//TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt) {
//	if (Size != mt.Size)
//		throw 'DifM';
//	TMatrix<ValType> result(Size);
//	for (int i = 0; i < Size; i++)
//		result[i] = pVector[i] - mt.pVector[i];
//	return result;
//} /*-------------------------------------------------------------------------*/
//
//  // TVector Î3 Ë2 Ï4 Ñ6
//  // TMatrix Î2 Ë2 Ï3 Ñ3
//#endif