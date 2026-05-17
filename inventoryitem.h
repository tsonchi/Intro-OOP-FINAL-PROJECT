#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include "FoodProduct.h"
#include <iostream>
#include <string>
#include <stdexcept>

class InventoryItem : public FoodProduct {
private:
    int currentDoses;
    int totalDoses;
    double doseSizeGrams;

public:
    InventoryItem(std::string name, double protein, double carbs, double fats, int totalDoses, double doseSize)
        : FoodProduct(name, protein, carbs, fats), currentDoses(totalDoses), totalDoses(totalDoses), doseSizeGrams(doseSize) {
        if (totalDoses <= 0 || doseSize <= 0) {
            throw std::invalid_argument("Doses and dose size must be positive numbers.");
        }
    }

    int getCurrentDoses() const { return currentDoses; }
    double getDoseSizeGrams() const { return doseSizeGrams; }

    void consumeDose() {
        if (currentDoses <= 0) {
            std::cout << "No doses left for " << getName() << std::endl;
            return;
        }
        
        currentDoses--;
        std::cout << "Consumed 1 dose of " << getName() << ". Remaining: " << currentDoses << std::endl;

        if (currentDoses <= 5 && currentDoses > 0) {
            std::cout << "Warning: " << getName() << " is running low! Only " << currentDoses << " doses left." << std::endl;
        }
    }

    void restock(int additionalDoses) {
        if (additionalDoses <= 0) throw std::invalid_argument("Restock doses must be positive.");
        currentDoses += additionalDoses;
    }
};

#endif