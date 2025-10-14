// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор -
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE )
            throw "Длинна вектора не должна равняться 0 или быть больше MAX_VECTOR_SIZE";
        pMem = new T[sz]();
    }
    TDynamicVector(T* arr, size_t size) : sz(size)
    {
        if (arr == nullptr)
            throw "Указатель на массив не должен быть равен nullptr";
        pMem = new T[size];
        std::copy(arr, arr + size, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        this->sz = v.sz;
        this->pMem = new T[v.sz];
        for (size_t i = 0; i  < v.sz ; ++i){
            this->pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept :  sz(v.sz), pMem(v.pMem)
    {
        v.sz = 0;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        delete [] pMem;
        pMem = nullptr;
        sz = 0;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;

        delete [] pMem;
        this->sz = v.sz;
        this->pMem = new T[v.sz];
        for (size_t i = 0; i < v.sz; ++i){
            this->pMem[i] = v.pMem[i];
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            delete[] pMem;
            sz = v.sz;
            pMem = v.pMem;
            v.sz = 0;
            v.pMem = nullptr;
        }
        return *this;
    }

    // индексация
    T& operator[](size_t ind)
    {
        return this->pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return this->pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (0 < ind || ind >= this->sz)
            throw "Индекс вне диапазона";
        return this->pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (0 < ind || ind >= this->sz)
            throw "Индекс вне диапазона";
        return this->pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (this == &v){return true;}
        if (this->sz != v.sz){return false;}
        for (size_t i = 0; i < this->sz; ++i){
            if (this->pMem[i] != v.pMem[i]){
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (this == &v){return false;}
        if (this->sz != v.sz){return true;}
        for (size_t i = 0; i < this->sz; ++i){
            if (this->pMem[i] != v.pMem[i]){
                return true;
            }
        }
        return false;
    }

    // скалярные операции
    TDynamicVector operator+(T val) const
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = this->pMem[i] + val;
        }
        return result;
    }
    TDynamicVector operator-(T val) const
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = this->pMem[i] - val;
        }
        return result;
    }
    TDynamicVector operator*(T val) const
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = this->pMem[i] * val;
        }
        return result;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v) const
    {
        if (this->sz != v.sz)
            throw "Складываются векторы разного размера";

        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] + v.pMem[i];
        }
        return result;
    }
    TDynamicVector operator-(const TDynamicVector& v) const
    {
        if (this->sz != v.sz)
            throw "Вычетаются векторы разного размера";

        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] - v.pMem[i];
        }
        return result;
    }
    T operator*(const TDynamicVector& v) const
    {
        if (this->sz != v.sz)
            throw "Умножатюся векторы разного размера";

        T result = T();
        for (size_t i = 0; i < sz; ++i) {
            result = result + pMem[i] * v.pMem[i];
        }
        return result;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }

    size_t size() const noexcept { return sz; }
};


// Динамическая матрица -
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s == 0 || s > MAX_MATRIX_SIZE)
            throw "Размер матрицы должен быть не равен 0 или не больше MAX_MATRIX_SIZE";
        for (size_t i = 0; i < sz; ++i)
            pMem[i] = TDynamicVector<T>(sz);
    }
    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; ++i) {
            if (pMem[i] != m.pMem[i])
                return false;
        }
        return true;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val) const
    {
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] * val;
        }
        return result;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] * v;
        }
        return result;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m) const
    {
        if (sz != m.sz)
            throw "Складываются матрицы разного размера";

        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] + m.pMem[i];
        }
        return result;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m) const
    {
        if (sz != m.sz)
            throw "Вычитаются матрицы разного размера";

        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] - m.pMem[i];
        }
        return result;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m) const
    {
        if (sz != m.sz)
            throw "Умножаются матрицы разного размера";

        TDynamicMatrix result(sz);

        for (size_t i = 0; i < sz; ++i) {
            for (size_t j = 0; j < sz; ++j) {
                T sum = T();
                for (size_t k = 0; k < sz; ++k) {
                    sum += pMem[i][k] * m.pMem[k][j];
                }
                result.pMem[i][j] = sum;
            }
        }
        return result;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i)
            istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i)
            ostr << v.pMem[i] << std::endl;
        return ostr;

    }
};

#endif
