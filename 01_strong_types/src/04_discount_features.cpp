#include <iostream>
#include <cassert>
#include <cmath>

namespace discount_features {

    struct Price   { double value; };
    struct Percent { double value; };
    struct Rubles  { double value; };

    // Разграничиваем логику скидок на уровне типов:
    Price discount(Price p, Percent pct) {
        return Price{p.value * (1.0 - pct.value / 100.0)};
    }

    Price discount(Price p, Rubles off) {
        return Price{p.value - off.value};
    }

    // Гибкий порядок параметров:
    Price discount(Rubles off, Price p) {
        return discount(p, off);
    }

    void run() {
        Price p{ 1000.0 };

        // Использование перегрузки (1)
        auto p1 = discount(p, Percent{ 10.0 });
        auto p2 = discount(p, Rubles{ 150.0 });

        // Использование гибкого порядка (2)
        auto p3 = discount(Rubles{ 150.0 }, p);

        std::cout << "[04] Percent discount: " << p1.value << "\n";
        std::cout << "[04] Rubles discount: " << p2.value << "\n";
        std::cout << "[04] Flexible order: " << p3.value << "\n";

        assert(std::abs(p1.value - 900.0) < 1e-10);
        assert(std::abs(p2.value - 850.0) < 1e-10);
        assert(std::abs(p3.value - 850.0) < 1e-10);
    }

} // namespace discount_features

int main() {
    discount_features::run();
}
