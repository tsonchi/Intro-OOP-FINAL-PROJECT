#ifndef WORKOUTSESSION_H
#define WORKOUTSESSION_H

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "Exercise.h"

class WorkoutSession {
private:
    std::string workoutName; // напр. "Chest & Triceps", "Leg Day"
    std::string date;        // напр. "2026-17-05"
    std::vector<Exercise> exercises;

public:
    WorkoutSession(std::string name, std::string date) {
        if (name == "" || date == "") throw std::invalid_argument("Workout name and date cannot be empty.");
        this->workoutName = name;
        this->date = date;
    }

    void addExercise(const Exercise& exercise) {
        exercises.push_back(exercise);
    }

    std::string getWorkoutName() const { return workoutName; }
    std::string getDate() const { return date; }
    const std::vector<Exercise>& getExercises() const { return exercises; }

    void displayWorkout() const {
        std::cout << "======= WORKOUT: " << workoutName << " (" << date << ") =======" << std::endl;
        if (exercises.empty()) {
            std::cout << " No exercises logged for this workout." << std::endl;
            return;
        }
        for (const auto& exercise : exercises) {
            exercise.displayExercise();
        }
        std::cout << "=================================================" << std::endl << std::endl;
    }
};

#endif