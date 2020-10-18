#pragma once

#include "MyVector.h"

const int MAX_MATRIX_SIZE = 10000;

// Âåðõíåòðåóãîëüíàÿ ìàòðèöà
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix &mt);                    // êîïèðîâàíèå
	TMatrix(const TVector<TVector<ValType> > &mt); // ïðåîáðàçîâàíèå òèïà
	bool operator==(const TMatrix &mt) const;      // ñðàâíåíèå
	bool operator!=(const TMatrix &mt) const;      // ñðàâíåíèå
	TMatrix& operator= (const TMatrix &mt);        // ïðèñâàèâàíèå
	TMatrix  operator+ (const TMatrix &mt);        // ñëîæåíèå
	TMatrix  operator- (const TMatrix &mt);        // âû÷èòàíèå

												   // ââîä / âûâîä
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
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if ((s<0) || (s > MAX_MATRIX_SIZE)) throw logic_error("incorrect parametr");
	for (int i = 0; i < s; i++)
	{
		TVector<ValType>Res(i + 1);
		(*this)[i] = Res;
	}
}

template <class ValType> // êîíñòðóêòîð êîïèðîâàíèÿ
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) :TVector<TVector<ValType> >(mt)
{
	for (int i = 0; i < (*this).GetSize(); i++)
	{
		TVector<ValType>mt(mt[i]);
		(*this)[i] = mt;
	}
	Size = mt.GetSize();
	StartIndex = mt.GetStartIndex();
}

template <class ValType> // êîíñòðóêòîð ïðåîáðàçîâàíèÿ òèïà
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) :TVector<TVector<ValType> >(mt)
{
	for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++)
	{
		TVector<ValType>ms(mt[i]);
		(*this)[i] = ms;
	}
	Size = mt.GetSize();
	StartIndex = mt.GetStartIndex();
}

template <class ValType> // ñðàâíåíèå
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
}

template <class ValType> // ñðàâíåíèå
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !((*this) == mt);
}

template <class ValType> // ïðèñâàèâàíèå
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

}

template <class ValType> // ñëîæåíèå
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (mt.GetSize() != (*this).GetSize()) throw logic_error("incorrect size");
	TMatrix<ValType>Res(*this);
	for (int i = Res.GetStartIndex(); i < Res.GetSize(); i++)
	{
		Res[i] = (*this).GetVector()[i] + mt.GetVector()[i];
	}
	return Res;

}

template <class ValType> // âû÷èòàíèå
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (mt.GetSize() != (*this).GetSize()) throw logic_error("incorrect size");
	TMatrix<ValType>Res(*this);
	for (int i = Res.GetStartIndex(); i < Res.GetSize(); i++)
	{
		Res[i] = (*this)[i] - mt.GetVector()[i];
	}
	return Res;
}

