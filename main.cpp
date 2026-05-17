#include <iostream>
#include "user.h"
#include "FoodProduct.h"
#include "Meal.h"
#include "foodlibrary.h"
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
        
        library.updateProduct("Bread", 9, 48, 2);
        library.deleteProduct("Rice");
        
        library.displayLibrary();
    } catch (const invalid_argument& e) {
        cout << "Library Error: " << e.what() << endl;
    }

    try {
        Meal breakfast("Breakfast");
        breakfast.addProduct(library.readProduct("Apple"), 150);
        breakfast.addProduct(library.readProduct("Bread"), 100);
        breakfast.displayMeal();

        Meal lunch("Lunch");
        lunch.addProduct(library.readProduct("Chicken Breast"), 150);   
        lunch.displayMeal();
        
    } catch (const invalid_argument& e) {
        cout << "Meal Tracker Error: " << e.what() << endl;
    }

    return 0;
}