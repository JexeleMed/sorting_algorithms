#ifndef DATAGENERATOR_HPP
#define DATAGENERATOR_HPP

#include <random>
#include <type_traits>
#include <limits>
#include <string>

namespace DataGenerator {

    // Mersenne Twister
    inline std::mt19937& getEngine() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    // Throws error when type is not handled
    template<typename T>
    T generateRandom() {
        static_assert(sizeof(T) == 0, "Type not handled!");
        return T();
    }

    // int
    template<>
    inline int generateRandom<int>() {
        std::uniform_int_distribution<int> dist(1, 100000);
        return dist(getEngine());
    }

    // float
    template<>
    inline float generateRandom<float>() {
        std::uniform_real_distribution<float> dist(1.0f, 100000.0f);
        return dist(getEngine());
    }

    // char (ASCI)
    template<>
    inline char generateRandom<char>() {
        std::uniform_int_distribution<int> dist(33, 126);
        return static_cast<char>(dist(getEngine()));
    }

    // double
    template<>
    inline double generateRandom<double>() {
        std::uniform_real_distribution<double> dist(1.0, 100000.0);
        return dist(getEngine());
    }
}

#endif // DATAGENERATOR_HPP