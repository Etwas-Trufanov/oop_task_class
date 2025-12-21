#include <clocale>
#include <iostream>
#include <vector>
#include <memory>
#include "buildings.hpp"

int main() {
    #ifdef _WIN32
    setlocale(LC_ALL, "ru_RU.UTF-8");
    #endif
    // Создаём объекты разных типов
    std::vector<std::unique_ptr<buildings::Building>> array;

    array.push_back(std::make_unique<buildings::House>("Гигахрущ", 99999, 10));
    array.push_back(std::make_unique<buildings::Factory>("Пивзавод \"Читинские Ключи\"", 99999, 10));
    array.push_back(std::make_unique<buildings::House>("Гигахрущ", 99999, 10));

    // ===== Пример полиморфизма =====
    // Вызываются версии методов соответствующих реальному типу объекта
    for (const auto& b : array) {
            b->info();
            std::cout << "Стоимость обслуживания: " << b->getMaintenanceCost() << std::endl << std::endl;
        }

    return 0;
}
