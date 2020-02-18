#ifndef GAME_OF_LIFE_GAMESETTINGS_H
#define GAME_OF_LIFE_GAMESETTINGS_H

#include <string>
#include <iostream>

struct GameSettings {
    bool doBenchmark = false;
    int generations = -1;
    int fieldWidth = 500;
    int fieldHeight = 500;
    int winWidth = 0;
    int winHeight = 0;
    std::string filename = "";
};

GameSettings parseArgs(int argc, char **argv) {
    GameSettings settings;

    for (int i = 1; i < argc; ) {
        auto currentArg = std::string(argv[i]);
        std::string nextArg;

        if (currentArg == "--generations" || currentArg == "-g") {
            i++;
            nextArg = std::string(argv[i]);
            settings.generations = std::stoi(nextArg);
            break;
        } else if (currentArg == "--fieldsize" || currentArg == "-f") {
            i++;
            nextArg = std::string(argv[i]);
            std::string delim = "x";
            auto pos = nextArg.find(delim);
            settings.fieldWidth = std::stoi(nextArg.substr(0, pos));
            settings.fieldHeight = std::stoi(nextArg.substr(pos + 1, nextArg.length()));
        } else if (currentArg == "--winsize" || currentArg == "-w") {
            i++;
            nextArg = std::string(argv[i]);
            std::string delim = "x";
            auto pos = nextArg.find(delim);
            settings.winWidth = std::stoi(nextArg.substr(0, pos));
            settings.winHeight = std::stoi(nextArg.substr(pos + 1, nextArg.length()));
        } else if (currentArg == "--benchmark" || currentArg == "-b") {
            settings.doBenchmark = true;
        } else if (currentArg == "--infile" || currentArg == "-i") {
            i++;
            nextArg = std::string(argv[i]);
            settings.filename = nextArg;
        } else {
            std::cout << "Warning: parameter " << currentArg << " was not understood" << std::endl;
        }

        i++;
    }

    if (settings.winWidth < settings.fieldWidth && !settings.doBenchmark) {
        std::cout << "Setting window width to the field width" << std::endl;
        settings.winWidth = settings.fieldWidth;
    }
    if (settings.winHeight < settings.fieldHeight && !settings.doBenchmark) {
        std::cout << "Setting window height to the field height" << std::endl;
        settings.winHeight = settings.fieldHeight;
    }
    if (settings.doBenchmark && settings.generations <= 0) {
        std::cout << "Must specify a generation count to do benchmarks. Using default value (30000)" << std::endl;
        settings.generations = 30000;
    }

    return settings;
}


#endif //GAME_OF_LIFE_GAMESETTINGS_H
