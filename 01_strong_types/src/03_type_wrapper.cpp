#include <iostream>
#include <functional>

/*
 * Цикл статей: "C++: Техники за пределами прикладного минимума"
 * Часть 1: Сильные типы
 * 
 * Пример 03: TypeWrapper - универсальный каркас для сильных типов.
 * 
 * Мы создаем шаблон, который позволяет штамповать сильные типы,
 * не дублируя код операторов вручную.
 */

template <typename T, typename Tag>
struct TypeWrapper {
    T value;

    explicit constexpr TypeWrapper(T v) : value(v) {}
    
    // Явное приведение обратно к базовому типу
    explicit constexpr operator T() const { return value; }
};

// Создание типов через пустые структуры-теги
struct MetersTag {};
using Meters = TypeWrapper<double, MetersTag>;

struct SecondsTag {};
using Seconds = TypeWrapper<double, SecondsTag>;

// Специализация std::hash для бесшовной интеграции в контейнеры
namespace std {
    template <typename T, typename Tag>
    struct hash<TypeWrapper<T, Tag>> {
        size_t operator()(const TypeWrapper<T, Tag>& w) const {
            return std::hash<T>{}(static_cast<T>(w));
        }
    };
}

int main() {
    Meters m{100.0};
    Seconds s{5.0};

    // Безопасное использование через статический каст
    double raw_m = static_cast<double>(m);
    
    std::cout << "Meters: " << raw_m << "\n";
    std::cout << "Hash of Meters: " << std::hash<Meters>{}(m) << "\n";

    return 0;
}
