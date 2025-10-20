#ifndef TYPES_OF_MATRIX_H
#define TYPES_OF_MATRIX_H

#include "tmatrix.h"
#include <vector>
#include <stdexcept>
#include <cmath>
using namespace std;

//const int MAX_MATRIX_SIZE = 1000;

//Ленточная матрица - матрица, где ненулевые элементы расположены только на главной диагонали и нескольких соседних диагоналях.
//Пример
//[a1 a2 0 0]            [0  a1 a2]             general band matrix
//[a3 a4 a5 0]           [a3 a4 a5]
//[0 a6 a7 a8]           [a6 a7 a8]
//[0 0 a9 a10]           [0 a9 a10]

template<typename T>
class TGeneralBandMatrix : public TDynamicMatrix<T>
{
protected:
    int n;
    int lower_bandwidth;  //кол-во диагоналей ниде главной
    int upper_bandwidth;  //кол-во диагоналей выше главной
    //храним только ненулевые элементы(в виде вектора диагоналей)
    vector<TDynamicVector<T>> diagonals; //тут все диагонали
public:
    TGeneralBandMatrix(int n, int lbw = 0, int ubw = 0) : TDynamicMatrix<T>(n), lower_bandwidth(lbw), upper_bandwidth(ubw)
    {
        if (n == 0 || n > MAX_MATRIX_SIZE)
            throw ("wrong size");
        if (lbw >= n || ubw >= n)
            throw ("wight must be less, then matrix size");
        // Создаём диагонали
        int all_diag = lbw + ubw + 1;  //+1 для главной
        diagonals.resize(all_diag); //создаёт пустые вект, diagonals[0], diagonals[1], diagonals[2] 
        for (int i = 0; i < all_diag; ++i) {
            int distance_from_center = abs(i - lbw);
            int diag_len = n - distance_from_center;
            diagonals[i] = TDynamicVector<T>(diag_len);
        }
    }
    // Доступ к элементу матрицы по индексам 
    T& operator()(int i, int j) {
        if (i >= this->size() || j >= this->size()) {
            throw ("invalid index");
        }
        int diff = j - i;  //if diff = 0, главная диагональ
        if (diff < -lower_bandwidth || diff > upper_bandwidth) {
            throw ("invalid elem");
        }
        // Находим диагональ и позицию в ней
        int diag_index = lower_bandwidth + diff;//номер диагонали сдвиг от главной
        int pos_in_diag = min(i, j);
        return diagonals[diag_index][pos_in_diag];
    }
    // Константная версия
    const T& operator()(int i, int j) const {
        if (i >= this->size() || j >= this->size()) {
            throw ("invalid index");
        }
        int diff = j - i;
        if (diff < -lower_bandwidth || diff > upper_bandwidth) {
            throw ("invalid elem");
        }
        int diag_index = lower_bandwidth + diff;
        int pos_in_diag = min(i, j);
        return diagonals[diag_index][pos_in_diag];
    }
    // Вывод матрицы
    friend ostream& operator<<(ostream& ostr, const TGeneralBandMatrix& m) {
        for (int i = 0; i < m.sz; ++i) {
            for (int j = 0; j < m.sz; ++j) {
                try {
                    ostr << m(i, j) << " ";
                }
                catch (...) {
                    ostr << "0 ";  //вне ленты-ноль
                }
            }
            ostr << endl;
        }
        return ostr;
    }
    int get_lower_bandwidth() const { return lower_bandwidth; }
    int get_upper_bandwidth() const { return upper_bandwidth; }
};
//Симметричная.Матрица, где A[i][j] = A[j][i].Достаточно хранить только верхнюю часть
template<typename T>
class TSymmetricBandMatrix : public TGeneralBandMatrix<T> {
public:
    TSymmetricBandMatrix(int n, int bandwidth) : TGeneralBandMatrix<T>(n, bandwidth, bandwidth) {}
    T& operator()(int i, int j) {   // При доступе к нижнему треугольнику — читаем из верхнего
        if (i > j) {
            return TGeneralBandMatrix<T>::operator()(j, i);  // симметрия
        }
        return TGeneralBandMatrix<T>::operator()(i, j);
    }
    const T& operator()(int i, int j) const {
        if (i > j) {
            return TGeneralBandMatrix<T>::operator()(j, i);
        }
        return TGeneralBandMatrix<T>::operator()(i, j);
    }
};
//Треугольная ленточная матрица-только верхняя или только нижняя часть
template<typename T>
class TTriangleBandMatrix : public TGeneralBandMatrix<T> {
private:
    bool is_upper;  //true-верхняя,false-нижняя
public:
    TTriangleBandMatrix(int n, int bandwidth, bool upper = false) : TGeneralBandMatrix<T>(n, upper ? 0 : bandwidth, upper ? bandwidth : 0), is_upper(upper) {}

