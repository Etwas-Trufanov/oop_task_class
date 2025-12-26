#pragma once

#include <iostream>
#include <sstream>
#include <string>

namespace buildings {

    // базовый класс здания
    class Building {
    protected:
        std::string name;   // название здания
        int floors;    // количество этажей

    public:
        // Конструктор
        // Добавить проверки
        Building(const std::string& name, int floors)
            : name(name), floors(floors) {}

        // Виртуальный деструктор, автоматически генерируется компилятором
        virtual ~Building() = default;

        // Виртуальный метод, который будет переопределяться в потомках
        virtual void info() const {
            std::cout << "Здание: " << name
                 << ", этажей: " << floors << std::endl;
        }

        virtual std::string str_info() const {
            std::stringstream a;
            a << "Здание: " << name
            << ", этажей: " << floors << std::endl;
            return a.str();
        }

        // Ещё один виртуальный метод
        virtual double getMaintenanceCost() const {
            return floors * 1000.0; // базовая стоимость обслуживания
        }

        // Геттер имени
        std::string getName() const { return name; }
    };

    // Наследник класс "Жилой дом"
    class House : public Building {
    private:
        int apartments; // количество квартир

    public:
        House(const std::string& name, int floors, int apartments)
            : Building(name, floors), apartments(apartments) {}

        // Переопределение метода info()
        // Это переопределение, для доступа к базовому методу нужно разрешить область вызова
        void info() const override {
            std::cout << "Жилой дом: " << name
                 << ", этажей: " << floors
                 << ", квартир: " << apartments << std::endl;
        }

        std::string str_info() const override {
            std::stringstream a;
            a << "Жилой дом: " << name
            << ", этажей: " << floors
            << ", квартир: " << apartments << std::endl;
            return a.str();
        }

        // Переопределение стоимости обслуживания
        double getMaintenanceCost() const override {
            return floors * 1200.0 + apartments * 100.0;
        }

    };

    // Производный класс "Завод"
    class Factory : public Building {
    private:
        int workers; // количество рабочих

    public:
        Factory(const std::string& name, int floors, int workers)
            : Building(name, floors), workers(workers) {}

        // Переопределённый метод информации
        void info() const override {
            std::cout << "Завод: " << name
                 << ", этажей: " << floors
                 << ", рабочих: " << workers << std::endl;
        }

        std::string str_info() const override {
            std::stringstream a;
            a << "Завод: " << name
            << ", этажей: " << floors
            << ", рабочих: " << workers << std::endl;
            return a.str();
        }

        // Переопределённый метод получения стоимости
        double getMaintenanceCost() const override {
            return floors * 2000.0 + workers * 50.0;
        }

        // Метод увольнения всех работяг
        void fireAllWorkers() {
            workers = 0;
        }
    };

    // Производный класс "Склад"
    class Warehouse : public Building {
    private:
        double area; // площадь в квадратных метрах

    public:
        Warehouse(const std::string& name, int floors, double area)
            : Building(name, floors), area(area) {}

        // Переопределённый метод информации
        void info() const override {
            std::cout << "Склад: " << name
                      << ", этажей: " << floors
                      << ", площадь: " << area << " м^2" << std::endl;
        }

        std::string str_info() const override {
            std::stringstream a;
            a << "Склад: " << name
            << ", этажей: " << floors
            << ", площадь: " << area << " м^2" << std::endl;
            return a.str();
        }

        // Переопределённый метод получения стоимости
        double getMaintenanceCost() const override {
            return floors * 1500.0 + area * 10.0;
        }

    };

}
