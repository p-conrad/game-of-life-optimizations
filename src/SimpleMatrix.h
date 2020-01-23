#ifndef GAME_OF_LIFE_SIMPLEMATRIX_H
#define GAME_OF_LIFE_SIMPLEMATRIX_H


#include <cstdlib>
#include <vector>

template<typename T>
class SimpleMatrix {
public:
    SimpleMatrix(const size_t rows, const size_t columns) :
            rows(rows),
            columns(columns),
            elements(rows * columns) {}

    SimpleMatrix(const size_t rows, const size_t columns, T value) :
            rows(rows),
            columns(columns),
            elements(rows * columns, value) {}

    virtual ~SimpleMatrix() {
        // TODO: does std::vector need to be deleted explicitly?
        elements.clear();
        delete &elements;
    }

    T operator()(size_t y, size_t x) {
        return getElementAt(y, x);
    }

    size_t getRows() {
        return rows;
    }

    size_t getColumns() {
        return columns;
    }

    T getElementAt(size_t y, size_t x) {
        return elements[(y * columns) + x];
    }

    void setElementAt(size_t y, size_t x, T value) {
        elements[(y * columns) + x] = value;
    }

private:
    size_t rows;
    size_t columns;
    std::vector<T> elements;
};


#endif //GAME_OF_LIFE_SIMPLEMATRIX_H
