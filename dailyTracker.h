#ifndef DAILYTRACKER_H
#define DAILYTRACKER_H

#include "Meal.h"
#include <vector>
#include <string>

class DailyTracker {
private:
    std::string date;
    std::vector<Meal> dailyMeals;
    std::vector<std::string> consumedSupplements;
    bool workoutComplete;

public:
    DailyTracker(std::string date) : date(date), workoutComplete(false) {}

    void addMeal(const Meal& meal) {
        dailyMeals.push_back(meal);
    }

    void markWorkoutComplete() {
        workoutComplete = true;
    }

    void markSupplementConsumed(const std::string& supplementName) {
        if (!hasConsumedSupplement(supplementName)) {
            consumedSupplements.push_back(supplementName);
        }
    }

    std::string getDate() const { 
        return date; 
    }

    bool getWorkoutComplete() const {
        return workoutComplete;
    }

    bool hasConsumedSupplement(const std::string& supplementName) const {
        for (const auto& consumedSupplement : consumedSupplements) {
            if (consumedSupplement == supplementName) {
                return true;
            }
        }

        return false;
    }

    double getTotalCaloriesEaten() const {
        double total = 0;
        for (const auto& meal : dailyMeals) {
            total += meal.getTotalCalories();
        }
        return total;
    }

    double getTotalProteinEaten() const {
        double total = 0;
        for (const auto& meal : dailyMeals) {
            total += meal.getTotalProtein();
        }
        return total;
    }

    double getTotalCarbsEaten() const {
        double total = 0;
        for (const auto& meal : dailyMeals) {
            total += meal.getTotalCarbs();
        }
        return total;
    }

    double getTotalFatsEaten() const {
        double total = 0;
        for (const auto& meal : dailyMeals) {
            total += meal.getTotalFats();
        }
        return total;
    }
};

#endif 
