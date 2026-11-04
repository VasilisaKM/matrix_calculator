#include <gtest/gtest.h>
#include "matrix.h"
#include <stdexcept>

// 1. НОРМАЛЬНЫЕ СЛУЧАИ
// 1.1. Создание матрицы
TEST(MatrixTest, CreateMatrix_NormalCase) {
    matrix::Matrix A = matrix::create_matrix(3, 4);
    
    EXPECT_EQ(A.rows, 3);
    EXPECT_EQ(A.cols, 4);
    EXPECT_NE(A.data, nullptr);
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_DOUBLE_EQ(A.data[i][j], 0.0);
        }
    }
    matrix::free_matrix(A);
}

// 1.2. Сложение матриц
TEST(MatrixTest, Addition_NormalCase) {
    matrix::Matrix A = matrix::create_matrix(2, 2);
    matrix::Matrix B = matrix::create_matrix(2, 2);
    
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;
    
    matrix::Matrix C = matrix::matrix_add(A, B);
    
    EXPECT_DOUBLE_EQ(C.data[0][0], 6.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 8.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 10.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 12.0);
    
    matrix::free_matrix(A);
    matrix::free_matrix(B);
    matrix::free_matrix(C);
}

// 1.3. Умножение матриц
TEST(MatrixTest, Multiplication_NormalCase) {
    matrix::Matrix A = matrix::create_matrix(2, 2);
    matrix::Matrix B = matrix::create_matrix(2, 2);
    
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;
    
    matrix::Matrix C = matrix::matrix_multiply(A, B);
    
    EXPECT_DOUBLE_EQ(C.data[0][0], 19.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 22.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 43.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 50.0);
    
    matrix::free_matrix(A);
    matrix::free_matrix(B);
    matrix::free_matrix(C);
}

// 1.4. Транспонирование
TEST(MatrixTest, Transpose_NormalCase) {
    matrix::Matrix A = matrix::create_matrix(2, 3);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;
    
    matrix::Matrix T = matrix::matrix_transpose(A);
    
    EXPECT_EQ(T.rows, 3);
    EXPECT_EQ(T.cols, 2);
    EXPECT_DOUBLE_EQ(T.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(T.data[0][1], 4.0);
    EXPECT_DOUBLE_EQ(T.data[1][0], 2.0);
    EXPECT_DOUBLE_EQ(T.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(T.data[2][0], 3.0);
    EXPECT_DOUBLE_EQ(T.data[2][1], 6.0);
    
    matrix::free_matrix(A);
    matrix::free_matrix(T);
}

// 1.5. Освобождение памяти
TEST(MatrixTest, FreeMatrix_NormalCase) {
    matrix::Matrix A = matrix::create_matrix(3, 3);
    EXPECT_NO_THROW(matrix::free_matrix(A));
}

// 1.6. ВАРИАНТ 18: Симметричность
TEST(MatrixTest, IsSymmetric_NormalCase) {
    double arr[] = {1, 2, 3, 2, 5, 6, 3, 6, 9}; // Симметричная 3x3
    matrix::Matrix A = matrix::matrix_from_array(arr, 3, 3);
    EXPECT_TRUE(matrix::matrix_is_symmetric(A, 1e-9));
    matrix::free_matrix(A);
}

// 2. ГРАНИЧНЫЕ СЛУЧАИ
// 2.1. Минимальный размер 1x1
TEST(MatrixTest, CreateMatrix_MinimumSize) {
    matrix::Matrix A = matrix::create_matrix(1, 1);
    EXPECT_EQ(A.rows, 1);
    EXPECT_EQ(A.cols, 1);
    EXPECT_DOUBLE_EQ(A.data[0][0], 0.0);
    matrix::free_matrix(A);
}

// 2.2. Умножение вектор-строка на вектор-столбец (1x1)
TEST(MatrixTest, Multiplication_RowTimesColumn_1x1) {
    matrix::Matrix A = matrix::create_matrix(1, 3);
    matrix::Matrix B = matrix::create_matrix(3, 1);
    
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    B.data[0][0] = 4; B.data[1][0] = 5; B.data[2][0] = 6;
    
    matrix::Matrix C = matrix::matrix_multiply(A, B);
    
    EXPECT_EQ(C.rows, 1);
    EXPECT_EQ(C.cols, 1);
    EXPECT_DOUBLE_EQ(C.data[0][0], 32.0);
    
    matrix::free_matrix(A);
    matrix::free_matrix(B);
    matrix::free_matrix(C);
}

// 2.3. Двойное транспонирование возвращает исходную матрицу
TEST(MatrixTest, TransposeTwice_ReturnsOriginal) {
    matrix::Matrix A = matrix::create_matrix(2, 3);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;

    matrix::Matrix T = matrix::matrix_transpose(A);   // 3x2
    matrix::Matrix TT = matrix::matrix_transpose(T);  // 2x3 — снова как A

    EXPECT_EQ(TT.rows, 2);
    EXPECT_EQ(TT.cols, 3);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_DOUBLE_EQ(TT.data[i][j], A.data[i][j]);
        }
    }

    matrix::free_matrix(A);
    matrix::free_matrix(T);
    matrix::free_matrix(TT);
}

