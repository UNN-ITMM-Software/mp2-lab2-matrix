#ifndef TYPES_OF_MATRIX_H
#define TYPES_OF_MATRIX_H

#include "tmatrix.h"
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iomanip>
using namespace std;

//const int MAX_MATRIX_SIZE = 1000;

//Ленточная матрица - матрица, где ненулевые элементы расположены только на главной диагонали и нескольких соседних диагоналях.
//Пример
//[a1 a2 0 0]            [0  a1 a2]             general band matrix
//[a3 a4 a5 0]           [a3 a4 a5]
//[0 a6 a7 a8]           [a6 a7 a8]
//[0 0 a9 a10]           [0 a9 a10]

template<typename T>
class TGeneralBandMatrix : public TDynamicMatrix<T>{
protected:
    int n;
    int lower_bandwidth;   //кол-во диагоналей ниде главной
    int upper_bandwidth;   //кол-во диагоналей выше главной
    //храним только ненулевые элементы(в виде вектора диагоналей)
    vector<TDynamicVector<T>> diagonals;  //тут все диагонали
public:
    TGeneralBandMatrix(int n, int lbw = 0, int ubw = 0) : TDynamicMatrix<T>(n), n(n), lower_bandwidth(lbw), upper_bandwidth(ubw){
        if (n == 0 || n > MAX_MATRIX_SIZE)
            throw ("wrong size");
        if (lbw >= n || ubw >= n)
            throw ("bandwidth must be less, than matrix size");
        // Создаем диагонали
        int total_diagonals = lbw + ubw + 1; //+1 для главной
        diagonals.resize(total_diagonals);   //создаёт пустые вект, diagonals[0], diagonals[1], diagonals[2] 
        for (int d = 0; d < total_diagonals; ++d) {
            int diag_offset = d - lbw; // смещение от главной диагонали (-lbw, ..., 0, ..., +ubw)
            int diag_length = n - abs(diag_offset);
            diagonals[d] = TDynamicVector<T>(diag_length);
        }
        // Инициализируем нулями
        for (auto& diag : diagonals) {
            for (int i = 0; i < diag.size(); i++) {
                diag[i] = T(0);
            }
        }
    }
    //доступ к элементам
    T& operator()(int i, int j) {
        int diff = j - i;
        //Проверка границ
        if (i < 0 || i >= n || j < 0 || j >= n) {
            throw out_of_range("Matrix indices out of range");
        }
        // Проверка нахождения в ленте
        if (diff < -lower_bandwidth || diff > upper_bandwidth) {
            throw out_of_range("Element outside bandwidth");
        }
        // Индекс диагонали (0..total_diagonals-1)
        int diag_index = lower_bandwidth + diff;
        // Позиция в диагонали - ВСЕГДА используем i
        int pos_in_diag = i;
        // Для верхних диагоналей корректируем позицию
        if (diff > 0) {
            pos_in_diag = i;
        }
        else {
            pos_in_diag = i + diff;
        }
        return diagonals[diag_index][pos_in_diag];
    }

    // Константная версия
    const T& operator()(int i, int j) const {
        int diff = j - i;
        if (i < 0 || i >= n || j < 0 || j >= n) {
            throw out_of_range("Matrix indices out of range");
        }
        if (diff < -lower_bandwidth || diff > upper_bandwidth) {
            throw out_of_range("Element outside bandwidth");
        }
        int diag_index = lower_bandwidth + diff;
        int pos_in_diag = (diff > 0) ? i : (i + diff);
        return diagonals[diag_index][pos_in_diag];
    }

