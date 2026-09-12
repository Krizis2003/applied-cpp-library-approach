#include <iostream>
#include <cstdint>
#include <cassert>

// ============================================================================
// Часть 1. Сильные типы
// Альтернативные приёмы: Parameter Object и enum class
// ============================================================================

// ----------------------------------------------------------------------------
// 1. Parameter Object & Designated Initializers (C++20)
// Когда параметров много, но создавать десятки сильных типов избыточно.
// ----------------------------------------------------------------------------
namespace parameter_object_demo {

    struct WindowConfig {
        double x{0.0};
        double y{0.0};
        double width{800.0};
        double height{600.0};
        double opacity{1.0};
        bool visible{true};
    };

    void create_window(WindowConfig config) {
        assert(config.width > 0);
        assert(config.height > 0);
        assert(config.opacity >= 0.0 && config.opacity <= 1.0);

        std::cout << "Window created: (" << config.x << ", " << config.y << ") "
                  << config.width << "x" << config.height 
                  << ", opacity=" << config.opacity << "\n";
    }

    void run() {
        std::cout << "--- 1. Parameter Object (C++20 Designated Initializers) ---\n";

        // Имена полей явно указаны на месте вызова:
        create_window({
            .x = 100.0,
            .y = 150.0,
            .width = 1024.0,
            .height = 768.0,
            .opacity = 0.9
        });

        // create_window({ .height = 768.0, .width = 1024.0 }); 
        // Ошибка компиляции C++20: нарушен порядок полей при обозначенной инициализации!
        std::cout << "Designated initializers обеспечивают наглядность без введения новых типов.\n\n";
    }

} // namespace parameter_object_demo

// ----------------------------------------------------------------------------
// 2. enum class как сильный тип
// Сверхлёгкий способ создать различимый тип для целочисленных данных (ID, дескрипторы).
// ----------------------------------------------------------------------------
namespace enum_class_demo {

    // 1. Ограничение: базовым типом может быть только целочисленный тип
    // enum class FloatMeters : double {}; // Ошибка компиляции: double запрещён!
    enum class UserId     : std::uint64_t {};
    enum class DocumentId : std::uint64_t {};

    void grant_access(UserId user, DocumentId doc) {
        std::cout << "User " << static_cast<std::uint64_t>(user)
                  << " granted access to doc " << static_cast<std::uint64_t>(doc) << "\n";
    }

    // 2. Ограничение: для арифметики операторы приходится объявлять вручную
    enum class Meters : std::uint64_t {};
    constexpr Meters operator+(Meters lhs, Meters rhs) noexcept {
        return Meters{static_cast<std::uint64_t>(lhs) + static_cast<std::uint64_t>(rhs)};
    }

    void run() {
        std::cout << "--- 2. enum class как сильный тип ---\n";

        UserId user{42};
        DocumentId doc{1001};

        grant_access(user, doc);
        // grant_access(doc, user); // Ошибка компиляции: типы не совпадают!
        // grant_access(42, 1001);  // Ошибка компиляции: неявные приведения запрещены!

        Meters m1{100}, m2{50};
        Meters total = m1 + m2;
        assert(static_cast<std::uint64_t>(total) == 150);
        std::cout << "enum class арифметика через явный operator+: total = " 
                  << static_cast<std::uint64_t>(total) << "\n\n";
    }

} // namespace enum_class_demo

int main() {
    std::cout << "============================================================\n";
    std::cout << "C++: Альтернативы сильным типам и границы их применения\n";
    std::cout << "============================================================\n\n";

    parameter_object_demo::run();
    enum_class_demo::run();

    std::cout << "Все проверки альтернатив успешно пройдены!\n";
    return 0;
}
