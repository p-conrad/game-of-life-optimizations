#ifndef GAME_OF_LIFE_RLE_H
#define GAME_OF_LIFE_RLE_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Pattern.h"
#include "accessors.h"

void readDimensions(std::string line, int &columns, int &rows) {
    // remove spaces first to improve resiliency
    line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
    // dimensions are in the format 'x = 10, y = 10, rule= ...'
    auto firstComma = line.find(',');
    auto secondComma = line.substr(firstComma + 1).find(',');
    columns = std::stoi(line.substr(2, firstComma)); // ex: x=10
    rows = std::stoi(line.substr(firstComma + 3, secondComma)); // ex: ,y=10
    // TODO: maybe parse the rules and check if they are compatible?
}

void readData(std::vector<uint_fast8_t> &data, std::string &line, int columns, int rows, int &y, int &x) {
    size_t cursorStart = 0;
    size_t cursorEnd = 0;
    int count = 1;

    // remove possible line endings
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());

    // read until the end of line or the terminating '!'
    while (cursorStart < line.length() && line.at(cursorStart) != '!') {
        // case 1: a '$' symbol indicates the next row
        if (line.at(cursorStart) == '$') {
            cursorStart++;
            x = 0;
            y = y + 1;
            continue;
        }

        // case 2: the cursor points at a digit - move cursorEnd until the number is fully enclosed
        if (isdigit(line.at(cursorStart))) {
            cursorEnd = cursorStart + 1;
            while (isdigit(line.at(cursorEnd))) {
                cursorEnd++;
            }

            // the enclosed number is our amount of repetitions
            count = std::stoi(line.substr(cursorStart, cursorEnd));

            // cursorEnd should now point at a letter indicating the state of the cell
            // 'b' indicates a dead cell, 'o' is a living cell
            // we take a shortcut by assuming those two are the only possible values here
            uint_fast8_t cellState = line.at(cursorEnd) == 'b' ? 0u : 1u;

            for (int n = 0; n < count; n++) {
                set(data, columns, y, x + n, cellState);
            }

            // move x and cursorStart forward
            x += count;
            cursorStart = cursorEnd + 1;
            continue;
        }

        // case 3: the cursor points at a letter - this is much easier than the digit case
        if (isalpha(line.at(cursorStart))) {
            uint_fast8_t cellState = line.at(cursorStart) == 'b' ? 0u : 1u;
            set(data, columns, y, x, cellState);
            x++;
            cursorStart++;
            continue;
        }

        // only an ill-formatted input file should get us to this point
        // issue a warning and advance the cursor to prevent infinite loops
        std::cout << "Failed to read symbol '" << line.at(cursorStart) << "'\n";
        cursorStart++;
    }
}

Pattern readRLE(const std::string &filename) {
    std::ifstream infile(filename);

    if (!infile.is_open()) {
        std::cout << "Failed to read input file" << std::endl;
        return Pattern(0, 0, {});
    }

    std::string line;
    int columns = 0, rows = 0, y = 0, x = 0;
    std::vector<uint_fast8_t> data;
    while (getline(infile, line)) {
        // first few lines may be comments, we simply ignore those
        if (line.substr(0, 1) == "#") continue;

        // the first non-comment should contain the dimensions and rules separated by comma
        if (line.substr(0, 1) == "x") {
            readDimensions(line, columns, rows);
            data = std::vector<uint_fast8_t>(columns * rows);
            continue;
        }

        // finally, we should have arrived at our data
        // those might span multiple lines so we need to keep track of the row and column we are currently at
        // it appears reasonable to assume that numbers don't appear at the end of any line
        readData(data, line, columns, rows, y, x);
    }

    return Pattern(rows, columns, data);
}

#endif //GAME_OF_LIFE_RLE_H
