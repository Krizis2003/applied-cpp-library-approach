#include <iostream>

/*
 * Цикл статей: "C++: Техники за пределами прикладного минимума"
 * Часть 1: Сильные типы
 * 
 * Пример 01: Эволюция контроля параметров.
 * 
 * Проблема: double — тип «анонимный». Смысл данных (расстояние/время) 
 * остается слепой зоной для компилятора, что ведет к опечаткам в аргументах.
 */

// --- СТАРОЕ API ---
// Параметры неразличимы для компилятора. Легко перепутать порядок.
constexpr double speed(double distance, double time) {
    return distance / time;
}

// --- НОВОЕ API (Strong Types) ---
struct Meters {
    double value;
};

struct Seconds {
    double value;
};

// Теперь типы несут смысл. Порядок аргументов защищен на уровне компиляции.
[[nodiscard]] constexpr double speed(Meters d, Seconds t) {
    return d.value / t.value;
}

// --- ОТРИЦАТЕЛЬНЫЙ ПРИМЕР (Иллюзорная защита) ---
// Если мы добавим неявное приведение, защита исчезнет при наличии старого API.
struct MetersImplicit {
    double value;
    constexpr operator double() const { return value; } 
};

struct SecondsImplicit {
    double value;
    constexpr operator double() const { return value; } 
};

[[nodiscard]] constexpr double speed(MetersImplicit d, SecondsImplicit t) {
    return d.value / t.value;
}

int main() {
    // 1. Проблема: Primitive Obsession
    double distance = 100.0;
    double time = 5.0;
    
    // ОШИБКА ЛОГИКИ: перепутали порядок, но код компилируется (старое API).
    auto v1 = speed(time, distance); 
    std::cout << "Raw speed (error): " << v1 << " units/s\n";

    // 2. Решение: Strong Types
    // speed(Seconds{5.0}, Meters{100.0}); // ОШИБКА КОМПИЛЯЦИИ
    auto v2 = speed(Meters{100.0}, Seconds{5.0}); // OK
    std::cout << "Fixed speed: " << v2 << " m/s\n";

    // 3. Отрицательный пример: Иллюзорная защита
    MetersImplicit mi{100.0};
    SecondsImplicit si{5.0};
    
    // ОШИБКА: Перепутали порядок. Из-за неявного приведения компилятор
    // просто вызовет speed(double, double). Ошибки сборки НЕ БУДЕТ.
    auto v3 = speed(si, mi); 
    std::cout << "Phantom protection speed (error): " << v3 << " units/s\n";

    return 0;
}
