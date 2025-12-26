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

    // Ччуть про запись в массив разных классов, про полиморфизм
    array.push_back(std::make_unique<buildings::House>("Гигахрущ", 200, 10));
    array.push_back(std::make_unique<buildings::Factory>("Яндекс AI", 100, 90));
    array.push_back(std::make_unique<buildings::Warehouse>("Склад DDR5", 1, 10000));
    array.push_back(std::make_unique<buildings::Factory>("Бобровый завод", 50, 200));
    array.push_back(std::make_unique<buildings::Warehouse>("Склад бобров", 3, 10000));
    array.push_back(std::make_unique<buildings::Warehouse>("Склад старых маков", 1, 10000));
    array.push_back(std::make_unique<buildings::Warehouse>("Склад кваса", 10, 10));

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
        // Получаем указатель на склад
        buildings::Warehouse* warehouse = dynamic_cast<buildings::Warehouse*>(b.get());
        if (warehouse != nullptr) {
            // Выводим то что в векторе нашли склад
            std::cout << "Склад обнаружен: " << warehouse->getName() << std::endl;
        }
    }

    // Увольняем всех с завода
    try {
        std::cout << "\n=== Повышаем безработицу ===\n";
        buildings::Factory *factory = dynamic_cast<buildings::Factory*>(array[3].get());
        if (factory != nullptr) {
            factory->fireAllWorkers();
            std::cout << "Работяги с завода " << factory->getName() << " уволены! :3\n";
        } else {
            // dynamic_cast при невозможности привести тип просто возвращает nullptr
            throw std::runtime_error("Здание по индексу 3 не является заводом");
        }
    } catch (std::runtime_error &e) {
        std::cerr << "Произошла ошибка в увольнении работяг: " << e.what() << std::endl;
    }

    buildings::House *house = dynamic_cast<buildings::House*>(array[0].get());
    std::cout << "Выводим метод str_info жилого дома:" << house->str_info() << std::endl;
    std::cout << "Выводим метод str_info базового здания:" << house->Building::str_info();

    return 0;
}
