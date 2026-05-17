#include <iostream>
#include "user.h"
#include "FoodProduct.h"
#include "Meal.h"
using namespace std;

int main() {
    // try {
    //     User user("Ivan Ivanov", 'M', 180, 75, 30, 4, "Gain");
    //     user.displayProfile();
    // } catch (const invalid_argument& e) {
    //     cout << "Error: " << e.what() << endl;
    // }
    
    // try {
    //     User invalidUser("Sigma", 's', 170, 0, -5, 10, "Invalid Goal");
    // } catch (const invalid_argument& e) {
    //     cout << "Error: " << e.what() << endl;
    // }
    
    try {
        User juli("Yuliyan Tsonchev", 'M', 173, 63, 16, 3, "Gain");
        juli.displayProfile();
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
    try{
        FoodProduct apple("Apple", 0.3, 14, 0.2);
        FoodProduct bread("Bread", 8, 50, 1.5);
        Meal breakfast("Breakfast");
        breakfast.addProduct(apple, 150);
        breakfast.addProduct(bread, 100);
        breakfast.displayMeal();
        Meal lunch("Lunch");
        lunch.displayMeal();
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}