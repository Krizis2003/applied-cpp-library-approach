# C++: Техники за пределами прикладного минимума

Код к циклу статей на Хабре, посвящённых практическим техникам C++ (сильные типы, tag dispatching, type traits и др.).

## Содержание серии

- **Часть 1. Сильные типы** — каталог [`01_strong_types`](./01_strong_types) ([статья на Хабре](https://habr.com/ru/...))

## Сборка и запуск

Для сборки всех примеров требуется компилятор с поддержкой C++20 и CMake 3.15+:

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

## Лицензия

MIT (см. [LICENSE](./LICENSE)).
