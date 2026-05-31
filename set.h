#ifndef SET_H
#define SET_H

#include <ios>
#include <istream>
#include <stdexcept>

class Set {
private:
    double weight;
    int reps;
    bool isWarmup;

public:
    Set() : weight(0), reps(1), isWarmup(false) {}

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
    bool getIsWarmup() const { return isWarmup; }

    friend std::istream& operator>>(std::istream& in, Set& set) {
        double parsedWeight;
        int parsedReps;
        char separator;

        in >> parsedWeight >> separator >> parsedReps;
        if (!in) return in;

        if (separator != 'x' && separator != 'X') {
            in.setstate(std::ios::failbit);
            return in;
        }
        if (parsedWeight < 0 || parsedReps <= 0) {
            in.setstate(std::ios::failbit);
            return in;
        }

        set.weight = parsedWeight;
        set.reps = parsedReps;
        set.isWarmup = false;
        return in;
    }
};

#endif
