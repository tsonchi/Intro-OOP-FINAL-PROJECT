#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "User.h"
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

class ReportGenerator {
private:
    static int dateToNumber(const std::string& date) {
        if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
            throw std::invalid_argument("Date must use YYYY-DD-MM format.");
        }

        int year = std::stoi(date.substr(0, 4));
        int day = std::stoi(date.substr(5, 2));
        int month = std::stoi(date.substr(8, 2));
        return year * 10000 + month * 100 + day;
    }

    static bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& endDate) {
        int current = dateToNumber(date);
        return current >= dateToNumber(startDate) && current <= dateToNumber(endDate);
    }

public:
    static void generateWeeklyReport(const User& user, const std::vector<DailyTracker>& nutrition, const std::vector<WorkoutSession>& workouts, const std::string& startDate, const std::string& endDate) {
        std::cout << "--- WEEKLY REPORT FOR " << user.getName() << " ---" << std::endl;
        std::cout << " Week: " << startDate << " to " << endDate << std::endl;

        double totalCal = 0;
        size_t nutritionDays = 0;

        for (const auto& day : nutrition) {
            if (isDateInRange(day.getDate(), startDate, endDate)) {
                totalCal += day.getTotalCaloriesEaten();
                nutritionDays++;
            }
        }
        
        double avgCalories = (nutritionDays > 0) ? (totalCal / nutritionDays) : 0;
        size_t workoutCount = 0;
        std::map<std::string, Achievement> weeklyRecords;

        for (const auto& workout : workouts) {
            if (!isDateInRange(workout.getDate(), startDate, endDate)) continue;

            workoutCount++;
            for (const auto& exercise : workout.getExercises()) {
                for (const auto& set : exercise.getSets()) {
                    if (set.getIsWarmup()) continue;

                    auto record = weeklyRecords.find(exercise.getName());
                    if (record == weeklyRecords.end()) {
                        weeklyRecords.insert({ exercise.getName(), Achievement(exercise.getName(), set.getWeight(), set.getReps()) });
                    } else if (set.getWeight() > record->second.getMaxWeight()) {
                        record->second.updateRecord(set.getWeight(), set.getReps());
                    }
                }
            }
        }

        std::cout << " Average Calories: " << (int)avgCalories << " kcal / day" << std::endl;
        std::cout << " Target Calories: " << user.getDailyCaloricTarget() << " kcal" << std::endl;
        std::cout << " Total Workouts: " << workoutCount << std::endl;
        std::cout << " Weekly Records:" << std::endl;
        if (weeklyRecords.empty()) {
            std::cout << "  No workout records this week." << std::endl;
        } else {
            for (const auto& record : weeklyRecords) {
                std::cout << "  " << record.second.getExerciseName() << ": "
                          << record.second.getMaxWeight() << " kg x "
                          << record.second.getReps() << " reps" << std::endl;
            }
        }
        std::cout << "---------------------------------" << std::endl << std::endl;
    }
};

#endif
