#include <iostream>
#include "Parameters.hpp"
#include "Benchmark.hpp"

int main(int argc, char** argv) {
    if (Parameters::readParameters(argc - 1, argv + 1) != 0) {
        std::cerr << "\nError. Parsing arguments failed. Use -h, for help.\n";
        return -1;
    }

    switch (Parameters::runMode) {
        case Parameters::RunModes::help:
            Parameters::help();
            break;

        case Parameters::RunModes::benchmark:
            std::cout << "\n=== BENCHMARK ===\n";
            Parameters::printParameters();
            Benchmark::execute();
            break;

        case Parameters::RunModes::singleFile:
            std::cout << "\n=== SINGLE FILE MODE ===\n";
            Parameters::printParameters();
            Benchmark::execute();
            break;

        default:
            std::cerr << "\nError: No run mode specified! Use -h for help.\n";
            return -1;
    }

    return 0;
}