#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "Set.h"

class Exercise {
private:
    std::string name;
    std::string muscleGroup; // Нова променлива за мускулна група
    std::vector<Set> sets;

public:
    // Конструктор за библиотеката (само име и мускулна група)
    Exercise(std::string name, std::string muscleGroup) {
        if (name == "" || muscleGroup == "") {
            throw std::invalid_argument("Exercise name and muscle group cannot be empty.");
        }
        this->name = name;
        this->muscleGroup = muscleGroup;
    }

    void addSet(const Set& set) {
        sets.push_back(set);
    }

    std::string getName() const { return name; }
    std::string getMuscleGroup() const { return muscleGroup; }
    const std::vector<Set>& getSets() const { return sets; }

    void displayExercise() const {
        std::cout << "  * " << name << " (" << muscleGroup << "):" << std::endl;
        for (size_t i = 0; i < sets.size(); ++i) {
            std::cout << "    Set " << i + 1 << ": " 
                      << sets[i].getWeight() << " kg x " 
                      << sets[i].getReps() << " reps";
            
            if (sets[i].getIsWarmup()) {
                std::cout << " (Warmup)";
            }
            std::cout << std::endl;
        }
    }
};

#endif