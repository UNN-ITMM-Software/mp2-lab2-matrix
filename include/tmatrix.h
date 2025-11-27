// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
#ifndef __TDYNAMICMATRIX_H__
#define __TDYNAMICMATRIX_H__

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("err");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("err");
        pMem = new T[sz]();
    }

    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "err");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("err");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(new T[v.sz])
    {
        std::copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
    {
        v.sz = 0;
        v.pMem = nullptr;
    }

    ~TDynamicVector()
    {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            if (sz != v.sz) {
                delete[] pMem;
                sz = v.sz;
                pMem = new T[sz];
            }
            std::copy(v.pMem, v.pMem + sz, pMem);
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

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }

    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("err");
        return pMem[ind];
    }

    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("err");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) return false;
        }
        return true;
    }

    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++)
            res.pMem[i] = pMem[i] + val;
        return res;
    }

    TDynamicVector operator-(T val)
    {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++)
            res.pMem[i] = pMem[i] - val;
        return res;
    }

    TDynamicVector operator*(T val)
    {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++)
            res.pMem[i] = pMem[i] * val;
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("err");
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++)
            res.pMem[i] = pMem[i] + v.pMem[i];
        return res;
    }

    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("err");
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++)
            res.pMem[i] = pMem[i] - v.pMem[i];
        return res;
    }

    T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("err");
        T res = T();
        for (size_t i = 0; i < sz; i++)
            res += pMem[i] * v.pMem[i];
        return res;
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
            istr >> v.pMem[i];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' ';
        return ostr;
    }
};


// Динамическая матрица -  шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s > MAX_MATRIX_SIZE)
            throw out_of_range("err");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    // явное объявление доступа к методам базового класса
    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::size;

    // явное объявление метода at() для матрицы
    TDynamicVector<T>& at(size_t ind)
    {
        return TDynamicVector<TDynamicVector<T>>::at(ind);
    }

    const TDynamicVector<T>& at(size_t ind) const
    {
        return TDynamicVector<TDynamicVector<T>>::at(ind);
    }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != m.pMem[i]) return false;
        }
        return true;
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(*this == m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            res[i] = pMem[i] * val;
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size())
            throw invalid_argument("err");
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++)
            res[i] = pMem[i] * v;
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("err");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            res[i] = pMem[i] + m[i];
        return res;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("err");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            res[i] = pMem[i] - m[i];
        return res;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("err");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                T sum = T();
                for (size_t k = 0; k < sz; k++)
                    sum += pMem[i][k] * m[k][j];
                res[i][j] = sum;
            }
        }
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++)
            istr >> m.pMem[i];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++) {
            for (size_t j = 0; j < m.sz; j++)
                ostr << m.pMem[i][j] << ' ';
            ostr << '\n';
        }
        return ostr;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Верхняя треугольная матрица
template<typename T>
class TUpperTriangularMatrix {
private:
    size_t sz;
    TDynamicVector<T> data;

public:
    TUpperTriangularMatrix(size_t size = 1) : sz(size), data(sz* (sz + 1) / 2) {
        if (sz == 0) throw out_of_range("err");
    }

    size_t size() const noexcept { return sz; }

    // Индексация
    T& at(size_t i, size_t j) {
        if (i >= sz || j >= sz || i > j)
            throw out_of_range("err");
        return data[i * (2 * sz - i - 1) / 2 + (j - i)];
    }

    const T& at(size_t i, size_t j) const {
        if (i >= sz || j >= sz || i > j)
            throw out_of_range("err");
        return data[i * (2 * sz - i - 1) / 2 + (j - i)];
    }

    // безопасное получение элемента
    T get(size_t i, size_t j) const {
        return (i <= j && i < sz && j < sz) ? at(i, j) : T();
    }

    // умножение на вектор
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const {
        if (sz != v.size()) throw invalid_argument("err");

        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            T sum = T();
            for (size_t j = i; j < sz; j++) {
                sum += get(i, j) * v[j];
            }
            res[i] = sum;
        }
        return res;
    }
};

// Ленточная матрица
template<typename T>
class TBandMatrix {
private:
    size_t sz;
    size_t bandWidth;
    TDynamicVector<T> data; // данные в виде вектора
    T zero = T(); 

public:
    TBandMatrix(size_t size = 1, size_t bandwidth = 1) : sz(size), bandWidth(bandwidth), data(sz* (2 * bandWidth + 1)) {
        if (sz == 0)
            throw out_of_range("err");
        if (bandWidth >= sz)
            throw out_of_range("err");
    }

