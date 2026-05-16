#include <algorithm> // std::swap
#include <cmath> // abs
#include <cstddef>
#include <iomanip> // setw, setprecision
#include <iostream> // ввод и вывод
#include <limits> // numeric_limits
#include <random> // генератор случайных чисел

// генератор случайных чисел
std::mt19937 gen(std::random_device{}());

// создание одномерного массива
int* createArray1D(const std::size_t size) {
    return new int[size];
}

// создание двумерного массива
double** createMatrix(const std::size_t rows,
    const std::size_t cols) {

    double** matrix{ new double* [rows] };

    for (std::size_t i{}; i < rows; ++i) {
        matrix[i] = new double[cols];
    }

    return matrix;
}

// создание трехмерного массива
int*** createArray3D(const std::size_t d1,
    const std::size_t d2,
    const std::size_t d3) {

    int*** arr{ new int** [d1] };

    for (std::size_t i{}; i < d1; ++i) {

        arr[i] = new int* [d2];

        for (std::size_t j{}; j < d2; ++j) {
            arr[i][j] = new int[d3];
        }
    }

    return arr;
}

// заполнение одномерного массива
void fillArray1D(int* const arr,
    const std::size_t size,
    const int min_val,
    const int max_val) {

    std::uniform_int_distribution<> dist(min_val, max_val);

    for (std::size_t i{}; i < size; ++i) {
        arr[i] = dist(gen);
    }
}

// заполнение матрицы
void fillMatrix(double** const matrix,
    const std::size_t rows,
    const std::size_t cols,
    const double min_val,
    const double max_val) {

    std::uniform_real_distribution<> dist(min_val, max_val);

    for (std::size_t i{}; i < rows; ++i) {

        for (std::size_t j{}; j < cols; ++j) {
            matrix[i][j] = dist(gen);
        }
    }
}

// заполнение трехмерного массива
void fillArray3D(int*** const arr,
    const std::size_t d1,
    const std::size_t d2,
    const std::size_t d3,
    const int min_val,
    const int max_val) {

    std::uniform_int_distribution<> dist(min_val, max_val);

    for (std::size_t i{}; i < d1; ++i) {

        for (std::size_t j{}; j < d2; ++j) {

            for (std::size_t k{}; k < d3; ++k) {
                arr[i][j][k] = dist(gen);
            }
        }
    }
}

// вывод одномерного массива
void printArray1D(const int* const arr,
    const std::size_t size) {

    for (std::size_t i{}; i < size; ++i) {

        std::cout << std::setw(6) << arr[i] << " ";

        if ((i + 1) % 10 == 0)
            std::cout << "\n";
    }

    std::cout << "\n";
}

// вывод матрицы
void printMatrix(double* const* const matrix,
    const std::size_t rows,
    const std::size_t cols) {

    for (std::size_t i{}; i < rows; ++i) {

        for (std::size_t j{}; j < cols; ++j) {

            std::cout << std::fixed
                << std::setprecision(2)
                << std::setw(8)
                << matrix[i][j] << " ";
        }

        std::cout << "\n";
    }
}

// удаление одномерного массива
void deleteArray1D(int* const arr) {
    delete[] arr;
}

