#include "matrix.h"
#include <iostream>

int main() {
    try {
        // 1. Создаем симметричную матрицу
        double arr_sym[] = {1, 2, 3, 2, 5, 6, 3, 6, 9};
        matrix::Matrix A = matrix::matrix_from_array(arr_sym, 3, 3);
        
        std::cout << "Matrix A:\n";
        matrix::print_matrix(A);

        // 2. Проверяем на симметричность (Вариант 18)
        bool is_sym = matrix::matrix_is_symmetric(A, 1e-9);
        std::cout << "Is symmetric? " << (is_sym ? "Yes" : "No") << "\n\n";

        // 3. Создаем несимметричную матрицу
        double arr_asym[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        matrix::Matrix B = matrix::matrix_from_array(arr_asym, 3, 3);
        std::cout << "Matrix B:\n";
        matrix::print_matrix(B);
        std::cout << "Is symmetric? " << (matrix::matrix_is_symmetric(B, 1e-9) ? "Yes" : "No") << "\n\n";

        // 4. Базовые операции
        matrix::Matrix C = matrix::matrix_add(A, B);
        std::cout << "Matrix A + B:\n";
        matrix::print_matrix(C);

        // 5. Освобождение памяти
        matrix::free_matrix(A);
        matrix::free_matrix(B);
        matrix::free_matrix(C);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}