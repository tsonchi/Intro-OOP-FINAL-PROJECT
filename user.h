#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "DailyTracker.h"
#include "WorkoutSession.h"
#include "Achievement.h"
#include "inventoryitem.h"

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
    std::vector<WorkoutSession> workoutHistory;
    std::vector<Achievement> personalRecords;
    std::vector<InventoryItem> supplements;

    bool hasWorkoutForDate(const std::string& date) const {
        for (const auto& session : workoutHistory) {
            if (session.getDate() == date) {
                return true;
            }
        }

        return false;
    }

    void markDailyWorkoutComplete(const std::string& date) {
        for (auto& record : nutritionHistory) {
            if (record.getDate() == date) {
                record.markWorkoutComplete();
                return;
            }
        }
    }

    void markDailySupplementConsumed(const std::string& date, const std::string& supplementName) {
        for (auto& record : nutritionHistory) {
            if (record.getDate() == date) {
                record.markSupplementConsumed(supplementName);
                return;
            }
        }
    }

    void calculateCaloricTarget() {
        double bmr;//Basal Metabolic Rate
        if (gender == 'M' || gender == 'm') {
            bmr = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age);
        } else {
            bmr = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
        }

        double amr = bmr;//active metabolic rate
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

        double proteinMultiplier = 1.2;
        double fatsMultiplier = 0.8;

        if (activityLevel >= 3) {
            proteinMultiplier = 2.0;
            fatsMultiplier = 1.0;
        } else if (activityLevel == 2) {
            proteinMultiplier = 1.6;
            fatsMultiplier = 0.9;
        }

        proteinTarget = (int)(weight * proteinMultiplier);
        fatsTarget = (int)(weight * fatsMultiplier);
        
        double caloriesFromProtein = proteinTarget * 4.0;
        double caloriesFromFats = fatsTarget * 9.0;
        double remainingCalories = dailyCaloricTarget - (caloriesFromProtein + caloriesFromFats);
        
        if (remainingCalories < 0) remainingCalories = 0; 
        carbsTarget = (int)(remainingCalories / 4.0);
    }

    void checkNewRecords(const WorkoutSession& session) {
        for (const auto& exercise : session.getExercises()) {
            double maxWeightToday = 0;
            int repsForMaxWeight = 0;
            bool foundValidSet = false;

            for (const auto& set : exercise.getSets()) {
                if (!set.getIsWarmup() && set.getWeight() > maxWeightToday) {
                    maxWeightToday = set.getWeight();
                    repsForMaxWeight = set.getReps();
                    foundValidSet = true;
                }
            }

            if (!foundValidSet) continue;

            bool dynamicRecordFound = false;
            for (auto& pr : personalRecords) {
                if (pr.getExerciseName() == exercise.getName()) {
                    dynamicRecordFound = true;
                    if (maxWeightToday > pr.getMaxWeight()) {
                        std::cout << "NEW PERSONAL RECORD for " << exercise.getName() << "! "
                                  << maxWeightToday << " kg x " << repsForMaxWeight << " reps "
                                  << "(Previous PR: " << pr.getMaxWeight() << " kg)" << std::endl;
                        pr.updateRecord(maxWeightToday, repsForMaxWeight);
                    }
                    break;
                }
            }

            if (!dynamicRecordFound) {
                personalRecords.push_back(Achievement(exercise.getName(), maxWeightToday, repsForMaxWeight));
                std::cout << "First record for " << exercise.getName() << " set to " 
                          << maxWeightToday << " kg." << std::endl;
            }
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
    const std::vector<DailyTracker>& getNutritionHistory() const { return nutritionHistory; }
    const std::vector<WorkoutSession>& getWorkoutHistory() const { return workoutHistory; }
    const std::vector<InventoryItem>& getSupplements() const {return supplements;}

    void updateWeight(double newWeight) {
        if (newWeight <= 0) throw std::invalid_argument("Weight must be a positive number.");
        this->weight = newWeight;
        calculateCaloricTarget();
    }

    void addDailyRecord(DailyTracker record) {
        if (hasWorkoutForDate(record.getDate())) {
            record.markWorkoutComplete();
        }
        nutritionHistory.push_back(record);
    }

    void addWorkoutRecord(const WorkoutSession& session) {
        workoutHistory.push_back(session);
        markDailyWorkoutComplete(session.getDate());
        checkNewRecords(session);
    }
    void addSupplement(const InventoryItem& supplement) {
        supplements.push_back(supplement);
    }

    void consumeSupplement(const std::string& supplementName) {
        for (auto& supplement : supplements) {
            if (supplement.getName() == supplementName) {
                supplement.consumeDose();
                return;
            }
        }

        throw std::invalid_argument("Supplement not found: " + supplementName);
    }

    void consumeSupplement(const std::string& supplementName, const std::string& date) {
        consumeSupplement(supplementName);
        markDailySupplementConsumed(date, supplementName);
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

        std::cout << "========================================" << std::endl;
        std::cout << "DAILY NUTRITION REPORT FOR " << name << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Calories:       " << eatenCal << " / " << dailyCaloricTarget << " kcal" << std::endl;
        std::cout << "Protein:        " << eatenP << " / " << proteinTarget << " g" << std::endl;
        std::cout << "Carbs:          " << eatenC << " / " << carbsTarget << " g" << std::endl;
        std::cout << "Fats:           " << eatenF << " / " << fatsTarget << " g" << std::endl;
        std::cout << "Workout:        " << (targetRecord->getWorkoutComplete() ? "Complete" : "Not complete yet") << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        if (balanceCal > 0) {
            std::cout << "Remaining: You need " << balanceCal << " kcal MORE to hit your target." << std::endl;
        } else if (balanceCal < 0) {
            std::cout << "Surplus: You exceeded your target by " << std::abs(balanceCal) << " kcal." << std::endl;
        } else {
            std::cout << "Perfect! You hit your daily caloric target exactly!" << std::endl;
        }
        if(!supplements.empty()){
            for(const auto& sup: supplements){
                if(!targetRecord->hasConsumedSupplement(sup.getName())){
                    std::cout << "Supplement: " << sup.getName() << " | Doses Available: " << sup.getCurrentDoses() << " (Dose not consumed today)" << std::endl;
                } else {
                    std::cout << "Supplement: " << sup.getName() << " | Doses Available: " << sup.getCurrentDoses() << " (Dose consumed today)" << std::endl;
                }
            }
        }else{
            std::cout << "No supplements added yet." << std::endl;
        }
        std::cout << "========================================" << std::endl << std::endl;
    }

    void displayWorkoutReport(std::string date) const {
        const WorkoutSession* targetWorkout = nullptr;
        for (const auto& session : workoutHistory) {
            if (session.getDate() == date) {
                targetWorkout = &session;
                break;
            }
        }

        if (targetWorkout == nullptr) {
            std::cout << "No workout logged for date: " << date << std::endl;
            return;
        }

        std::cout << "=== WORKOUT REPORT FOR " << name << " ===" << std::endl;
        targetWorkout->displayWorkout();
    }
};

#endif 
