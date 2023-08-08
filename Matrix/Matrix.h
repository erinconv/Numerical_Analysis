
#ifndef MATRIX_STRUCT_H
#define MATRIX_STRUCT_H

#include <fstream> // for file access
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cmath> // For Absolute function
#include <vector>
#include <tuple>
#include <stdexcept>
#include <cstring>

template <class Type>
class Matrix
{

public:
    // Default constructor for a nxm matrix
    Matrix(const size_t rows, const size_t cols, std::vector<std::vector<Type>> mat);
    Matrix(const size_t rows, const size_t cols);
    Matrix();
    ~Matrix();

    // Setters

    // Getters
    void print(std::vector<std::vector<Type>> array);
    std::tuple<size_t, size_t> getDims();
    Matrix<Type> eye();
    Matrix<Type> transpose();
    Matrix<Type> zeros();

    void getSolution(Matrix<Type> &Vect);

    std::vector<std::vector<Type>> get_augmented(Matrix<Type> &Vect);
    std::vector<std::vector<Type>> get_array();
    // Setter for matrix dimensions

    Type &operator()(const size_t &row, const size_t &col);             // Accesing values in matrix object using parenthesis ()
    const Type &operator()(const size_t &row, const size_t &col) const; // Accesing values in matrix object using parenthesis ()
    Matrix<Type> operator+(const Matrix<Type> &Mat);                    // Sum two matrix
    Matrix<Type> operator-(const Matrix<Type> &Mat);                    // Subs two matrix
    Matrix<Type> operator*(const Matrix<Type> &Mat);                    // Multiplicate two matrix
    // Matrix<Type> augmented;

private:
    // Member variables
    const size_t _rows;                        // Number of rows
    const size_t _cols;                        // Number of columns
    std::vector<std::vector<Type>> _matrix;    // Coefficient matrix
    std::vector<std::vector<Type>> _augmented; // Coefficient matrix

    // Compute augmented
    void _compute_augmented(Matrix<Type> &Vect);

    // Create matrixes to store solutions and augmented matrix
    // Matrix<Type> _augmented_(const size_t rows, const size_t cols);
    // Matrix<Type> _solution(const size_t rows, const size_t cols);
    // Matrix<Type> _zeros();
    // Matrix<Type> _eye(const size_t rows, const size_t cols);
    // Matrix<Type> _transpose(const size_t rows, const size_t cols);
    // Allocate memory for arrays
    void Alloc();
    void Alloc_augmented();
    // Compute gaussian Elimination
    void gaussianElimination();
    void swapRows(size_t row1, size_t row2);
};

// This is here since this is a template class
#include "Matrix.cpp"
#endif