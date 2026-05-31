#ifndef EXERCISE_H
#define EXERCISE_H

#include <iostream>
#include <istream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Set.h"

class Exercise {
private:
    std::string name;
    std::string muscleGroup;
    std::vector<Set> sets;

public:
    Exercise() : name("Unnamed Exercise"), muscleGroup("Unknown") {}

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

    friend std::istream& operator>>(std::istream& in, Exercise& exercise) {
        std::getline(in >> std::ws, exercise.name);
        if (!in) return in;

        if (exercise.name == "") {
            in.setstate(std::ios::failbit);
            return in;
        }

        exercise.muscleGroup = "Unknown";
        exercise.sets.clear();
        return in;
    }

    friend std::istream& operator>>(std::istream& in, class WorkoutSession& session);
};

#endif
