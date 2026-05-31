#ifndef FOODLIBRARY_H
#define FOODLIBRARY_H

#include "FoodProduct.h"
#include <vector>
#include <iostream>
#include <stdexcept>

class FoodLibrary {
private:
    std::vector<FoodProductSnapshot> db;//databse of food products

public:
    // Create
    void createProduct(const FoodProduct& product) {
        for (const auto& item : db) {
            if (item.getName() == product.getName()) {
                throw std::invalid_argument("Product already exists in library.");
            }
        }
        db.push_back(product);
    }

    // Read
    FoodProductSnapshot readProduct(std::string name) const {
        for (const auto& item : db) {
            if (item.getName() == name) {
                return item;
            }
        }
        throw std::invalid_argument("Product '" + name + "' not found in library.");
    }

    // Update
    void updateProduct(std::string name, double newP, double newC, double newF) {
        for (auto& item : db) {
            if (item.getName() == name) {
                item = FoodProductSnapshot(name, newP, newC, newF, item.getCurrentDoses());
                return;
            }
        }
        throw std::invalid_argument("Cannot update. Product '" + name + "' not found.");
    }

    // Delete
    void deleteProduct(std::string name) {
        for (auto it = db.begin(); it != db.end(); ++it) {
            if (it->getName() == name) {
                db.erase(it);
                return;
            }
        }
        throw std::invalid_argument("Cannot delete. Product '" + name + "' not found.");
    }

    void displayLibrary() const {
        std::cout << "====== FOOD LIBRARY CATALOG ======" << std::endl;
        if (db.empty()) {
            std::cout << "Library is empty." << std::endl;
            return;
        }
        for (const auto& item : db) {
            std::cout << " " << item.getName() << ": " << item.getCalories() << " kcal [P: " 
                      << item.getProtein() << "g, C: " << item.getCarbs() << "g, F: " << item.getFats() << "g]" << std::endl;
        }
        std::cout << "==================================" << std::endl << std::endl;
    }
};

#endif
