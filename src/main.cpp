#include <iostream>
#include "Parameters.hpp"
#include "Benchmark.hpp"

int main(int argc, char** argv) {
    if (Parameters::readParameters(argc - 1, argv + 1) != 0) {
        std::cerr << "\nError. Parsing arguments failed. Use -h, for help.\n";
        return -1;
    }

    if (Parameters::runMode == Parameters::RunModes::help) {
        Parameters::help();
        return 0;
    }

    if (Parameters::runMode == Parameters::RunModes::benchmark) {
        std::cout << "\n=== BENCHMARK ===\n";
        Parameters::printParameters();

        Benchmark::execute();
    }

    return 0;
}