    // Доступ к элементу
    T& operator()(int i, int j)
    {
        if (is_upper) {
            // Верхняя треугольная: i должен быть <= j
            if (i > j)
                throw out_of_range("Верхняя матрица: нельзя обращаться ниже диагонали");
        }
        else {
            // Нижняя треугольная: i должен быть >= j  
            if (i < j)
                throw out_of_range("Нижняя матрица: нельзя обращаться выше диагонали");
        }

        return TGeneralBandMatrix<T>::operator()(i, j);
    }

    // Константный доступ
    const T& operator()(int i, int j) const
    {
        if (is_upper) {
            if (i > j)
                throw out_of_range("Верхняя матрица: нельзя обращаться ниже диагонали");
        }
        else {
            if (i < j)
                throw out_of_range("Нижняя матрица: нельзя обращаться выше диагонали");
        }

        return TGeneralBandMatrix<T>::operator()(i, j);
    }

    // Вывод матрицы
    friend ostream& operator<<(ostream& ostr, const TTriangleBandMatrix& m)
    {
        for (int i = 0; i < m.size(); i++) {
            for (int j = 0; j < m.size(); j++) {
                try {
                    ostr << m(i, j) << "\t";
                }
                catch (...) {
                    ostr << "0\t";  // запрещённая область = 0
                }
            }
            ostr << endl;
        }
        return ostr;
    }

    // Простые методы для получения информации
    bool is_upper_triangle() const { return is_upper; }
    bool is_lower_triangle() const { return !is_upper; }
    int size() const { return this->sz; }
};
// Сжатое хранение по строкам (CSR) - только ненулевые элементы
template<typename T>
class TCSRMatrix {
private:
    int rows, cols;
    vector<T> values;        // ненулевые значения
    vector<int> col_indices; // номера столбцов
    vector<int> row_index;   // нач индекс
public:
    TCSRMatrix(int r, int c) : rows(r), cols(c) {
        if (r <= 0 || c <= 0 || r > MAX_MATRIX_SIZE || c > MAX_MATRIX_SIZE) {
            throw ("invalid size");
        }
        row_index.resize(rows + 1, 0);
    }
    void set(int i, int j, T val) {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            throw ("invalid index");
        }
        if (val == T(0)) {
            // Если элемент уже существует - удаляем его
            int start = row_index[i];
            int end = row_index[i + 1];
            for (int k = start; k < end; ++k) {
                if (col_indices[k] == j) {
                    values.erase(values.begin() + k);
                    col_indices.erase(col_indices.begin() + k);
                    // Обновляем индексы строк
                    for (int m = i + 1; m <= rows; ++m)
                        row_index[m]--;
                    return;
                }
            }
            return;
        }
        int start = row_index[i];
        int end = row_index[i + 1];
        // Ищем существующий элемент
        for (int k = start; k < end; ++k) {
            if (col_indices[k] == j) {
                values[k] = val;
                return;
            }
        }
        // Добавляем новый
        values.insert(values.begin() + end, val);
        col_indices.insert(col_indices.begin() + end, j);
        // Обновляем индексы строк
        for (int k = i + 1; k <= rows; ++k) {
            row_index[k]++;
        }
    }
    T get(int i, int j) const {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            throw ("invalid index");
        }
        int start = row_index[i];
        int end = row_index[i + 1];
        for (int k = start; k < end; ++k) {
            if (col_indices[k] == j) {
                return values[k];
            }
        }
        return T(); // ноль
    }
    T operator()(int i, int j) const { return get(i, j); }
    friend ostream& operator<<(ostream& ostr, const TCSRMatrix& m) {
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j) {
                ostr << m.get(i, j) << " ";
            }
            ostr << endl;
        }
        return ostr;
    }
    int get_rows() const { return rows; }
    int get_cols() const { return cols; }
    int non_zeros() const { return values.size(); }
};
#endif 
