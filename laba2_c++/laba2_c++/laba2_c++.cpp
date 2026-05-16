#include <cmath> // для математических функций
#include <expected> // для std::expected и std::unexpected
#include <format> // для форматированного вывода std::format
#include <iostream> // для cout, cin, cerr
#include <limits> // для numeric_limits
#include <string> // для std::string

// структура для хранения коэффициентов уравнения
struct Coefficients {

    // коэффициент a
    double a{};

    // коэффициент b
    double b{};

    // коэффициент c
    double c{};
};

// функция ввода коэффициентов
std::expected<Coefficients, std::string> getCoefficients() {

    // приглашение ко вводу коэффициентов
    std::cout << "Введите a, b, c (через пробел, a != 0): ";

    // структура для хранения введенных значений
    Coefficients vals{};

    // попытка считать три числа
    if (!(std::cin >> vals.a >> vals.b >> vals.c)) {

        // проверка завершения ввода
        if (std::cin.eof())
            return std::unexpected("Ввод завершен (EOF)");

        // очистка состояния потока
        std::cin.clear();

        // очистка буфера ввода
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // возврат сообщения об ошибке
        return std::unexpected("Ожидается три числа через пробел");
    }

    // проверка коэффициента a
    if (vals.a == 0.0) {
        return std::unexpected("Коэффициент a не может быть равен нулю");
    }

    // возврат корректных коэффициентов
    return vals;
}

int main() {

    // подключение русской локализации
    setlocale(LC_ALL, "rus");

    // бесконечный цикл
    while (true) {

        // вызов функции получения коэффициентов
        auto res{ getCoefficients() };

        // проверка успешности ввода
        if (!res) {

            // вывод сообщения об ошибке
            std::cerr << std::format("Ошибка: {}\n", res.error());

            // если ввод завершен через EOF — завершить программу
            if (res.error() == "Ввод завершен (EOF)") {
                return 1;
            }

            // переход к следующей итерации цикла
            continue;
        }

        // распаковка коэффициентов
        auto [a, b, c] {*res};

        // вычисление k
        double k{ a + b };

        // предполагаем наличие вещественных корней
        bool hasRealRoots{ true };

        // проверка отсутствия решений
        if (k == 0.0 && c != 0.0) {
            hasRealRoots = false;
        }

        // вывод результата проверки
        std::cout << (hasRealRoots
            ? "Уравнение имеет вещественные корни\n"
            : "Уравнение не имеет вещественных корней\n");

        // если k не равно нулю
        if (k != 0.0) {

            // вывод найденного корня
            std::cout << std::format("x = {:.4f}\n", -c / k);
        }

        // если любое x является решением
        else if (c == 0.0) {

            // вывод сообщения
            std::cout << "Любое x является решением\n";
        }

        // завершение программы после успешного ввода
        break;
    }

    // успешное завершение программы
    return 0;
}