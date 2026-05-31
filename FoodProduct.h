#ifndef FOODPRODUCT_H
#define FOODPRODUCT_H

#include <iostream>
#include <stdexcept>
#include <string>

class FoodProduct {
private:
    std::string name;
    double protein;
    double carbs;
    double fats;
    double calories;
    int currentDoses;

    void calculateCalories() {
        calories = (protein * 4) + (carbs * 4) + (fats * 9);
    }

public:
    FoodProduct(std::string name, double protein, double carbs, double fats, int currentDoses = 0) {
        if (name == "") throw std::invalid_argument("Product name cannot be empty.");
        if (protein < 0 || carbs < 0 || fats < 0) {
            throw std::invalid_argument("Macros cannot be negative numbers.");
        }
        if (currentDoses < 0) {
            throw std::invalid_argument("Current doses cannot be negative.");
        }

        this->name = name;
        this->protein = protein;
        this->carbs = carbs;
        this->fats = fats;
        this->currentDoses = currentDoses;
        calculateCalories();
    }

    virtual ~FoodProduct() {}

    std::string getName() const { return name; }
    double getProtein() const { return protein; }
    double getCarbs() const { return carbs; }
    double getFats() const { return fats; }
    double getCalories() const { return calories; }
    int getCurrentDoses() const { return currentDoses; }

    void setCurrentDoses(int doses) {
        if (doses < 0) throw std::invalid_argument("Current doses cannot be negative.");
        currentDoses = doses;
    }

    void addDoses(int doses) {
        if (doses <= 0) throw std::invalid_argument("Doses must be positive.");
        currentDoses += doses;
    }

    bool useDose() {
        if (currentDoses <= 0) return false;
        currentDoses--;
        return true;
    }

    virtual void displayProduct() const = 0;
};

class BasicFoodProduct : public FoodProduct {
public:
    BasicFoodProduct(std::string name, double protein, double carbs, double fats)
        : FoodProduct(name, protein, carbs, fats) {}

    BasicFoodProduct(const FoodProduct& product)
        : FoodProduct(product.getName(), product.getProtein(), product.getCarbs(), product.getFats()) {}

    void displayProduct() const override {
        std::cout << "Food Product: " << getName() << std::endl;
        std::cout << "Protein: " << getProtein() << " g/100g" << std::endl;
        std::cout << "Carbs: " << getCarbs() << " g/100g" << std::endl;
        std::cout << "Fats: " << getFats() << " g/100g" << std::endl;
        std::cout << "Calories: " << getCalories() << " kcal/100g" << std::endl;
    }
};

class TrainingFoodProduct : public FoodProduct {
public:
    TrainingFoodProduct(const FoodProduct& product)
        : FoodProduct(product.getName(), product.getProtein(), product.getCarbs(), product.getFats(), product.getCurrentDoses()) {}

    TrainingFoodProduct(std::string name, double protein, double carbs, double fats, int currentDoses = 0)
        : FoodProduct(name, protein, carbs, fats, currentDoses) {}

    void displayProduct() const override {
        std::cout << "Training Food Product: " << getName() << std::endl;
        std::cout << "Protein: " << getProtein() << " g/100g" << std::endl;
        std::cout << "Carbs: " << getCarbs() << " g/100g" << std::endl;
        std::cout << "Fats: " << getFats() << " g/100g" << std::endl;
        std::cout << "Calories: " << getCalories() << " kcal/100g" << std::endl;
        std::cout << "Current doses: " << getCurrentDoses() << std::endl;
    }
};

#endif