    TGeneralBandMatrix<T> operator*(const TGeneralBandMatrix<T>& m) const {
        if (n != m.n) {
            throw ("Matrix sizes must match for multiplication");
        }
        // Создаем результат с максимальной шириной ленты
        TGeneralBandMatrix<T> result(n, n - 1, n - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                T sum = T(0);
                for (int k = 0; k < n; ++k) {
                    // Пытаемся получить элементы, игнорируя исключения
                    try {
                        T val1 = (*this)(i, k);
                        try {
                            T val2 = m(k, j);
                            sum += val1 * val2;
                        }
                        catch (...) {
                            // Элемент m(k,j) вне ленты = 0
                        }
                    }
                    catch (...) {
                        // Элемент (*this)(i,k) вне ленты = 0
                    }
                }
                // Записываем результат если он ненулевой
                if (sum != T(0)) {
                    try {
                        result(i, j) = sum;
                    }
                    catch (...) {
                        // Не можем записать в результат (вне ленты)
                    }
                }
            }
        }
        return result;
    }

    // Вывод матрицы
    friend ostream& operator<<(ostream& ostr, const TGeneralBandMatrix& m) {
        ostr << "General Band Matrix " << m.n << "x" << m.n << " (lbw=" << m.lower_bandwidth << ", ubw=" << m.upper_bandwidth << "):" << endl;
        for (int i = 0; i < m.n; ++i) {
            for (int j = 0; j < m.n; ++j) {
                try {
                    ostr << m(i, j) << "\t";
                }
                catch (...) {
                    ostr << "0\t";
                }
            }
            ostr << endl;
        }
        return ostr;
    }
    int size() const { return n; }
    int get_lower_bandwidth() const { return lower_bandwidth; }
    int get_upper_bandwidth() const { return upper_bandwidth; }

    void debug_info() const {
        cout << "Matrix: " << n << "x" << n << ", lbw=" << lower_bandwidth << ", ubw=" << upper_bandwidth << endl;
        cout << "Diagonals count: " << diagonals.size() << endl;
        for (int d = 0; d < diagonals.size(); d++) {
            int offset = d - lower_bandwidth;
            cout << "Diagonal " << d << " (offset=" << offset << ", size=" << diagonals[d].size() << ")" << endl;
        }
    }
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
    // Оператор умножения для симметричной матрицы
    TSymmetricBandMatrix<T> operator*(const TSymmetricBandMatrix<T>& m) const {
        if (this->n != m.n) {
            throw invalid_argument("matrix sizes must match for multiplication");
        }
        int max_bandwidth = min(this->n - 1, this->lower_bandwidth + m.lower_bandwidth);
        TSymmetricBandMatrix<T> result(this->n, max_bandwidth);

        for (int i = 0; i < this->n; ++i) {
            for (int j = i; j <= min(this->n - 1, i + max_bandwidth); ++j) {
                T sum = T(0);
                // Оптимизируем границы цикла по k
                int start_k = max(0, max(i - this->lower_bandwidth, j - m.lower_bandwidth));
                int end_k = min(this->n - 1, min(i + this->upper_bandwidth, j + m.upper_bandwidth));
                for (int k = start_k; k <= end_k; ++k) {
                    // Для симметричных матриц используем только верхний треугольник при доступе
                    T val1 = (i <= k) ? (*this)(i, k) : (*this)(k, i);
                    T val2 = (k <= j) ? m(k, j) : m(j, k);
                    sum += val1 * val2;
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    // Вывод
    friend ostream& operator<<(ostream& ostr, const TSymmetricBandMatrix& m) {
        ostr << "Symmetric Band Matrix " << m.n << "x" << m.n
            << " (bandwidth=" << m.lower_bandwidth << "):" << endl;

        for (int i = 0; i < m.n; ++i) {
            for (int j = 0; j < m.n; ++j) {
                try {
                    ostr << m(i, j) << " "; 
                }
                catch (...) {
                    ostr << "0 ";
                }
            }
            ostr << endl;
        }
        return ostr;
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
    T& operator()(int i, int j){
        if (is_upper) {
            if (i > j)
                throw out_of_range("Upper matrix: cannot be drawn below the diagonal");
        }
        else {
            if (i < j)
                throw out_of_range("Lower matrix: it is impossible to turn above the diagonal");
        }

        return TGeneralBandMatrix<T>::operator()(i, j);
    }

    //Константный доступ
    const T& operator()(int i, int j) const{
        if (is_upper) {
            if (i > j)
                throw ("Upper matrix: cannot be drawn below the diagonal");
        }
        else {
            if (i < j)
                throw ("Lower matrix: it is impossible to turn above the diagonal");
        }
        return TGeneralBandMatrix<T>::operator()(i, j);
    }

    //умножение
    TTriangleBandMatrix<T> operator*(const TTriangleBandMatrix<T>& m) const {
        if (this->n != m.n) {
            throw ("matrix sizes must match for multiplication");
        }
        // Умножение треугольных матриц сохраняет треугольность
        int bandwidth = min(this->n - 1, this->upper_bandwidth + m.upper_bandwidth);
        TTriangleBandMatrix<T> result(this->n, bandwidth, this->is_upper);
        for (int i = 0; i < this->n; ++i) {
            for (int j = (this->is_upper ? i : 0); j <= (this->is_upper ? this->n - 1 : i);  ++j) {
                T sum = T(0);
                int start_k = this->is_upper ? i : 0;
                int end_k = this->is_upper ? j : min(i, j);
                for (int k = start_k; k <= end_k; ++k) {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    // Вывод матрицы
    friend ostream& operator<<(ostream& ostr, const TTriangleBandMatrix& m) {
        string type = m.is_upper ? "Upper" : "Lower";
        ostr << type << " Triangular Band Matrix " << m.n << "x" << m.n << " (bandwidth=" << m.upper_bandwidth << "):" << endl;
        for (int i = 0; i < m.n; ++i) {
            for (int j = 0; j < m.n; ++j) {
                try {
                    ostr << m(i, j) << " "; 
                }
                catch (...) {
                    ostr << "0 ";
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
    T operator()(int i, int j) const { 
        return get(i, j); 
    }

    //умножение
    TCSRMatrix<T> operator*(const TCSRMatrix<T>& m) const {
        if (cols != m.rows) {
            throw ("matrix dimensions don't match for multiplication");
        }
        TCSRMatrix<T> result(rows, m.cols);
        for (int i = 0; i < rows; ++i) {
            vector<T> row_result(m.cols, T(0));
            //для каждой строки i в первой матрице
            int start_i = row_index[i];
            int end_i = row_index[i + 1];
            for (int k_idx = start_i; k_idx < end_i; ++k_idx) {
                int k = col_indices[k_idx];
                T val_ik = values[k_idx];
                //умножаем на соотв столбец k во второй матрице
                int start_k = m.row_index[k];
                int end_k = m.row_index[k + 1];
                for (int j_idx = start_k; j_idx < end_k; ++j_idx) {
                    int j = m.col_indices[j_idx];
                    row_result[j] += val_ik * m.values[j_idx];
                }
            }
            //добавляем ненулевые элементы в результат
            for (int j = 0; j < m.cols; ++j) {
                if (row_result[j] != T(0)) {
                    result.set(i, j, row_result[j]);
                }
            }
        }
        return result;
    }
    //Вывод
    friend ostream& operator<<(ostream& ostr, const TCSRMatrix& m) {
        ostr << "CSR Matrix " << m.rows << "x" << m.cols << " (ненулевое значение: " << m.values.size() << "):" << endl;
        //Вывод в плотном формате
        ostr << "Плотное представление:" << endl;
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
