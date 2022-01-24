#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>

template<typename T>
class Matrix {
private:
    int numRows;
    int numColumns;
    std::vector<T> ** rows;
public:
    Matrix() : numRows(0), numColumns(0), rows(NULL){
    }
    Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T>*[numRows]) {
        for (int i = 0; i < numRows; i++) {
            rows[i] = new std::vector<T>(numColumns);
        }
    }
    Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new std::vector<T>*[rhs.numRows]) {  // why parameter no T?
        for (int i = 0; i < numRows; i++) {
            rows[i] = new std::vector<T>(rhs[i]);
        }
    }
    ~Matrix() {
        for (int i = 0; i < numRows; i++) {
            delete rows[i];
        }
        delete[] rows;
    }
    Matrix & operator=(const Matrix & rhs) {
        if (this != &rhs) {
            std::vector<T> ** temp = new std::vector<T>*[rhs.numRows];
            for (int i = 0; i < rhs.numRows; i++) {  // must use rhs.numRows instead of numRows
                temp[i] = new std::vector<T>(rhs[i]);
            }
            // free the original memory
            for (int i = 0; i < numRows; i++) {
                delete rows[i];
            }
            delete[] rows;
            rows = temp;
            numRows = rhs.numRows;
            numColumns = rhs.numColumns;
        }
        return *this;
    }
    int getRows() const {
        return numRows;
    }
    int getColumns() const {
        return numColumns;
    }
    const std::vector<T> & operator[](int index) const {
        assert(index >= 0 && index < numRows);
        return *rows[index];
    }
    std::vector<T> & operator[](int index) {
        assert(index >= 0 && index < numRows);
        return *rows[index];
    }
    bool operator==(const Matrix & rhs) const {
        if (numRows != rhs.numRows) {
            return false;
        }
        if (numColumns != rhs.numColumns) {
            return false;
        }
        for (int i = 0; i < numRows; i++) {
            if ((*this)[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }
    Matrix operator+(const Matrix & rhs) const {
        assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
        Matrix temp(numRows, numColumns);
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numColumns; j++) {
                temp[i][j] = (*this)[i][j] + rhs[i][j];
            }
        }
        return temp;
    }
};

// Matrix<T> << overload
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
    s << "[ ";
    for (int i = 0; i < rhs.getRows(); i++) {
        s << rhs[i];
        if (i != rhs.getRows() - 1) {
            s << ",\n";
        }
    }
    s << " ]";
    return s;
}

// vector<T> << overload
template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
    s << "{";
    for (size_t i = 0; i < rhs.size(); i++) {
        s << rhs[i];
        if (i != rhs.size()-1) {
            s << ", ";
        }
    }
    s << "}";
    return s;
}



#endif
