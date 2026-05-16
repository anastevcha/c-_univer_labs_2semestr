#include <expected> // для std::expected и std::unexpected
#include <format> // для форматированного вывода std::format
#include <iostream> // для cout, cin, cerr
#include <limits> // для numeric_limits
#include <string> // для std::string

// константа тарифа за 1 кВт
constexpr double TARIFF{ 3.0 };

// функция получает количество кВт от пользователя
// expected хранит либо double (успешный результат),
// либо string (текст ошибки)
std::expected<double, std::string> getEnergy() {

    // вывод приглашения ко вводу
    std::cout << "Введите количество кВт: ";

    // переменная для хранения введенного значения
    double value{};

    // проверяем успешность ввода числа
    if (!(std::cin >> value)) {

        // проверяем, не был ли завершен ввод (EOF)
        if (std::cin.eof())

            // возвращаем ошибку через unexpected
            return std::unexpected("Ввод заверешен");

        // очищаем состояние ошибки потока
        std::cin.clear();

        // удаляем неправильный ввод из буфера
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // возвращаем сообщение об ошибке
        return std::unexpected("Введите корректное число");
    }

    // проверяем, не отрицательное ли число
    if (value < 0.0) {

        // возвращаем ошибку, если значение меньше нуля
        return std::unexpected("Значение не может быть отрицательным");
    }

    // если ошибок нет - возвращаем введенное значение
    return value;
}

int main() {

    // вызов функции для отображения кириллицы  
    setlocale(LC_ALL, "rus");

    // вывод информации о тарифе
    std::cout << std::format(
        "Стоимость электроэнергии (тариф: {:.2f} Р/кВт * ч)\n\n", TARIFF);

    // бесконечный цикл программы
    while (1) {

        // вызываем функцию получения данных
        auto result{ getEnergy() };

        // проверяем, есть ли успешный результат
        if (result) {

            // вычисляем итоговую стоимость
            double total{ *result * TARIFF };

            // выводим сумму к оплате
            std::cout << std::format("К оплате: {:.2f} Р\n", total);

            // выходим из цикла после успешного ввода
            break;
        }

        // выводим текст ошибки
        std::cerr << std::format("Ошибка: {}\n", result.error());
    }

    // успешное завершение программы
    return 0;
}