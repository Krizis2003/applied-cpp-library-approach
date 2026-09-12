#pragma once

#include <compare>
#include <functional>
#include <utility>

// ============================================================================
// C++: Техники за пределами прикладного минимума. Часть 1. Сильные типы
// Шаблонная обёртка TypeWrapper<T, Tag>
// ============================================================================

/**
 * @brief Обобщённая обёртка над базовым типом T с фантомным типом-тегом Tag.
 * 
 * Позволяет создавать строго типизированные сущности с нулевыми накладными
 * расходами в рантайме (Zero-Cost Abstraction).
 */
template <typename T, typename Tag>
struct TypeWrapper {
    using value_type = T;
    using tag_type   = Tag;

    T value;

    // Конструктор намеренно explicit, чтобы запретить неявную инициализацию из сырых значений
    explicit constexpr TypeWrapper(T v) : value(std::move(v)) {}

    // Явное приведение обратно к базовому типу
    explicit constexpr operator T() const { return value; }

    // C++20: автоматически генерирует все 6 операторов сравнения (==, !=, <, <=, >, >=)
    auto operator<=>(const TypeWrapper&) const = default;
};

// Подключение к стандартной библиотеке (STL) через специализацию std::hash
namespace std {
    template <typename T, typename Tag>
    struct hash<TypeWrapper<T, Tag>> {
        std::size_t operator()(const TypeWrapper<T, Tag>& wrapper) const noexcept(noexcept(std::hash<T>{}(wrapper.value))) {
            return std::hash<T>{}(wrapper.value);
        }
    };
}
