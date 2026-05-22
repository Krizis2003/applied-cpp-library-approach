#include <iostream>
#include <cassert>

namespace parameter_object {

    // Паттерн Parameter Object через агрегат C++20
    struct SpeedParams {
        double distance;
        double time;
    };

    double speed(SpeedParams p) {
        return p.distance / p.time;
    }

    void run() {
        // Designated init (C++20): наглядно и безопасно на границе вызова
        auto v = speed({.distance = 100.0, .time = 5.0});
        
        std::cout << "[06] Speed from Parameter Object: " << v << "\n";
        assert(v == 20.0);

        // Ограничение: внутри функции p.distance и p.time - это обычные double.
        // Мы все еще можем ошибиться в реализации: return p.time / p.distance;
        // Сильные типы в этом плане дают более глубокую защиту.
    }

} // namespace parameter_object

int main() {
    parameter_object::run();
}
