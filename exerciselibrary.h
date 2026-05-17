#ifndef EXERCISELIBRARY_H
#define EXERCISELIBRARY_H

#include "Exercise.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

class ExerciseLibrary {
private:
    std::vector<Exercise> availableExercises;

public:
    void addExerciseToLibrary(const Exercise& exercise) {
        for (const auto& ex : availableExercises) {
            if (ex.getName() == exercise.getName()) {
                throw std::invalid_argument("Exercise already exists in library.");
            }
        }
        availableExercises.push_back(exercise);
    }

    Exercise getExerciseFromLibrary(std::string name) const {
        for (const auto& ex : availableExercises) {
            if (ex.getName() == name) {
                return ex; // Връща копие на обекта, готово за добавяне на серии
            }
        }
        throw std::invalid_argument("Exercise not found in library: " + name);
    }

    void deleteExerciseFromLibrary(std::string name) {
        for (auto it = availableExercises.begin(); it != availableExercises.end(); ++it) {
            if (it->getName() == name) {
                availableExercises.erase(it);
                return;
            }
        }
        throw std::invalid_argument("Exercise not found for deletion.");
    }

    void displayLibrary() const {
        std::cout << "--- EXERCISE LIBRARY ---" << std::endl;
        if (availableExercises.empty()) {
            std::cout << " Library is empty." << std::endl;
            return;
        }
        for (const auto& ex : availableExercises) {
            std::cout << " - " << ex.getName() << " [" << ex.getMuscleGroup() << "]" << std::endl;
        }
        std::cout << "------------------------" << std::endl << std::endl;
    }
};

#endif