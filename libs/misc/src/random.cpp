#include "random.h"

RandomNumberGenerator::RandomNumberGenerator() : m_RandomEngine(std::random_device()()) {}

int RandomNumberGenerator::generateInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(m_RandomEngine);
}

float RandomNumberGenerator::generateFloat(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(m_RandomEngine);
}