    size_t size() const noexcept { return sz; }
    size_t getBandWidth() const noexcept { return bandWidth; }

    // индексация с проверкой на принадлежность ленте
    T& at(size_t i, size_t j) {
        if (i >= sz || j >= sz)
            throw out_of_range("Index out of range");

        long diff = static_cast<long>(j) - static_cast<long>(i);
        if (diff > static_cast<long>(bandWidth) || diff < -static_cast<long>(bandWidth))
            throw out_of_range("Element outside band");

        return data[i * (2 * bandWidth + 1) + (j - i + bandWidth)];
    }

    const T& at(size_t i, size_t j) const {
        if (i >= sz || j >= sz)
            throw out_of_range("Index out of range");

        long diff = static_cast<long>(j) - static_cast<long>(i);
        if (diff > static_cast<long>(bandWidth) || diff < -static_cast<long>(bandWidth))
            return zero;

        return data[i * (2 * bandWidth + 1) + (j - i + bandWidth)];
    }

    // умножение на вектор 
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const {
        if (sz != v.size())
            throw invalid_argument("err");

        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            T sum = T();
            // границы для оптимизации
            size_t start_j = (i > bandWidth) ? i - bandWidth : 0;
            size_t end_j = (i + bandWidth < sz) ? i + bandWidth + 1 : sz;

            for (size_t j = start_j; j < end_j; j++) {
                long diff = static_cast<long>(j) - static_cast<long>(i);
                if (diff >= -static_cast<long>(bandWidth) && diff <= static_cast<long>(bandWidth)) {
                    sum += at(i, j) * v[j];
                }
            }
            res[i] = sum;
        }
        return res;
    }
};

// CSR матрица

template<typename T>
class TCSRMatrix {
private:
    size_t sz;
    TDynamicVector<T> values;    // Ненулевые значения
    TDynamicVector<size_t> cols; // Столбцы ненулевых элементов
    TDynamicVector<size_t> rows; // Индексы начала строк

public:
    TCSRMatrix(size_t size = 1) : sz(size), rows(sz + 1) {
        if (sz == 0)
            throw out_of_range("err");
        rows[0] = 0;
    }

    TCSRMatrix(const TDynamicMatrix<T>& dense) : sz(dense.size()), rows(sz + 1) {
        rows[0] = 0;

        // подсчет количества ненулевых элементов
        size_t nonZeroCount = 0;
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                if (dense[i][j] != T()) {
                    nonZeroCount++;
                }
            }
        }

        // выделяем память
        values = TDynamicVector<T>(nonZeroCount);
        cols = TDynamicVector<size_t>(nonZeroCount);

        // заполняем данные
        size_t idx = 0;
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                if (dense[i][j] != T()) {
                    values[idx] = dense[i][j];
                    cols[idx] = j;
                    idx++;
                }
            }
            rows[i + 1] = idx;
        }
    }

    size_t size() const noexcept { return sz; }
    size_t nonZeros() const noexcept { return values.size(); }

    // умножение на вектор
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const {
        if (sz != v.size())
            throw invalid_argument("err");

        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            T sum = T();
            for (size_t j = rows[i]; j < rows[i + 1]; j++) {
                sum += values[j] * v[cols[j]];
            }
            res[i] = sum;
        }
        return res;
    }

    // получение элемента
    T at(size_t i, size_t j) const {
        if (i >= sz || j >= sz)
            throw out_of_range("err");

        for (size_t k = rows[i]; k < rows[i + 1]; k++) {
            if (cols[k] == j) {
                return values[k];
            }
        }
        return T();
    }

    // установка элемента
    void set(size_t i, size_t j, const T& value) {
        if (i >= sz || j >= sz)
            throw out_of_range("err");

        // создаем временную плотную матрицу
        TDynamicMatrix<T> dense(sz);

        for (size_t row = 0; row < sz; row++) {
            for (size_t col = 0; col < sz; col++) {
                dense[row][col] = this->at(row, col);
            }
        }

        dense[i][j] = value;

        // пересоздание CSR матрицы
        *this = TCSRMatrix<T>(dense);
    }

    // оператор присваивания
    TCSRMatrix& operator=(const TCSRMatrix& other) {
        if (this != &other) {
            sz = other.sz;
            values = other.values;
            cols = other.cols;
            rows = other.rows;
        }
        return *this;
    }
};
#endif