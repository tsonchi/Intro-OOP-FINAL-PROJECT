#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "DailyTracker.h"

class User {
private:
    std::string name;
    char gender;
    double height;
    double weight;
    int age;
    int activityLevel;
    std::string goal;
    int dailyCaloricTarget;

    std::vector<DailyTracker> nutritionHistory;

    void calculateCaloricTarget() {
        double bmr;
        if (gender == 'M' || gender == 'm') {
            bmr = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age);
        } else {
            bmr = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
        }

        double amr = bmr;
        switch (activityLevel) {
            case 1: amr *= 1.2; break;
            case 2: amr *= 1.375; break;
            case 3: amr *= 1.55; break;
            case 4: amr *= 1.725; break;
            case 5: amr *= 1.9; break;
            default: amr *= 1.2; break;
        }

        if (goal == "Gain") {
            dailyCaloricTarget = (int)(amr + (amr * 0.10));
        } else if (goal == "Lose") {
            dailyCaloricTarget = (int)(amr - (amr * 0.20));
        } else {
            dailyCaloricTarget = (int)amr;
        }
    }
public:
    User(std::string name, char gender, double height, double weight, int age, int activityLevel, std::string goal) {
        if (name == "") throw std::invalid_argument("Name cannot be empty.");
        if (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f') {
            throw std::invalid_argument("Gender must be 'M' or 'F'.");
        }
        if (height <= 0 || weight <= 0 || age <= 0) {
            throw std::invalid_argument("Height, weight, and age must be positive numbers.");
        }
        if (activityLevel < 1 || activityLevel > 5) {
            throw std::invalid_argument("Activity level must be between 1 and 5.");
        }
        if (goal != "Gain" && goal != "Lose" && goal != "Maintain") {
            throw std::invalid_argument("Goal must be 'Gain', 'Lose', or 'Maintain'.");
        }

        this->name = name;
        this->gender = gender;
        this->height = height;
        this->weight = weight;
        this->age = age;
        this->activityLevel = activityLevel;
        this->goal = goal;
        calculateCaloricTarget();
    }

    std::string getName() const { return name; }
    int getDailyCaloricTarget() const { return dailyCaloricTarget; }

    void addDailyRecord(const DailyTracker& record) {
        nutritionHistory.push_back(record);
    }

    void displayProfile() const {
        std::cout << "=== User Profile ===" << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Goal: " << goal << std::endl;
        std::cout << "Daily Caloric Target: " << dailyCaloricTarget << " kcal" << std::endl;
        std::cout << "====================" << std::endl << std::endl;
    }

    void displayDailyReport(std::string date) const {
        int eaten = 0;
        bool found = false;

        for (const auto& record : nutritionHistory) {
            if (record.getDate() == date) {
                eaten = (int)record.getTotalCaloriesEaten();
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "No nutrition data found for date: " << date << std::endl;
            return;
        }

        int balance = dailyCaloricTarget - eaten;

        std::cout << "\n========================================\n";
        std::cout << "DAILY CALORIE REPORT FOR " << name << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "========================================\n";
        std::cout << "Target: " << dailyCaloricTarget << " kcal\n";
        std::cout << "Eaten: " << eaten << " kcal\n";
        std::cout << "----------------------------------------\n";

        if (balance > 0) {
            std::cout << "Remaining: You need " << balance << " kcal MORE to hit your target.\n";
            if (balance > 500) {
                std::cout << "Tip: You are quite short on calories. Consider a high-protein snack!\n";
            }
        } else if (balance < 0) {
            std::cout << "Surplus: You exceeded your target by " << std::abs(balance) << " kcal.\n";
            if (eaten > dailyCaloricTarget + 500) {
                std::cout << "Tip: Watch out! You are way over your daily budget.\n";
            }
        } else {
            std::cout << "Perfect! You hit your daily caloric target exactly!\n";
        }
        std::cout << "========================================\n\n";
    }
};

#endif