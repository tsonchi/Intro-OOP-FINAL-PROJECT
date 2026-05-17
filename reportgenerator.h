#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "User.h"
#include <iostream>
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
        size_t workoutCount = workouts.size();

        std::cout << " Average Calories: " << (int)avgCalories << " kcal / day" << std::endl;
        std::cout << " Target Calories: " << user.getDailyCaloricTarget() << " kcal" << std::endl;
        std::cout << " Total Workouts: " << workoutCount << std::endl;
        std::cout << "---------------------------------" << std::endl << std::endl;
    }
};

#endif