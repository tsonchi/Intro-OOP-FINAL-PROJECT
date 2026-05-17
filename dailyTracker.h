#ifndef DAILYTRACKER_H
#define DAILYTRACKER_H

#include "User.h"
#include "Meal.h"
#include <vector>
#include <iostream>
#include <cmath>

class DailyTracker {
private:
    std::string date;
    const User& user;
    std::vector<Meal> dailyMeals;

public:
    DailyTracker(std::string date, const User& u) : date(date), user(u) {
        if (date == "") throw std::invalid_argument("Date cannot be empty.");
        
    }

    void addMeal(const Meal& meal) {
        dailyMeals.push_back(meal);
    }

    double getTotalCaloriesEaten() const {
        double total = 0;
        for (const auto& meal : dailyMeals) {
            total += meal.getTotalCalories();
        }
        return total;
    }

    void displayDailyReport() const {
        int target = user.getDailyCaloricTarget();
        int eaten = (int)getTotalCaloriesEaten();
        int balance = target - eaten;

        std::cout << "\n========================================\n";
        std::cout << "DAILY CALORIE REPORT\n";
        std::cout <<  "Date: " << date << std::endl;
        std::cout << "========================================\n";
        std::cout << "Target: " << target << " kcal\n";
        std::cout << "Eaten: " << eaten << " kcal\n";
        std::cout << "----------------------------------------\n";

        if (balance > 0) {
            std::cout << "Remaining: You need " << balance << " kcal MORE to hit your target.\n";
            if (balance > 500) {
                std::cout << "Tip: You are quite short on calories. Consider a high-protein snack!\n";
            }
        } else if (balance < 0) {
            std::cout << "Surplus: You exceeded your target by " << std::abs(balance) << " kcal.\n";
            if (eaten > target + 500) {
                std::cout << "Tip: Watch out! You are way over your daily budget.\n";
            }
        } else {
            std::cout << "Perfect! You hit your daily caloric target exactly!\n";
        }
        std::cout << "========================================\n\n";
    }
};

#endif