// 2.4. ВАРИАНТ 18: Не квадратная матрица
TEST(MatrixTest, IsSymmetric_NotSquare) {
    double arr[] = {1, 2, 3, 4, 5, 6}; // 2x3
    matrix::Matrix A = matrix::matrix_from_array(arr, 2, 3);
    EXPECT_FALSE(matrix::matrix_is_symmetric(A, 1e-9));
    matrix::free_matrix(A);
}

// 3. НЕКОРРЕКТНЫЕ СЛУЧАИ
// 3.1. Нулевые размеры
TEST(MatrixTest, CreateMatrix_ZeroRows) {
    EXPECT_THROW(matrix::create_matrix(0, 3), std::invalid_argument);
}

// 3.2. Отрицательные размеры
TEST(MatrixTest, CreateMatrix_NegativeCols) {
    EXPECT_THROW(matrix::create_matrix(3, -1), std::invalid_argument);
}

// 3.3. Сложение матриц разных размеров
TEST(MatrixTest, Addition_SizeMismatch) {
    matrix::Matrix A = matrix::create_matrix(2, 2);
    matrix::Matrix B = matrix::create_matrix(3, 3);
    
    EXPECT_THROW(matrix::matrix_add(A, B), std::invalid_argument);
    
    matrix::free_matrix(A);
    matrix::free_matrix(B);
}

// 3.4. Умножение несовместимых матриц
TEST(MatrixTest, Multiplication_SizeMismatch) {
    matrix::Matrix A = matrix::create_matrix(2, 3);
    matrix::Matrix B = matrix::create_matrix(2, 2);
    
    EXPECT_THROW(matrix::matrix_multiply(A, B), std::invalid_argument);
    
    matrix::free_matrix(A);
    matrix::free_matrix(B);
}

// 3.5. Освобождение памяти для пустой матрицы (Nullptr)
TEST(MatrixTest, FreeMatrix_Nullptr) {
    matrix::Matrix empty_mat;
    empty_mat.data = nullptr;
    empty_mat.rows = 0;
    empty_mat.cols = 0;
    
    // Не должно быть падения или исключения
    EXPECT_NO_THROW(matrix::free_matrix(empty_mat));
}
// 3.6. ВАРИАНТ 18: Проверка симметричности пустой матрицы
TEST(MatrixTest, IsSymmetric_Nullptr) {
    matrix::Matrix empty_mat;
    empty_mat.data = nullptr;
    empty_mat.rows = 0;
    empty_mat.cols = 0;

    EXPECT_FALSE(matrix::matrix_is_symmetric(empty_mat, 1e-9));
}