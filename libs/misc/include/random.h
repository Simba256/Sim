#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include <random>

class RandomNumberGenerator {
public:
    RandomNumberGenerator();
    int generateInt(int min, int max);
    float generateFloat(float min, float max);

private:
    std::mt19937 m_RandomEngine;
};

#endif // RANDOM_NUMBER_GENERATOR_H
