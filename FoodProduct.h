#ifndef FOODPRODUCT_H
#define FOODPRODUCT_H

#include <string>
#include <iostream>
#include <stdexcept>

class FoodProduct {
private:
    std::string name;
    double protein;      // на 100г
    double carbs;        // на 100г
    double fats;         // на 100г
    double calories;     // изчислява се автоматично на 100г

    void calculateCalories() {
        // 1g Protein = 4 kcal, 1g Carbs = 4 kcal, 1g Fat = 9 kcal
        calories = (protein * 4) + (carbs * 4) + (fats * 9);
    }

public:
    // Конструктор
    FoodProduct(std::string name, double protein, double carbs, double fats) {
        if (name == "") throw std::invalid_argument("Product name cannot be empty.");
        if (protein < 0 || carbs < 0 || fats < 0) {
            throw std::invalid_argument("Macros cannot be negative numbers.");
        }

        this->name = name;
        this->protein = protein;
        this->carbs = carbs;
        this->fats = fats;
        calculateCalories();
    }

    // Гетъри
    std::string getName() const { return name; }
    double getProtein() const { return protein; }
    double getCarbs() const { return carbs; }
    double getFats() const { return fats; }
    double getCalories() const { return calories; }

    void displayProduct() const {
        std::cout << "Food Product: " << name << std::endl;
        std::cout << "Protein: " << protein << " g/100g" << std::endl;
        std::cout << "Carbs: " << carbs << " g/100g" << std::endl;
        std::cout << "Fats: " << fats << " g/100g" << std::endl;
        std::cout << "Calories: " << calories << " kcal/100g" << std::endl;
    }
};

#endif