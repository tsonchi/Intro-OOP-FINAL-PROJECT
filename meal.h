#ifndef MEAL_H
#define MEAL_H

#include "FoodProduct.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

class Meal {
private:
    std::string mealName;
    std::vector<std::pair<FoodProductSnapshot, double>> eatenProducts;

public:
    Meal(std::string name) {
        if (name == "") throw std::invalid_argument("Meal name cannot be empty.");
        this->mealName = name;
    }

    void addProduct(const FoodProduct& product, double grams) {
        if (grams <= 0) throw std::invalid_argument("Grams must be a positive number.");
        eatenProducts.push_back({product, grams});
    }

    double getTotalCalories() const {
        double total = 0;
        for (const auto& pair : eatenProducts) {
            total += (pair.first.getCalories() / 100.0) * pair.second;
        }
        return total;
    }

    double getTotalProtein() const {
        double total = 0;
        for (const auto& pair : eatenProducts) {
            total += (pair.first.getProtein() / 100.0) * pair.second;
        }
        return total;
    }

    double getTotalCarbs() const {
        double total = 0;
        for (const auto& pair : eatenProducts) {
            total += (pair.first.getCarbs() / 100.0) * pair.second;
        }
        return total;
    }

    double getTotalFats() const {
        double total = 0;
        for (const auto& pair : eatenProducts) {
            total += (pair.first.getFats() / 100.0) * pair.second;
        }
        return total;
    }

    void displayMeal() const {
        std::cout << "--- MEAL SUMMARY: " << mealName << " ---" << std::endl;
        if (eatenProducts.empty()) {
            std::cout << " No products in this meal." << std::endl;
            return;
        }
        for (const auto& pair : eatenProducts) {
            double cal = (pair.first.getCalories() / 100.0) * pair.second;
            std::cout << " " << pair.first.getName() << ": " << pair.second << "g (" << cal << " kcal)" << std::endl;
        }
        std::cout << " Total Calories: " << getTotalCalories() << " kcal" << std::endl;
        std::cout << " Protein: " << getTotalProtein() << " g" << std::endl;
        std::cout << " Carbs: " << getTotalCarbs() << " g" << std::endl;
        std::cout << " Fats: " << getTotalFats() << " g" << std::endl;
        std::cout << "---------------------------------" << std::endl << std::endl;
    }
};

#endif
