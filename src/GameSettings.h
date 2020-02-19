#ifndef GAME_OF_LIFE_GAMESETTINGS_H
#define GAME_OF_LIFE_GAMESETTINGS_H

#include <string>
#include <iostream>

struct GameSettings {
    bool doBenchmark = false;
    int generations = 0;
    int logFrequency = 0;
    int fieldWidth = 500;
    int fieldHeight = 500;
    int winWidth = 0;
    int winHeight = 0;
    std::string filename = "";
};

void readDimensionArg(const std::string& arg, int &width, int &height) {
    std::string delim = "x";
    auto pos = arg.find(delim);
    if (pos == std::string::npos) {
        throw std::invalid_argument("Dimension format is not valid: '" + arg + "'");
    }
    try {
        width = std::stoi(arg.substr(0, pos));
        height = std::stoi(arg.substr(pos + 1, arg.length()));
    } catch(const std::invalid_argument &ia) {
        throw std::invalid_argument("Failed to parse dimensions: '" + arg + "'");
    }
}

void readDimensionArg(int i, int argc, char **argv, int &width, int &height) {
    if (i >= argc) {
        throw std::invalid_argument("No value provided for parameter '" + std::string(argv[i - 1]) + "'");
    }
    readDimensionArg(std::string(argv[i]), width, height);
}

void readNumberArg(const std::string& arg, int &num) {
    try {
        num = std::stoi(arg);
    } catch(const std::invalid_argument &ia) {
        throw std::invalid_argument("Number is not valid: '" + arg + "'");
    }
}

void readNumberArg(int i, int argc, char **argv, int &num) {
    if (i >= argc) {
        throw std::invalid_argument("No value provided for parameter '" + std::string(argv[i - 1]) + "'");
    }
    readNumberArg(std::string(argv[i]), num);
}

GameSettings parseArgs(int argc, char **argv) {
    GameSettings settings;

    for (int i = 1; i < argc; ) {
        auto currentArg = std::string(argv[i]);
        std::string nextArg;

        if (currentArg == "--generations" || currentArg == "-g") {
            readNumberArg(++i, argc, argv, settings.generations);
        } else if (currentArg == "--fieldsize" || currentArg == "-f") {
            readDimensionArg(++i, argc, argv, settings.fieldWidth, settings.fieldHeight);
        } else if (currentArg == "--winsize" || currentArg == "-w") {
            readDimensionArg(++i, argc, argv, settings.winWidth, settings.winHeight);
        } else if (currentArg == "--benchmark" || currentArg == "-b") {
            settings.doBenchmark = true;
        } else if (currentArg == "--infile" || currentArg == "-i") {
            settings.filename = std::string(argv[++i]);
        } else if (currentArg == "--logfrequency" || currentArg == "-l") {
            readNumberArg(++i, argc, argv, settings.logFrequency);
        } else {
            throw std::invalid_argument("Parameter '" + currentArg + "' is not valid");
        }

        i++;
    }

    if (settings.filename.empty()) {
        throw std::invalid_argument("No input file provided");
    }
    if (!settings.doBenchmark && settings.winWidth < settings.fieldWidth) {
        std::cout << "Window width is too small or was not provided, setting to field width" << std::endl;
        settings.winWidth = settings.fieldWidth;
    }
    if (!settings.doBenchmark && settings.winHeight < settings.fieldHeight) {
        std::cout << "Window height is too small or was not provided, setting to field height" << std::endl;
        settings.winHeight = settings.fieldHeight;
    }
    if (settings.doBenchmark && settings.generations <= 0) {
        std::cout << "No valid generation count provided, using default (30000)" << std::endl;
        settings.generations = 30000;
    }
    if (settings.doBenchmark && settings.logFrequency <= 0) {
        std::cout << "No valid log frequency provided, using default (50)" << std::endl;
        settings.logFrequency = 50;
    }
    if (settings.doBenchmark && settings.generations % settings.logFrequency != 0) {
        std::cout << "Generation count is not a multiple of log frequency, some results will be lost" << std::endl;
    }

    return settings;
}


#endif //GAME_OF_LIFE_GAMESETTINGS_H
