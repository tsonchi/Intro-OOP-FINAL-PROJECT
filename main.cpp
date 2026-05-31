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
#include "SupplementLibrary.h"

using namespace std;

int main() {
    User juli("Yuliyan Tsonchev", 'M', 173, 63, 16, 3, "Gain");
    FoodLibrary library;
    ExerciseLibrary exLibrary;
    SupplementLibrary supLibrary;

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

        library.updateProduct("Bread", 9, 48, 2);
        library.deleteProduct("Rice");
    } catch (const invalid_argument& e) {
        cout << "Library Error: " << e.what() << endl;
    }
    try{
        supLibrary.createProduct(TrainingFoodProduct("Creatine", 0, 0, 0, 30));
        supLibrary.createProduct(TrainingFoodProduct("Protein Powder", 80, 5, 3, 60));
    } catch (const invalid_argument& e) {
        cout << "Supplement Library Error: " << e.what() << endl;
    }

    try {
        exLibrary.addExerciseToLibrary(Exercise("Bench Press", "Chest"));
        exLibrary.addExerciseToLibrary(Exercise("Overhead Press", "Shoulders"));
        exLibrary.addExerciseToLibrary(Exercise("Squat", "Legs"));
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
        juli.displayDailyReport("2026-17-05");

    } catch (const invalid_argument& e) {
        cout << "Tracker Error: " << e.what() << endl;
    }

        


    // try {
    //     cout << "\n--- Testing Manual Workout Creation ---" << endl;
    //     WorkoutSession pushDay("Push Day", "2026-17-05");

    //     Exercise benchPress = exLibrary.getExerciseFromLibrary("Bench Press");
    //     // Note: Assuming your Set constructor accepts (weight, reps, isWarmup)
    //     benchPress.addSet(Set(20, 15, true)); 
    //     benchPress.addSet(Set(40, 10, true)); 
    //     benchPress.addSet(Set(60, 8));  
    //     benchPress.addSet(Set(65, 6));  

    //     Exercise overheadPress = exLibrary.getExerciseFromLibrary("Overhead Press");
    //     overheadPress.addSet(Set(15, 12, true));
    //     overheadPress.addSet(Set(30, 10, true));
    //     overheadPress.addSet(Set(45, 8));
    //     overheadPress.addSet(Set(50, 6));
        
    //     pushDay.addExercise(overheadPress);
    //     pushDay.addExercise(benchPress);
        
    //     // Display to check if manual object generation works
    //     pushDay.displayWorkout();
        
    //     juli.addWorkoutRecord(pushDay);

    // } catch (const invalid_argument& e) {
    //     cout << "Workout Error (Manual): " << e.what() << endl;
    // }

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

    cout << "\n--- Generating Final Weekly Report ---" << endl;
    ReportGenerator::generateWeeklyReport(juli, juli.getNutritionHistory(), juli.getWorkoutHistory());

    return 0;
}