// удаление матрицы
void deleteMatrix(double** const matrix,
    const std::size_t rows) {

    for (std::size_t i{}; i < rows; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

// удаление трехмерного массива
void deleteArray3D(int*** const arr,
    const std::size_t d1,
    const std::size_t d2) {

    for (std::size_t i{}; i < d1; ++i) {

        for (std::size_t j{}; j < d2; ++j) {
            delete[] arr[i][j];
        }

        delete[] arr[i];
    }

    delete[] arr;
}

// задача 1
void task1() {

    std::cout << "\nЗАДАЧА 1: вставка 0 в середину массива\n";

    const std::size_t SIZE{ 20 };

    // создание массива
    int* arr{ createArray1D(SIZE + 1) };

    // заполнение массива
    fillArray1D(arr, SIZE, 1, 100);

    std::cout << "Исходный массив:\n";

    printArray1D(arr, SIZE);

    // сдвиг элементов вправо
    for (std::size_t i{ SIZE - 1 }; i >= 10; --i) {

        *(arr + i + 1) = *(arr + i);
    }

    // вставка 0 в середину
    *(arr + 10) = 0;

    std::cout << "\nМассив после вставки:\n";

    printArray1D(arr, SIZE + 1);

    // удаление массива
    deleteArray1D(arr);
}

// задача 2
void task2() {

    std::cout << "\nЗАДАЧА 2: сортировка по убыванию\n";

    const std::size_t SIZE{ 15 };

    int* arr{ createArray1D(SIZE) };

    fillArray1D(arr, SIZE, 1, 100);

    std::cout << "Исходный массив:\n";

    printArray1D(arr, SIZE);

    // сортировка пузырьком
    for (std::size_t i{}; i < SIZE - 1; ++i) {

        for (std::size_t j{}; j < SIZE - 1 - i; ++j) {

            if (arr[j] < arr[j + 1]) {

                std::swap(arr[j], arr[j + 1]);
            }
        }
    }

    std::cout << "\nОтсортированный массив:\n";

    printArray1D(arr, SIZE);

    deleteArray1D(arr);
}

// задача 3
void task3() {

    std::cout << "\nЗАДАЧА 3: обмен элементов матрицы\n";

    const std::size_t ROWS{ 7 };
    const std::size_t COLS{ 9 };

    double** matrix{ createMatrix(ROWS, COLS) };

    fillMatrix(matrix, ROWS, COLS, -50.0, 50.0);

    std::cout << "Исходная матрица:\n";

    printMatrix(matrix, ROWS, COLS);

    // обработка строк матрицы
    for (std::size_t i{}; i < ROWS; ++i) {

        double max_abs{ std::abs(matrix[i][0]) };

        std::size_t max_col{};

        int count_max{ 1 };

        // поиск максимального по модулю элемента
        for (std::size_t j{ 1 }; j < COLS; ++j) {

            double abs_val{ std::abs(matrix[i][j]) };

            if (abs_val > max_abs) {

                max_abs = abs_val;

                max_col = j;

                count_max = 1;
            }

            else if (abs_val == max_abs) {

                ++count_max;
            }
        }

        // обмен элементов
        if (count_max == 1 && max_col != 0) {

            std::swap(matrix[i][0], matrix[i][max_col]);
        }
    }

    std::cout << "\nМатрица после обработки:\n";

    printMatrix(matrix, ROWS, COLS);

    deleteMatrix(matrix, ROWS);
}

// задача 4
void task4() {

    std::cout << "\nЗАДАЧА 4: сумма справа от побочной диагонали\n";

    const std::size_t SIZE{ 6 };

    double** matrix{ createMatrix(SIZE, SIZE) };

    fillMatrix(matrix, SIZE, SIZE, -20.0, 20.0);

    std::cout << "Квадратная матрица:\n";

    printMatrix(matrix, SIZE, SIZE);

    double sum{ 0.0 };

    // поиск суммы элементов
    for (std::size_t i{}; i < SIZE; ++i) {

        for (std::size_t j{}; j < SIZE; ++j) {

            if (j > SIZE - 1 - i) {

                sum += matrix[i][j];
            }
        }
    }

    std::cout << "\nСумма элементов: "
        << std::fixed
        << std::setprecision(2)
        << sum << "\n";

    deleteMatrix(matrix, SIZE);
}

// задача 5
void task5() {

    std::cout << "\nЗАДАЧА 5: анализ успеваемости групп\n";

    const std::size_t GROUPS{ 3 };
    const std::size_t STUDENTS{ 25 };
    const std::size_t EXAMS{ 4 };

    // создание трехмерного массива
    int*** results{
        createArray3D(GROUPS, STUDENTS, EXAMS)
    };

    // заполнение оценками
    fillArray3D(results,
        GROUPS,
        STUDENTS,
        EXAMS,
        1,
        4);

    std::cout << "Групп | Студентов | Средний балл\n";

    double max_avg{ 0.0 };

    std::size_t best_group{};

    // анализ результатов
    for (std::size_t g{}; g < GROUPS; ++g) {

        double sum{ 0.0 };

        int count{};

        for (std::size_t s{}; s < STUDENTS; ++s) {

            for (std::size_t e{}; e < EXAMS; ++e) {

                int grade{ results[g][s][e] };

                if (grade > 1) {

                    sum += grade;

                    ++count;
                }
            }
        }

        double avg{
            count > 0 ? sum / count : 0.0
        };

        std::cout << "  "
            << (g + 1)
            << "   |    "
            << STUDENTS
            << "    | "
            << std::fixed
            << std::setprecision(2)
            << avg << "\n";

        // поиск лучшей группы
        if (avg > max_avg) {

            max_avg = avg;

            best_group = g + 1;
        }
    }

    std::cout << "\nЛучше всех подготовилась группа "
        << best_group
        << " со средним баллом "
        << max_avg << "\n";

    deleteArray3D(results, GROUPS, STUDENTS);
}

// главная функция
int main() {

    setlocale(LC_ALL, "rus");

    std::cout << "Решение задач\n";

    // меню программы
    while (true) {

        std::cout << "\nВыберите задачу:\n";

        std::cout << "1 - Вставка 0 в середину массива\n";
        std::cout << "2 - Сортировка массива\n";
        std::cout << "3 - Обмен элементов матрицы\n";
        std::cout << "4 - Сумма элементов матрицы\n";
        std::cout << "5 - Анализ успеваемости\n";
        std::cout << "0 - Выход\n";
        std::cout << "> ";

        int choice{};

        std::cin >> choice;

        // проверка ввода
        if (!std::cin) {

            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');

            std::cout
                << "Некорректный ввод. Попробуйте снова.\n";

            continue;
        }

        // выбор задачи
        switch (choice) {

        case 1:
            task1();
            break;

        case 2:
            task2();
            break;

        case 3:
            task3();
            break;

        case 4:
            task4();
            break;

        case 5:
            task5();
            break;

        case 0:

            std::cout << "Выход из программы.\n";

            return 0;

        default:

            std::cout
                << "Неверный номер задачи. Попробуйте снова.\n";
        }
    }

    return 0;
}