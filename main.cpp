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
    //     WorkoutSession pushDay("Push Day", "2026-17-05");

    //     Exercise benchPress = exLibrary.getExerciseFromLibrary("Bench Press");
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
    //     juli.addWorkoutRecord(pushDay);
    //     juli.displayWorkoutReport("2026-17-05");

    //     InventoryItem whey("Whey Protein", 80, 5, 3, 60, 30);
    //     whey.consumeDose();

    //     Meal shake("Post-Workout Shake");
    //     shake.addProduct(whey, whey.getDoseSizeGrams());

    // } catch (const invalid_argument& e) {
    //     cout << "Workout Error (Day 1): " << e.what() << endl;
    // }

    // try {
    //     WorkoutSession legDay("Leg Day", "2026-18-05");
        
    //     Exercise squat = exLibrary.getExerciseFromLibrary("Squat");
    //     squat.addSet(Set(30, 15, true));
    //     squat.addSet(Set(60, 10, true));
    //     squat.addSet(Set(90, 8));
    //     squat.addSet(Set(100, 6));
        
    //     legDay.addExercise(squat);
    //     juli.addWorkoutRecord(legDay);
    //     juli.displayWorkoutReport("2026-18-05");

    // } catch (const invalid_argument& e) {
    //     cout << "Workout Error (Day 2): " << e.what() << endl;
    // }

    // try {
    //     WorkoutSession pushDay2("Push Day 2", "2026-19-05");
        
    //     Exercise benchPress2 = exLibrary.getExerciseFromLibrary("Bench Press");
    //     benchPress2.addSet(Set(20, 15, true)); 
    //     benchPress2.addSet(Set(40, 10, true)); 
    //     benchPress2.addSet(Set(70, 8));  
    //     benchPress2.addSet(Set(75, 6));  
        
    //     pushDay2.addExercise(benchPress2);
    //     juli.addWorkoutRecord(pushDay2);
    //     juli.displayWorkoutReport("2026-19-05");

    // } catch (const invalid_argument& e) {
    //     cout << "Workout Error (Day 3): " << e.what() << endl;
    // }

    //ReportGenerator::generateWeeklyReport(juli, juli.getNutritionHistory(), juli.getWorkoutHistory());
// ... (Keep your previous user, library, and daily tracker setup here) ...

    try {
        cout << "\n--- Testing Manual Workout Creation ---" << endl;
        WorkoutSession pushDay("Push Day", "2026-17-05");

        Exercise benchPress = exLibrary.getExerciseFromLibrary("Bench Press");
        // Note: Assuming your Set constructor accepts (weight, reps, isWarmup)
        benchPress.addSet(Set(20, 15, true)); 
        benchPress.addSet(Set(40, 10, true)); 
        benchPress.addSet(Set(60, 8));  
        benchPress.addSet(Set(65, 6));  

        Exercise overheadPress = exLibrary.getExerciseFromLibrary("Overhead Press");
        overheadPress.addSet(Set(15, 12, true));
        overheadPress.addSet(Set(30, 10, true));
        overheadPress.addSet(Set(45, 8));
        overheadPress.addSet(Set(50, 6));
        
        pushDay.addExercise(overheadPress);
        pushDay.addExercise(benchPress);
        
        // Display to check if manual object generation works
        pushDay.displayWorkout();
        
        juli.addWorkoutRecord(pushDay);

    } catch (const invalid_argument& e) {
        cout << "Workout Error (Manual): " << e.what() << endl;
    }

    try {
        cout << "\n--- Testing File Parsing Logic (readFromFile) ---" << endl;
        
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