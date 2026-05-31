#include <iostream>
#include "User.h"
#include "FoodProduct.h"
#include "Meal.h"
#include "FoodLibrary.h"
#include "DailyTracker.h"
#include "Exercise.h"
#include "WorkoutSession.h"
#include "ReportGenerator.h"
#include "InventoryItem.h"
#include "ExerciseLibrary.h"

using namespace std;

int main() {
    User juli("Yuliyan Tsonchev", 'M', 173, 63, 16, 3, "Gain");
    FoodLibrary library;
    ExerciseLibrary exLibrary;
    try {
        juli.displayProfile();
    } catch (const invalid_argument& e) {
        cout << "Error displaying profile: " << e.what() << endl;
    }

    try {
        library.createProduct(BasicFoodProduct("Apple", 0.3, 14, 0.2));
        library.createProduct(BasicFoodProduct("Bread", 8, 50, 1.5));
        library.createProduct(BasicFoodProduct("Chicken Breast", 31, 0, 3.6));
        library.createProduct(BasicFoodProduct("Rice", 2.7, 28, 0.3));
        library.createProduct(BasicFoodProduct("Broccoli", 2.8, 7, 0.4));
        library.createProduct(BasicFoodProduct("Potatoes", 2, 17, 0.1));
        library.createProduct(BasicFoodProduct("Protein Shake", 20, 3, 1));
        library.createProduct(BasicFoodProduct("Oats", 13, 68, 7));
        library.createProduct(BasicFoodProduct("Eggs", 13, 1.1, 11));
        library.createProduct(BasicFoodProduct("Greek Yogurt", 10, 3.6, 0.4));
        library.createProduct(BasicFoodProduct("Salmon", 20, 0, 13));

        library.updateProduct("Bread", 9, 48, 2);
        library.deleteProduct("Rice");
    } catch (const invalid_argument& e) {
        cout << "Library Error: " << e.what() << endl;
    }
    

    try {
        exLibrary.addExerciseToLibrary(Exercise("Bench Press", "Chest"));
        exLibrary.addExerciseToLibrary(Exercise("Overhead Press", "Shoulders"));
        exLibrary.addExerciseToLibrary(Exercise("Squat", "Legs"));
        exLibrary.addExerciseToLibrary(Exercise("Deadlift", "Back"));
        exLibrary.addExerciseToLibrary(Exercise("Barbell Row", "Back"));
    } catch (const invalid_argument& e) {
        cout << "Exercise Library Error: " << e.what() << endl;
    }

    try {
        DailyTracker today("2026-17-05");

        Meal breakfast("Breakfast");
        breakfast.addProduct(library.readProduct("Apple"), 150);
        breakfast.addProduct(library.readProduct("Bread"), 100);
        breakfast.displayMeal();
        today.addMeal(breakfast);

        Meal lunch("Lunch");
        lunch.addProduct(library.readProduct("Chicken Breast"), 200);   
        lunch.displayMeal();
        today.addMeal(lunch);

        InventoryItem creatine("Creatine", 0, 0, 0, 30, 5);
        juli.addSupplement(creatine);
        juli.consumeSupplement("Creatine");
        InventoryItem proteinPowder("Protein Powder", 80, 5, 3, 60, 30);
        juli.addSupplement(proteinPowder);

        Meal dinner("Dinner");
        dinner.addProduct(library.readProduct("Broccoli"), 100);
        dinner.addProduct(library.readProduct("Potatoes"), 200);
        dinner.displayMeal();
        today.addMeal(dinner);

        juli.addDailyRecord(today);

        DailyTracker outsideWeek("2026-24-05");

        Meal outsideBreakfast("Breakfast");
        outsideBreakfast.addProduct(library.readProduct("Greek Yogurt"), 250);
        outsideBreakfast.addProduct(library.readProduct("Oats"), 60);
        outsideBreakfast.displayMeal();
        outsideWeek.addMeal(outsideBreakfast);

        Meal outsideDinner("Dinner");
        outsideDinner.addProduct(library.readProduct("Salmon"), 200);
        outsideDinner.addProduct(library.readProduct("Broccoli"), 150);
        outsideDinner.displayMeal();
        outsideWeek.addMeal(outsideDinner);

        juli.addDailyRecord(outsideWeek);

    } catch (const invalid_argument& e) {
        cout << "Tracker Error: " << e.what() << endl;
    }

    try {
        WorkoutSession oldWorkout("Old Bench Day", "2026-10-05");
        Exercise oldBench = exLibrary.getExerciseFromLibrary("Bench Press");
        oldBench.addSet(Set(20, 12, true));
        oldBench.addSet(Set(80, 5));
        oldBench.addSet(Set(90, 3));
        oldWorkout.addExercise(oldBench);
        juli.addWorkoutRecord(oldWorkout);

        WorkoutSession pullDay("Pull Day", "2026-20-05");
        Exercise deadlift = exLibrary.getExerciseFromLibrary("Deadlift");
        deadlift.addSet(Set(60, 8, true));
        deadlift.addSet(Set(100, 5));
        deadlift.addSet(Set(120, 3));

        Exercise row = exLibrary.getExerciseFromLibrary("Barbell Row");
        row.addSet(Set(40, 10));
        row.addSet(Set(55, 8));

        pullDay.addExercise(deadlift);
        pullDay.addExercise(row);
        juli.addWorkoutRecord(pullDay);

    } catch (const invalid_argument& e) {
        cout << "Workout Error (Manual): " << e.what() << endl;
    }

    try {
        // This will call your custom operator>> under the hood multiple times
        std::vector<WorkoutSession> savedSessions = WorkoutSession::readFromFile("workouts.txt");
        
        cout << "Successfully parsed " << savedSessions.size() << " sessions from file.\n" << endl;
        
        for (const auto& session : savedSessions) {
            session.displayWorkout();
            // Optional: Feed them into your user object to check integration
            juli.addWorkoutRecord(session);
        }

    } catch (const invalid_argument& e) {
        cout << "File Parser Error: " << e.what() << endl;
    }

    juli.displayDailyReport("2026-17-05");
    juli.displayDailyReport("2026-24-05");

    cout << "\n--- Generating Final Weekly Report ---" << endl;
    ReportGenerator::generateWeeklyReport(juli, juli.getNutritionHistory(), juli.getWorkoutHistory(), "2026-17-05", "2026-23-05");

    return 0;
}
