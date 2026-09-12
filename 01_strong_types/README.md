# Часть 1. Сильные типы

Примеры кода к первой части цикла статей на Хабре: сильные типы, шаблонный `TypeWrapper`, пользовательские литералы (UDL) и альтернативные решения (Parameter Object, `enum class`).

## Структура каталога

- `include/type_wrapper.hpp` — компактная заголовочная реализация `TypeWrapper<T, Tag>` с поддержкой C++20 `operator<=>` и `std::hash`.
- `src/demo.cpp` — главное сквозное демо («До и После»):
  1. Primitive Obsession и ловушка неявного приведения (`silent overload hijacking`).
  2. Защищённый API на `TypeWrapper` и пользовательские литералы (`_m`, `_s`).
  3. Разграничение систем координат (`ScreenRect` vs `ClientRect`) и совместимость с STL (`std::unordered_set`).
- `src/alternatives.cpp` — разбор альтернативных подходов:
  1. Parameter Object и Designated Initializers (C++20) для конфигураций.
  2. `enum class` как легковесный сильный тип и границы его применимости.

## Сборка и запуск

Сборка из текущего каталога:

```bash
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Для Visual Studio:
```powershell
cmake -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```
