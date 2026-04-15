#ifndef DATAGENERATOR_HPP
#define DATAGENERATOR_HPP

#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>

namespace DataGenerator {

    enum class Distribution {
        RANDOM,
        ASCENDING,
        DESCENDING,
        HALF_SORTED
    };

    inline std::mt19937& getEngine() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    template<typename T>
    T generateSingle() {
        static_assert(sizeof(T) == 0, "Unsupported type!");
        return T();
    }

    template<>
        inline int generateSingle<int>() {
        std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        return dist(getEngine());
    }

    template<>
    inline float generateSingle<float>() {
        std::uniform_real_distribution<float> dist(-100000.0f, 100000.0f);
        return dist(getEngine());
    }

    template<>
    inline double generateSingle<double>() {
        std::uniform_real_distribution<double> dist(-1000000.0, 1000000.0);
        return dist(getEngine());
    }

    template<>
    inline unsigned int generateSingle<unsigned int>() {
        std::uniform_int_distribution<unsigned int> dist(std::numeric_limits<unsigned int>::min(), std::numeric_limits<unsigned int>::max());
        return dist(getEngine());
    }

    template<>
    inline unsigned long generateSingle<unsigned long>() {
        std::uniform_int_distribution<unsigned long> dist(std::numeric_limits<unsigned long>::min(), std::numeric_limits<unsigned long>::max());
        return dist(getEngine());
    }

    template<>
    inline unsigned char generateSingle<unsigned char>() {
        std::uniform_int_distribution<int> dist(33, 126);
        return static_cast<unsigned char>(dist(getEngine()));
    }

    template<>
    inline char generateSingle<char>() {
        std::uniform_int_distribution<int> dist(33, 126);
        return static_cast<char>(dist(getEngine()));
    }

    template<>
    inline std::string generateSingle<std::string>() {
        // Random string length
        std::uniform_int_distribution<int> lengthDist(5, 12);
        // Printable
        std::uniform_int_distribution<int> charDist(33, 126);

        int len = lengthDist(getEngine());
        std::string result;
        result.reserve(len);

        for (int i = 0; i < len; ++i) {
            result.push_back(static_cast<char>(charDist(getEngine())));
        }

        return result;
    }

    template <typename Container, typename T>
    void populate(Container& container, int size, Distribution dist = Distribution::RANDOM) {
        std::vector<T> temp;
        temp.reserve(size);

        for (int i = 0; i < size; ++i) {
            temp.push_back(generateSingle<T>());
        }

        if (dist == Distribution::ASCENDING) {
            std::sort(temp.begin(), temp.end());
        }
        else if (dist == Distribution::DESCENDING) {
            std::sort(temp.begin(), temp.end(), std::greater<T>());
        }
        else if (dist == Distribution::HALF_SORTED) {
            std::sort(temp.begin(), temp.begin() + (size / 2));
        }

        for (int i = 0; i < size; ++i) {
            container.append(temp[i]);
        }
    }
}

#endif // DATAGENERATOR_HPP