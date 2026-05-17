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
    int proteinTarget;
    int carbsTarget;
    int fatsTarget;

    std::vector<DailyTracker> nutritionHistory;

    void calculateCaloricTarget() {
        // 1. Изчисляване на BMR
        double bmr;
        if (gender == 'M' || gender == 'm') {
            bmr = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age);
        } else {
            bmr = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
        }

        // 2. Изчисляване на AMR (с активност)
        double amr = bmr;
        switch (activityLevel) {
            case 1: amr *= 1.2; break;
            case 2: amr *= 1.375; break;
            case 3: amr *= 1.55; break;
            case 4: amr *= 1.725; break;
            case 5: amr *= 1.9; break;
            default: amr *= 1.2; break;
        }

        // 3. Калориен излишък/дефицит в проценти
        if (goal == "Gain") {
            dailyCaloricTarget = (int)(amr + (amr * 0.10));
        } else if (goal == "Lose") {
            dailyCaloricTarget = (int)(amr - (amr * 0.20));
        } else {
            dailyCaloricTarget = (int)amr;
        }

        // 4. УНИВЕРСАЛНО изчисляване на Макроси според активността
        double proteinMultiplier = 1.2; // по подразбиране за неактивни хора
        double fatsMultiplier = 0.8;

        if (activityLevel >= 3) {
            proteinMultiplier = 2.0; // за трениращи хора
            fatsMultiplier = 1.0;
        } else if (activityLevel == 2) {
            proteinMultiplier = 1.6; // за умерено активни
            fatsMultiplier = 0.9;
        }

        proteinTarget = (int)(weight * proteinMultiplier);
        fatsTarget = (int)(weight * fatsMultiplier);
        
        // Въглехидратите обират останалите калории
        double caloriesFromProtein = proteinTarget * 4.0;
        double caloriesFromFats = fatsTarget * 9.0;
        double remainingCalories = dailyCaloricTarget - (caloriesFromProtein + caloriesFromFats);
        
        // Защита: ако калориите не стигат (при много агресивен дефицит), въглехидратите да не станат отрицателни
        if (remainingCalories < 0) remainingCalories = 0; 

        carbsTarget = (int)(remainingCalories / 4.0);
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

    // Методът за промяна на теглото, който поиска
    void updateWeight(double newWeight) {
        if (newWeight <= 0) throw std::invalid_argument("Weight must be a positive number.");
        this->weight = newWeight;
        calculateCaloricTarget(); // Автоматично преизчислява всичко
    }

    void addDailyRecord(const DailyTracker& record) {
        nutritionHistory.push_back(record);
    }

    void displayProfile() const {
        std::cout << "=== User Profile ===" << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Weight: " << weight << " kg" << std::endl;
        std::cout << "Goal: " << goal << std::endl;
        std::cout << "Targets -> Calories: " << dailyCaloricTarget << " kcal | P: " 
                  << proteinTarget << "g | C: " << carbsTarget << "g | F: " << fatsTarget << "g" << std::endl;
        std::cout << "====================" << std::endl << std::endl;
    }

    void displayDailyReport(std::string date) const {
        const DailyTracker* targetRecord = nullptr;

        for (const auto& record : nutritionHistory) {
            if (record.getDate() == date) {
                targetRecord = &record;
                break;
            }
        }

        if (targetRecord == nullptr) {
            std::cout << "No nutrition data found for date: " << date << std::endl;
            return;
        }

        int eatenCal = (int)targetRecord->getTotalCaloriesEaten();
        int eatenP = (int)targetRecord->getTotalProteinEaten();
        int eatenC = (int)targetRecord->getTotalCarbsEaten();
        int eatenF = (int)targetRecord->getTotalFatsEaten();

        int balanceCal = dailyCaloricTarget - eatenCal;

        std::cout << "\n========================================\n";
        std::cout << "DAILY NUTRITION REPORT FOR " << name << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "========================================\n";
        std::cout << " (Nutrient) | Eaten / Target\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Calories:       " << eatenCal << " / " << dailyCaloricTarget << " kcal\n";
        std::cout << "Protein:        " << eatenP << " / " << proteinTarget << " g\n";
        std::cout << "Carbs:          " << eatenC << " / " << carbsTarget << " g\n";
        std::cout << "Fats:           " << eatenF << " / " << fatsTarget << " g\n";
        std::cout << "----------------------------------------\n";

        if (balanceCal > 0) {
            std::cout << "Remaining: You need " << balanceCal << " kcal MORE to hit your target.\n";
            if (eatenP < proteinTarget) {
                std::cout << "Tip: You are short on protein (" << (proteinTarget - eatenP) << "g left). Focus on protein sources!\n";
            }
            if (eatenC < carbsTarget) {
                std::cout << "Tip: You are short on carbs (" << (carbsTarget - eatenC) << "g left). Consider adding some whole grains or fruits.\n";
            }
            if (eatenF < fatsTarget) {
                std::cout << "Tip: You are short on fats (" << (fatsTarget - eatenF) << "g left). Healthy fats can be found in nuts, seeds, and avocados.\n";
            }
        } else if (balanceCal < 0) {
            std::cout << "Surplus: You exceeded your target by " << std::abs(balanceCal) << " kcal.\n";
        } else {
            std::cout << "Perfect! You hit your daily caloric target exactly!\n";
        }
        std::cout << "========================================\n\n";
    }
};

#endif