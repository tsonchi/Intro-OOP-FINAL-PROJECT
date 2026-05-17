#ifndef SET_H
#define SET_H

#include <stdexcept>

class Set {
private:
    double weight;
    int reps;
    bool isWarmup; // Новата променлива

public:
    // Конструктор с параметър по подразбиране за isWarmup
    Set(double weight, int reps, bool isWarmup = false) {
        if (weight < 0 || reps <= 0) {
            throw std::invalid_argument("Weight cannot be negative and reps must be positive.");
        }
        this->weight = weight;
        this->reps = reps;
        this->isWarmup = isWarmup;
    }

    double getWeight() const { return weight; }
    int getReps() const { return reps; }
    bool getIsWarmup() const { return isWarmup; } // Гетър за проверка
};

#endif