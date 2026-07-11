#include <iostream>
#include <cassert>

namespace discount_features {

    struct Price   { double value; };
    struct Percent { double value; };
    struct Rubles  { double value; };

    // [2. Смысловая перегрузка интерфейсов]
    Price discount(Price p, Percent pct) {
        return Price{p.value * (1.0 - pct.value / 100.0)};
    }

    Price discount(Price p, Rubles off) {
        return Price{p.value - off.value};
    }

    // [3. Гибкий порядок параметров]
    Price discount(Rubles off, Price p) {
        return discount(p, off);
    }

    void run() {
        Price p{1000.0};
        auto p1 = discount(p, Percent{10.0});
        auto p2 = discount(Rubles{150.0}, p);

        std::cout << "[04] Semantic overloading and flexible order works.\n";
        assert(p1.value == 900.0);
        assert(p2.value == 850.0);
    }

} // namespace discount_features

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

namespace parameter_object {

    // [Явная инициализация агрегатов]
    struct SpeedParams {
        double distance;
        double time;
    };

    double speed(SpeedParams p) {
        // Ограничение: внутри всё еще сырые double (нет защиты логики)
        return p.distance / p.time;
    }

    void run() {
        // Такой синтаксис помогает не ошибиться при вызове функции
        auto v = speed({.distance = 100.0, .time = 5.0});
        std::cout << "[06] Parameter Object works: " << v << "\n";
    }

} // namespace parameter_object

int main() {
    discount_features::run();
    modern_cpp::run();
    parameter_object::run();
}
