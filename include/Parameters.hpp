#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>

namespace Parameters
{
    enum class RunModes {
        undefined = -1,
        singleFile = 0,
        benchmark,
        help
      };

    enum class Algorithms {
        undefined = -1,
        bubble = 0,
        cocktail,
        merge,
        insertion,
        quick,
        shell,

        count
      };

    enum class Structures {
        undefined = -1,
        array = 0,
        singleList,
        doubleList,
        queue,
        stack,
        binaryTree,

        count
      };

    enum class DataTypes {
        undefined = -1,
        typeInt = 0,
        typeFloat,
        typeDouble,
        typeChar,
        typeString,
        typeUnsignedLong,
        typeUnsignedChar,

        count
      };

    enum class Pivots {
        undefined = -1,
        random = 0,
        left,
        right,
        middle,

        count
      };

    enum class ShellParameters {
        undefined = -1,
        option1 = 0,
        option2,
        option3,
        option4,

        count
      };

    //
    // Parameters to use.
    //

    RunModes runMode = RunModes::undefined;
    Algorithms algorithm = Algorithms::undefined;
    Structures structure = Structures::undefined;
    DataTypes dataType = DataTypes::undefined;

    std::string inputFile = {};
    std::string outputFile = {};
    std::string resultsFile = {};

    int structureSize = -1;
    int iterations = -1;

    Pivots pivot = Pivots::undefined;
    ShellParameters shellParameter = ShellParameters::undefined;

    //
    // Methods to use.
    //

    int readParameters(int argc, char **argv);
    void printParameters();

    void enableDebug();
    void disableDebug();

    void help();
};

#endif
