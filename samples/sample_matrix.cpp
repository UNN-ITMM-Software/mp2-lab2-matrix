// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"

using namespace std;

void main()
{
    setlocale(LC_ALL, "Russian");

    cout << "=== Тестирование класса работы с матрицами ===" << endl;

    size_t size;
    cout << "Введите размер квадратных матриц (до " << MAX_MATRIX_SIZE << "): ";
    cin >> size;

    if (size == 0 || size > MAX_MATRIX_SIZE) {
        cout << "Ошибка: Неверный размер матрицы!" << endl;
        return;
    }

    try {
        TDynamicMatrix<int> a(size), b(size), c(size);

        cout << "\nВыберите способ заполнения матриц:" << endl;
        cout << "1. Заполнить автоматически (тестовыми данными)" << endl;
        cout << "2. Ввести элементы вручную с клавиатуры" << endl;
        int fillChoice;
        cin >> fillChoice;

        if (fillChoice == 2) {
            cout << "Введите элементы матрицы A по строкам (" << size * size << " чисел):" << endl;
            cin >> a;
            cout << "Введите элементы матрицы B по строкам (" << size * size << " чисел):" << endl;
            cin >> b;
        }
        else {
            for (size_t i = 0; i < size; i++) {
                for (size_t j = 0; j < size; j++) {
                    a[i][j] = (i + 1) * 10 + (j + 1);
                    b[i][j] = ((i + 1) * 10 + (j + 1)) * 2;
                }
            }
            cout << "\nМатрицы автоматически заполнены тестовыми данными." << endl;
        }

        cout << "\nМатрица A:" << endl << a << endl;
        cout << "Матрица B:" << endl << b << endl;

        cout << "Выберите операцию над матрицами:" << endl;
        cout << "1. Сложение (A + B)" << endl;
        cout << "2. Вычитание (A - B)" << endl;
        cout << "3. Умножение (A * B)" << endl;
        int opChoice;
        cin >> opChoice;

        switch (opChoice) {
        case 1:
            c = a + b;
            cout << "\nРезультат сложения C = A + B:" << endl << c << endl;
            break;
        case 2:
            c = a - b;
            cout << "\nРезультат вычитания C = A - B:" << endl << c << endl;
            break;
        case 3:
            c = a * b;
            cout << "\nРезультат умножения C = A * B:" << endl << c << endl;
            break;
        default:
            cout << "Ошибка: Неверный выбор операции!" << endl;
            break;
        }
    }
    catch (const exception& e) {
        cout << "\nПроизошла ошибка: " << e.what() << endl;
    }
}