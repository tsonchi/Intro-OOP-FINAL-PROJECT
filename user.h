#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <stdexcept>

class User {
private:
    std::string name;
    char gender;            // 'M' for Male, 'F' for Female
    double height;          // in cm
    double weight;          // in kg
    int age;                // years
    int activityLevel;      // 1 to 5
    std::string goalType;   // "Gain", "Maintain", "Lose"
    double dailyCaloricTarget;

    void calculateDailyNeeds() {
        // Mifflin-St Jeor Equation
        double bmr = (10 * weight) + (6.25 * height) - (5 * age);
        if (gender == 'M' || gender == 'm') {
            bmr += 5;
        } else {
            bmr -= 161;
        }

        double activityMultiplier = 1.2;
        switch (activityLevel) {
            case 1: activityMultiplier = 1.2;   break; // Sedentary
            case 2: activityMultiplier = 1.375; break; // Lightly active
            case 3: activityMultiplier = 1.55;  break; // Moderately active
            case 4: activityMultiplier = 1.725; break; // Very active
            case 5: activityMultiplier = 1.9;   break; // Super active
        }

        double tdee = bmr * activityMultiplier; 

        if (goalType == "Gain") {
            dailyCaloricTarget = tdee + 300; 
        } else if (goalType == "Lose") {
            dailyCaloricTarget = tdee - 400; 
        } else {
            dailyCaloricTarget = tdee;       
        }
    }

public:
    User(std::string name, char gender, double height, double weight, int age, int activityLevel, std::string goalType) {
        if(name == "") throw std::invalid_argument("Name cannot be empty.");
        this->name = name;
        
        if (gender != 'M' && gender != 'F' && gender != 'm' && gender != 'f') {
            throw std::invalid_argument("Invalid gender. Use 'M' or 'F'.");
        }
        this->gender = (gender == 'F' || gender == 'f') ? 'F' : 'M';
        
        setPhysicalData(height, weight, age);
        setActivityAndGoal(activityLevel, goalType);
    }

    void setPhysicalData(double h, double w, int a) {
        if (h <= 0 || h > 300) throw std::invalid_argument("Height must be a positive number between 0 and 300.");
        if (w <= 0 || w > 500) throw std::invalid_argument("Weight must be a positive number between 0 and 500.");
        if (a <= 0 || a > 110) throw std::invalid_argument("Age must be a positive number between 0 and 110.");
        height = h;
        weight = w;
        age = a;
        calculateDailyNeeds(); 
    }

    void setActivityAndGoal(int activity, std::string goal) {
        if (activity >= 1 && activity <= 5) activityLevel = activity;
        else throw std::invalid_argument("Activity level must be between 1 and 5.");

        if (goal == "Gain" || goal == "Maintain" || goal == "Lose") {
            goalType = goal;
        } else {
            throw std::invalid_argument("Invalid goal. Use 'Gain', 'Maintain' or 'Lose'.");
        }
        calculateDailyNeeds();
    }

    int getDailyCaloricTarget() const { return (int)dailyCaloricTarget; }

    void displayProfile() const {
        std::cout << "========================================\n";
        std::cout << "USER PROFILE: " << name << " (" << (gender == 'M' ? "Male" : "Female") << ")\n";
        std::cout << "========================================\n";
        std::cout << " Height: " << height << " cm | Weight: " << weight << " kg | Age: " << age << " y/o\n";
        std::cout << " Activity Level (1-5): " << activityLevel << "\n";
        std::cout << " Goal: " << goalType << "\n";
        std::cout << "----------------------------------------\n";
        std::cout << " Daily Caloric Target: " << getDailyCaloricTarget() << " kcal\n";
        std::cout << "========================================\n\n";
    }
};

#endif