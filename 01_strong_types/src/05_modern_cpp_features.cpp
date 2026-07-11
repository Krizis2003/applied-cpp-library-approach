#include <iostream>

/*
 * Цикл статей: "C++: Техники за пределами прикладного минимума"
 * Часть 1: Сильные типы
 * 
 * Пример 05: Современные возможности (C++11..C++23)
 * Пользовательские литералы (UDL)
 */

namespace modern_cpp {

    struct Meters {
        double value;
        explicit constexpr Meters(double v) : value(v) {}
    };

    // [Определяемые пользователем литералы]
    // Снимают синтаксический шум, сохраняя наглядность примитивов
    constexpr Meters operator""_m(long double x) {
        return Meters{static_cast<double>(x)};
    }

    constexpr Meters operator""_m(unsigned long long x) {
        return Meters{static_cast<double>(x)};
    }

    void run() {
        Meters d = 10.5_m;
        Meters d2 = 100_m;
        std::cout << "[05] UDL works: " << d.value << " m, " << d2.value << " m\n";
    }

} // namespace modern_cpp

int main() {
    modern_cpp::run();
    return 0;
}
