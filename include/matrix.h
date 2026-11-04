#pragma once

#include <stdexcept>

/**
 * @file matrix.h
 * @brief Библиотека для работы с матрицами (Вариант 18).
 * @author Студент
 */

namespace matrix {

/**
 * @brief Структура матрицы.
 * Хранит двумерный динамический массив и его размеры.
 * @warning Память освобождается через free_matrix().
 */
typedef struct {
    double** data; ///< Указатель на двумерный массив.
    int rows;      ///< Количество строк.
    int cols;      ///< Количество столбцов.
} Matrix;

/**
 * @brief Создание матрицы заданного размера.
 * @param rows Количество строк (> 0).
 * @param cols Количество столбцов (> 0).
 * @return Matrix Инициализированная нулями матрица.
 * @exception std::invalid_argument Если rows <= 0 или cols <= 0.
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождение памяти.
 * @param m Матрица для освобождения.
 */
void free_matrix(Matrix m);

/**
 * @brief Сложение двух матриц.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Matrix Результат сложения.
 * @exception std::invalid_argument Если размеры не совпадают.
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Умножение двух матриц.
 * @param a Матрица MxN.
 * @param b Матрица NxK.
 * @return Matrix Результат MxK.
 * @exception std::invalid_argument Если cols(a) != rows(b).
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Вывод матрицы в консоль.
 * @param m Матрица для вывода.
 */
void print_matrix(Matrix m);

/**
 * @brief Создание матрицы из массива.
 * @param data Указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Matrix Новая матрица.
 */
Matrix matrix_from_array(double* data, int rows, int cols);

/**
 * @brief Проверка на симметричность (Вариант 18).
 * @param m Матрица.
 * @param tolerance Погрешность.
 * @return true Если симметрична.
 * @return false Если нет.
 */
bool matrix_is_symmetric(Matrix m, double tolerance);

/**
 * @brief Транспонирование матрицы.
 * @param m Исходная матрица.
 * @return Matrix Транспонированная матрица.
 */
Matrix matrix_transpose(Matrix m);
} // namespace matrix