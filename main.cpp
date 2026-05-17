#include <iostream>
#include "user.h"
#include "FoodProduct.h"
#include "Meal.h"
#include "foodlibrary.h"
#include "dailyTracker.h"
using namespace std;

int main() {
    User juli("Yuliyan Tsonchev", 'M', 173, 63, 16, 3, "Gain");
    FoodLibrary library;

    try {
        juli.displayProfile();
    } catch (const invalid_argument& e) {
        cout << "Error displaying profile: " << e.what() << endl;
    }

    try {
        library.createProduct(FoodProduct("Apple", 0.3, 14, 0.2));
        library.createProduct(FoodProduct("Bread", 8, 50, 1.5));
        library.createProduct(FoodProduct("Chicken Breast", 31, 0, 3.6));
        library.createProduct(FoodProduct("Rice", 2.7, 28, 0.3));
        library.createProduct(FoodProduct("Broccoli", 2.8, 7, 0.4));
        library.createProduct(FoodProduct("Potatoes", 2, 17, 0.1));
        library.createProduct(FoodProduct("Protein Shake", 20, 3, 1));

        library.updateProduct("Bread", 9, 48, 2);
        library.deleteProduct("Rice");
        
        // library.displayLibrary();
    } catch (const invalid_argument& e) {
        cout << "Library Error: " << e.what() << endl;
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
    return 0;
}