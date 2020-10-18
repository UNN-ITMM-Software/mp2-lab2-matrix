#pragma once

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;

// Øàáëîí âåêòîðà
template <class ValType>
class TVector
{
protected:
	ValType *pVector;
	int Size;       // ðàçìåð âåêòîðà
	int StartIndex; // èíäåêñ ïåðâîãî ýëåìåíòà âåêòîðà
public:
	TVector(int s = 10, int si = 0);          // îäíîâðåìåííî êîíñòðóêòîð ïî óìîë÷àíèþ
											  // è êîíñòðóêòîð ñ ïàðàìåòðàìè
	TVector(const TVector &v);                // êîíñòðóêòîð êîïèðîâàíèÿ
	~TVector();
	ValType* GetVector()const
	{
		return pVector;
	}
	int GetSize() const { return Size; } // ðàçìåð âåêòîðà
	int GetStartIndex()const { return StartIndex; } // èíäåêñ ïåðâîãî ýëåìåíòà
	ValType& operator[](int pos);
	const ValType& operator[](int pos)const;// äîñòóï
	bool operator==(const TVector &v)const;  // ñðàâíåíèå
	bool operator!=(const TVector &v) const;  // ñðàâíåíèå
	TVector& operator=(const TVector &v);     // ïðèñâàèâàíèå

											  // ñêàëÿðíûå îïåðàöèè
	TVector  operator+(const ValType &val);   // ïðèáàâèòü ñêàëÿð
	TVector  operator-(const ValType &val);   // âû÷åñòü ñêàëÿð
	TVector  operator*(const ValType &val);   // óìíîæèòü íà ñêàëÿð

											  // âåêòîðíûå îïåðàöèè
	TVector  operator+(const TVector &v);     // ñëîæåíèå
	TVector  operator-(const TVector &v);     // âû÷èòàíèå
	ValType  operator*(const TVector &v);     // ñêàëÿðíîå ïðîèçâåäåíèå

											  // ââîä-âûâîä
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
	if ((s < 0) || (s>MAX_VECTOR_SIZE) || (si<0)) throw logic_error("negative size");
	pVector = new ValType[s];
	for (int i = si; i < s; i++)
	{
		pVector[i] = 0;
	}
	Size = s;
	StartIndex = si;
}

template <class ValType> //êîíñòðóêòîð êîïèðîâàíèÿ
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	pVector = new ValType[v.Size];
	for (int i = v.StartIndex; i < v.Size; i++)
	{
		pVector[i] = v.pVector[i];
	}
	Size = v.Size;
	StartIndex = v.StartIndex;
}
template <class ValType>
TVector<ValType>::~TVector()
{
	delete[]pVector;
}

template <class ValType> // äîñòóï
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos < 0) || (pos>(*this).GetStartIndex() + (*this).GetSize())) throw logic_error("negative index");
	return pVector[pos];
}

template <class ValType> // äîñòóï
const ValType& TVector<ValType>::operator[](int pos)const
{
	if ((pos < 0) || (pos >= (*this).GetStartIndex() + (*this).GetSize())) throw logic_error("negative index");
	return pVector[pos];
}

template <class ValType> // ñðàâíåíèå
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (((*this).GetSize() == v.GetSize()) && ((*this).GetStartIndex() == v.GetStartIndex()))
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

template <class ValType> // ñðàâíåíèå
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return!(v == (*this));
}

template <class ValType> // ïðèñâàèâàíèå
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this == &v)
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
}

template <class ValType> // ïðèáàâèòü ñêàëÿð
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> res((*this));
	for (int i = res.GetStartIndex(); i < res.GetSize(); i++)
	{
		res[i] += val;
	}
	return res;
}

template <class ValType> // âû÷åñòü ñêàëÿð
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> res((*this));
	for (int i = res.GetStartIndex(); i < res.GetSize(); i++)
	{
		res[i] -= val;
	}
	return res;
}

template <class ValType> // óìíîæèòü íà ñêàëÿð
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> res((*this));
	for (int i = res.GetStartIndex(); i < res.GetSize(); i++)
	{
		res[i] *= val;
	}
	return res;
}

template <class ValType> // ñëîæåíèå
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if ((*this).GetSize() != v.GetSize()) throw logic_error("not equal size");
	TVector<ValType> res((*this));
	for (int i = res.GetStartIndex(); i < res.GetSize(); i++)
	{
		res[i] += v.GetVector()[i];
	}
	return res;
}

template <class ValType> // âû÷èòàíèå
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if ((*this).GetSize() != v.GetSize()) throw logic_error("not equal size");
	TVector<ValType> res((*this));
	for (int i = res.GetStartIndex(); i < res.GetSize(); i++)
	{
		res[i] -= v.GetVector()[i];
	}
	return res;
}

template <class ValType> // ñêàëÿðíîå ïðîèçâåäåíèå
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if ((*this).GetSize() != v.GetSize()) throw logic_error("not equal size");
	ValType res = 0;
	for (int i = v.GetStartIndex(); i<v.GetSize(); i++)
	{
		res += v.GetVector()[i] * (*this).GetVector()[i];
	}
	return sqrt(res);
}

