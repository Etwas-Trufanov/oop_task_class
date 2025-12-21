#pragma once

#include <iostream>
#include <string>

namespace buildings {

    class Building {
    protected:
        std::string name;   // название здания
        int floors;    // количество этажей

    public:
        // Конструктор
        Building(const std::string& name, int floors)
            : name(name), floors(floors) {}

        // Виртуальный деструктор
        virtual ~Building() = default;

        // Виртуальный метод, который будет переопределяться в потомках
        virtual void info() const {
            std::cout << "Здание: " << name
                 << ", этажей: " << floors << std::endl;
        }

        // Ещё один виртуальный метод
        virtual double getMaintenanceCost() const {
            return floors * 1000.0; // базовая стоимость обслуживания
        }
    };

    // Производный класс "Жилой дом"
    class House : public Building {
    private:
        int apartments; // количество квартир

    public:
        House(const std::string& name, int floors, int apartments)
            : Building(name, floors), apartments(apartments) {}

        // Переопределение метода info()
        void info() const override {
            std::cout << "Жилой дом: " << name
                 << ", этажей: " << floors
                 << ", квартир: " << apartments << std::endl;
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

        void info() const override {
            std::cout << "Завод: " << name
                 << ", этажей: " << floors
                 << ", рабочих: " << workers << std::endl;
        }

        double getMaintenanceCost() const override {
            return floors * 2000.0 + workers * 50.0;
        }
    };

    // Производный класс "Склад"
    class Warehouse : public Building {
    private:
        double area; // площадь в квадратных метрах

    public:
        Warehouse(const std::string& name, int floors, double area)
            : Building(name, floors), area(area) {}

        void info() const override {
            std::cout << "Склад: " << name
                 << ", этажей: " << floors
                 << ", площадь: " << area << " м^2" << std::endl;
        }

        double getMaintenanceCost() const override {
            return floors * 1500.0 + area * 10.0;
        }
    };

}
