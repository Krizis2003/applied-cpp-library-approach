#include <iostream>
#include <cassert>

namespace logic_and_price {

    // [1. Защита логики взаимодействия]
    struct Meters {
        double value;
        explicit constexpr Meters(double v) : value(v) {}
        explicit constexpr operator double() const { return value; }

        // Разрешаем только те действия, которые имеют смысл для этой сущности:
        constexpr Meters operator+(Meters other) const { return Meters{value + other.value}; }
        constexpr Meters operator-(Meters other) const { return Meters{value - other.value}; }
    };

    // Однако ручное описание таких правил требует времени (рутина):
    struct Kilograms {
        double v;
        Kilograms operator+(Kilograms o) const { return {v + o.v}; }
        bool operator==(Kilograms o) const { return v == o.v; }
        // ... и ещё 5-6 подобных операторов для каждой сущности
    };

    void run() {
        Meters m1{10.0}, m2{5.0};
        auto total = m1 + m2;
        // m1 + 5.0; // ОШИБКА: нет неявного приведения

        std::cout << "[02] Logic protection (Meters): " << static_cast<double>(total) << "\n";
        assert(static_cast<double>(total) == 15.0);
    }

} // namespace logic_and_price

int main() {
    logic_and_price::run();
}
