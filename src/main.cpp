#include <iostream>
#include <vector>
#include <memory>
#ifdef _WIN32
#include <clocale>
#endif
#include "buildings.hpp"

// Функция для проверки и обработки заводов
void processFactory(const std::unique_ptr<buildings::Building>& building) {
    // Пытаемся преобразовать указатель на Building к указателю на Factory
    buildings::Factory* factory = dynamic_cast<buildings::Factory*>(building.get());

    if (factory != nullptr) {
        // Успешное преобразование - это действительно Factory
        std::cout << "=== ОБРАБОТКА ЗАВОДА ===" << std::endl;
        std::cout << "Название завода: " << factory->getName() << std::endl;
        std::cout << "======================" << std::endl << std::endl;
    }
}
// Функция подсчёта типов
template<typename T>
int countBuildingType(const std::vector<std::unique_ptr<buildings::Building>>& buildings) {
    int count = 0;
    for (const auto& building : buildings) {
        if (dynamic_cast<T*>(building.get()) != nullptr) {
            count++;
        }
    }
    return count;
}

int main() {
    #ifdef _WIN32
    setlocale(LC_ALL, "ru_RU.UTF-8");
    #endif

    // Создаём объекты разных типов
    std::vector<std::unique_ptr<buildings::Building>> array;

    array.push_back(std::make_unique<buildings::House>("Гигахрущ", 200, 10));
    array.push_back(std::make_unique<buildings::Factory>("Пивзавод \"Читинские Ключи\"", 100, 90));
    array.push_back(std::make_unique<buildings::Warehouse>("Склад пива", 1, 10000));
    array.push_back(std::make_unique<buildings::Factory>("Металлургический завод", 50, 200));

    // Вызываются версии методов соответствующих реальному типу объекта
    for (const auto& b : array) {
        b->info();
        std::cout << "Стоимость обслуживания: " << b->getMaintenanceCost() << std::endl;

        // Используем dynamic_cast для проверки типа
        processFactory(b);

        std::cout << std::endl;
    }

    // Используем dynamic_cast для подсчета типов зданий
    std::cout << "=== СТАТИСТИКА ===" << std::endl;
    std::cout << "Всего зданий: " << array.size() << std::endl;
    std::cout << "Жилых домов: " << countBuildingType<buildings::House>(array) << std::endl;
    std::cout << "Заводов: " << countBuildingType<buildings::Factory>(array) << std::endl;
    std::cout << "Складов: " << countBuildingType<buildings::Warehouse>(array) << std::endl;

    std::cout << "\n=== ОБРАБОТКА СКЛАДОВ ===" << std::endl;
    for (const auto& b : array) {
        buildings::Warehouse* warehouse = dynamic_cast<buildings::Warehouse*>(b.get());
        if (warehouse != nullptr) {
            std::cout << "Склад обнаружен: " << warehouse->getName() << std::endl;
        }
    }

    return 0;
}
