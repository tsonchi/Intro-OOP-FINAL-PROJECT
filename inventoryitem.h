#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include "FoodProduct.h"
#include <iostream>
#include <string>
#include <stdexcept>

class InventoryItem : public FoodProduct {
private:
    int totalDoses;
    double doseSizeGrams;

public:
    InventoryItem(std::string name, double protein, double carbs, double fats, int totalDoses, double doseSize)
        : FoodProduct(name, protein, carbs, fats, totalDoses), totalDoses(totalDoses), doseSizeGrams(doseSize) {
        if (totalDoses <= 0 || doseSize <= 0) {
            throw std::invalid_argument("Doses and dose size must be positive numbers.");
        }
    }

    int getTotalDoses() const { return totalDoses; }
    double getDoseSizeGrams() const { return doseSizeGrams; }

    void consumeDose() {
        if (!useDose()) {
            std::cout << "No doses left for " << getName() << std::endl;
            return;
        }

        std::cout << "Consumed 1 dose of " << getName() << ". Remaining: " << getCurrentDoses() << std::endl;

        if (getCurrentDoses() <= 5 && getCurrentDoses() > 0) {
            std::cout << "Warning: " << getName() << " is running low! Only " << getCurrentDoses() << " doses left." << std::endl;
        }
    }

    void restock(int additionalDoses) {
        addDoses(additionalDoses);
        totalDoses += additionalDoses;
    }

    void displayProduct() const override {
        std::cout << "Inventory Item: " << getName() << std::endl;
        std::cout << "Protein: " << getProtein() << " g/100g" << std::endl;
        std::cout << "Carbs: " << getCarbs() << " g/100g" << std::endl;
        std::cout << "Fats: " << getFats() << " g/100g" << std::endl;
        std::cout << "Calories: " << getCalories() << " kcal/100g" << std::endl;
        std::cout << "Doses: " << getCurrentDoses() << "/" << totalDoses << std::endl;
        std::cout << "Dose size: " << doseSizeGrams << " g" << std::endl;
    }
};

#endif
