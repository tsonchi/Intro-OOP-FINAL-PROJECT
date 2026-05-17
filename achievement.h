#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <string>

class Achievement {
private:
    std::string exerciseName;
    double maxWeight;
    int reps;

public:
    Achievement(std::string name, double weight, int reps) 
        : exerciseName(name), maxWeight(weight), reps(reps) {}

    std::string getExerciseName() const { return exerciseName; }
    double getMaxWeight() const { return maxWeight; }
    int getReps() const { return reps; }

    void updateRecord(double newWeight, int newReps) {
        maxWeight = newWeight;
        reps = newReps;
    }
};

#endif