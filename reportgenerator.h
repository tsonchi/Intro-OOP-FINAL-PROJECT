#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "User.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

class ReportGenerator {
public:
    static void generateWeeklyReport(const User& user, const std::vector<DailyTracker>& nutrition, const std::vector<WorkoutSession>& workouts) {
        std::cout << "--- WEEKLY REPORT FOR " << user.getName() << " ---" << std::endl;

        double totalCal = 0;
        size_t nutritionDays = (nutrition.size() > 7) ? 7 : nutrition.size();
        
        for (size_t i = nutrition.size() - nutritionDays; i < nutrition.size(); ++i) {
            totalCal += nutrition[i].getTotalCaloriesEaten();
        }
        
        double avgCalories = (nutritionDays > 0) ? (totalCal / nutritionDays) : 0;
        size_t workoutDays = (workouts.size() > 7) ? 7 : workouts.size();
        std::map<std::string, Achievement> weeklyRecords;

        for (size_t i = workouts.size() - workoutDays; i < workouts.size(); ++i) {
            for (const auto& exercise : workouts[i].getExercises()) {
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
        std::cout << " Total Workouts: " << workoutDays << std::endl;
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
