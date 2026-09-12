#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "type_wrapper.hpp"

// ============================================================================
// Часть 1. Сильные типы
// Главное сквозное демо: от проблемы к решению через TypeWrapper
// ============================================================================

// ----------------------------------------------------------------------------
// 1. Проблема: Primitive Obsession и ловушка неявного приведения
// ----------------------------------------------------------------------------
namespace problem_demonstration {

    // Старый API: сырые числа double
    constexpr double speed(double distance, double time) {
        return distance / time;
    }

    // Попытка ввести обёртки, но с опасным неявным приведением (operator double)
    struct MetersImplicit {
        double value;
        constexpr operator double() const { return value; }
    };

    struct SecondsImplicit {
        double value;
        constexpr operator double() const { return value; }
    };

    // Перегруженный API: принимает обёртки
    constexpr double speed(MetersImplicit d, SecondsImplicit t) {
        return d.value / t.value;
    }

    void run() {
        std::cout << "--- 1. Primitive Obsession & Ловушка неявных приведений ---\n";

        double distance = 100.0;
        double time = 5.0;

        // Баг 1: перепутан порядок аргументов, компилятор молчит
        auto v1 = speed(time, distance);
        std::cout << "speed(time, distance) [тихий баг]: " << v1 << " (ожидалось 20)\n";
        assert(v1 == 0.05);

        // Баг 2: ловушка неявного приведения при наличии старой перегрузки
        MetersImplicit m{100.0};
        SecondsImplicit s{5.0};

        // Корректный вызов новой функции:
        assert(speed(m, s) == 20.0);

        // Перепутали аргументы: компилятор не выдаёт ошибку, а молча откатывается
        // к старому speed(double, double), неявно распаковывая оба типа!
        auto silent_bug = speed(s, m);
        std::cout << "speed(SecondsImplicit, MetersImplicit) [silent overload hijacking]: " 
                  << silent_bug << "\n\n";
        assert(silent_bug == 0.05);
    }

} // namespace problem_demonstration

// ----------------------------------------------------------------------------
// 2. Решение: TypeWrapper, теги и пользовательские литералы (UDL)
// ----------------------------------------------------------------------------
namespace solution_demonstration {

    // Фантомные типы-теги (Phantom Types):
    struct MetersTag {};
    struct SecondsTag {};

    using Meters  = TypeWrapper<double, MetersTag>;
    using Seconds = TypeWrapper<double, SecondsTag>;

    // Новый API: надёжно защищён на уровне типов
    constexpr double speed(Meters d, Seconds t) {
        return d.value / t.value;
    }

    // Пользовательские литералы (UDL) для максимального удобства на месте вызова:
    constexpr Meters operator""_m(long double x) {
        return Meters{static_cast<double>(x)};
    }
    constexpr Seconds operator""_s(long double x) {
        return Seconds{static_cast<double>(x)};
    }
    constexpr Meters operator""_m(unsigned long long x) {
        return Meters{static_cast<double>(x)};
    }
    constexpr Seconds operator""_s(unsigned long long x) {
        return Seconds{static_cast<double>(x)};
    }

    void run() {
        std::cout << "--- 2. Решение: TypeWrapper и пользовательские литералы ---\n";

        // Корректный типизированный вызов:
        auto v1 = speed(Meters{100.0}, Seconds{5.0});
        std::cout << "speed(Meters{100}, Seconds{5}): " << v1 << " m/s\n";
        assert(v1 == 20.0);

        // Лаконичный вызов через UDL:
        auto v2 = speed(100_m, 5_s);
        std::cout << "speed(100_m, 5_s) [через литералы]: " << v2 << " m/s\n";
        assert(v2 == 20.0);

        // Ошибки компиляции, которые теперь надёжно страхуют разработчика:
        // speed(5_s, 100_m);          // Ошибка: несовпадение типов параметров
        // speed(100.0, 5.0);          // Ошибка: неявная упаковка запрещена (explicit constructor)
        // speed_legacy(100_m, 5_s);   // Ошибка: неявная распаковка запрещена (explicit operator T)

        // C++20: оператор <=> работает из коробки для TypeWrapper:
        Meters m1{100.0}, m2{200.0};
        assert(m1 < m2);
        assert(m1 != m2);
        std::cout << "Spaceship operator: " << m1.value << " < " << m2.value << " (OK)\n\n";
    }

} // namespace solution_demonstration

// ----------------------------------------------------------------------------
// 3. Практика: Разграничение систем координат и интеграция с STL
// ----------------------------------------------------------------------------
namespace coordinates_and_stl {

    struct Rect {
        int x, y, width, height;
        auto operator<=>(const Rect&) const = default;
    };

    struct ScreenCoordsTag {};
    struct ClientCoordsTag {};

    using ScreenRect = TypeWrapper<Rect, ScreenCoordsTag>;
    using ClientRect = TypeWrapper<Rect, ClientCoordsTag>;

    void render_popup_menu(ScreenRect coords) {
        std::cout << "Render menu at screen coords: (" << coords.value.x << ", " << coords.value.y << ")\n";
    }

    void run() {
        std::cout << "--- 3. Практика: Системы координат и STL ---\n";

        ScreenRect screen_pos{Rect{100, 200, 400, 300}};
        ClientRect client_pos{Rect{10, 20, 400, 300}};

        render_popup_menu(screen_pos);
        // render_popup_menu(client_pos); // Ошибка компиляции: несовместимые системы координат!

        // Интеграция с STL: использование TypeWrapper в std::unordered_set
        using namespace solution_demonstration;
        std::unordered_set<Meters> unique_measurements;
        unique_measurements.insert(100_m);
        unique_measurements.insert(200_m);
        unique_measurements.insert(100_m); // Дубликат
        assert(unique_measurements.size() == 2);
        std::cout << "std::unordered_set<Meters> успешно использует std::hash: " 
                  << unique_measurements.size() << " уникальных значения.\n\n";
    }

} // namespace coordinates_and_stl

int main() {
    std::cout << "============================================================\n";
    std::cout << "C++: Сильные типы. Главное сквозное демо (Before & After)\n";
    std::cout << "============================================================\n\n";

    problem_demonstration::run();
    solution_demonstration::run();
    coordinates_and_stl::run();

    std::cout << "Все проверки успешно пройдены!\n";
    return 0;
}
