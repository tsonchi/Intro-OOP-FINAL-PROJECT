#ifndef WORKOUTSESSION_H
#define WORKOUTSESSION_H

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Exercise.h"

class WorkoutSession {
private:
    std::string workoutName;
    std::string date;
    std::vector<Exercise> exercises;

    static std::string trim(const std::string& text) {
        size_t start = 0;
        while (start < text.size() && std::isspace(static_cast<unsigned char>(text[start]))) {
            start++;
        }

        size_t end = text.size();
        while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1]))) {
            end--;
        }

        return text.substr(start, end - start);
    }

    static bool readNonEmptyLine(std::istream& in, std::string& line) {
        while (std::getline(in, line)) {
            line = trim(line);
            if (line != "") return true;
        }
        return false;
    }

    static bool isSeparator(const std::string& line) {
        if (line.size() < 3) return false;
        for (char ch : line) {
            if (ch != '-') return false;
        }
        return true;
    }

    static bool isSetLine(const std::string& line) {
        std::istringstream input(line);
        double weight;
        int reps;
        char separator;
        input >> weight >> separator >> reps;
        return input && (separator == 'x' || separator == 'X');
    }

public:
    WorkoutSession() : workoutName("Unnamed Workout"), date("Unknown Date") {}

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

    static std::vector<WorkoutSession> readFromFile(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file) {
            throw std::invalid_argument("Cannot open workout file: " + fileName);
        }

        std::vector<WorkoutSession> sessions;
        while (file) {
            WorkoutSession session;
            file >> session;
            if (file || (file.eof() && session.workoutName != "Unnamed Workout" && session.date != "Unknown Date")) {
                sessions.push_back(session);
            }
            if (file.eof()) break;
        }

        return sessions;
    }

    friend std::istream& operator>>(std::istream& in, WorkoutSession& session) {
        session.exercises.clear();

        if (!readNonEmptyLine(in, session.workoutName)) return in;
        if (!readNonEmptyLine(in, session.date)) {
            in.setstate(std::ios::failbit);
            return in;
        }

        std::string pendingLine;
        bool hasPendingLine = false;

        while (true) {
            std::string firstLine;
            if (hasPendingLine) {
                firstLine = pendingLine;
                hasPendingLine = false;
            } else if (!readNonEmptyLine(in, firstLine)) {
                break;
            }

            if (isSeparator(firstLine)) break;

            std::string secondLine;
            if (!readNonEmptyLine(in, secondLine)) {
                session.exercises.push_back(Exercise(firstLine, "Unknown"));
                break;
            }

            if (isSeparator(secondLine)) {
                session.exercises.push_back(Exercise(firstLine, "Unknown"));
                break;
            }

            std::string exerciseName = firstLine;
            std::string muscleGroup = "Unknown";

            if (!isSetLine(secondLine)) {
                muscleGroup = firstLine;
                exerciseName = secondLine;
            } else {
                pendingLine = secondLine;
                hasPendingLine = true;
            }

            Exercise exercise(exerciseName, muscleGroup);

            while (true) {
                std::string setLine;
                if (hasPendingLine) {
                    setLine = pendingLine;
                    hasPendingLine = false;
                } else if (!std::getline(in, setLine)) {
                    break;
                }

                setLine = trim(setLine);
                if (setLine == "") break;
                if (isSeparator(setLine)) {
                    session.exercises.push_back(exercise);
                    return in;
                }
                if (!isSetLine(setLine)) {
                    pendingLine = setLine;
                    hasPendingLine = true;
                    break;
                }

                std::istringstream setStream(setLine);
                Set set;
                setStream >> set;
                if (!setStream) {
                    in.setstate(std::ios::failbit);
                    return in;
                }
                exercise.addSet(set);
            }

            session.exercises.push_back(exercise);

            if (!in && !in.eof()) return in;
            if (in.eof()) break;
        }

        if (session.workoutName == "" || session.date == "") {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
};

#endif
