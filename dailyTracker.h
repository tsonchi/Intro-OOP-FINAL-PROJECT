#ifndef DAILYTRACKER_H
#define DAILYTRACKER_H

#include "Meal.h"
#include <vector>
#include <string>

class DailyTracker {
private:
    std::string date;
    std::vector<Meal> dailyMeals;

public:
    DailyTracker(std::string date) : date(date) {}

    void addMeal(const Meal& meal) {
        dailyMeals.push_back(meal);
    }

    std::string getDate() const { 
        return date; 
    }

    double getTotalCaloriesEaten() const {
        double total = 0;
        for (const auto& meal : dailyMeals) {
            total += meal.getTotalCalories();
        }
        return total;
    }
};

#endif