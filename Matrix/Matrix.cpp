#ifndef MATRIX_STRUCT_CPP
#define MATRIX_STRUCT_CPP
#include "Matrix.h"

template <class Type>
Matrix<Type>::Matrix(const size_t rows, const size_t cols, std::vector<std::vector<Type>> mat) : _rows(rows), _cols(cols), _matrix(mat)
{
}
template <class Type>
Matrix<Type>::Matrix(const size_t rows, const size_t cols) : _rows(rows), _cols(cols)
{
    std::vector<Type> v(cols, 0);
    std::vector<std::vector<Type>> mat(rows, v);
    this->_matrix.swap(mat);
}

template <class Type>
Matrix<Type>::Matrix()
{
}

template <class Type>
Matrix<Type>::~Matrix()
{
}

template <class Type>
std::tuple<size_t, size_t> Matrix<Type>::getDims()
{
    auto dims = std::make_tuple(this->_rows, this->_cols);
    return std::make_tuple(this->_rows, this->_cols);
}

template <class Type>
std::vector<std::vector<Type>> Matrix<Type>::get_array()
{
    return this->_matrix;
}

template <class Type>
Matrix<Type> Matrix<Type>::eye()
{
    Matrix<Type> identity(this->_rows, this->_cols);
    identity.Alloc();
    if (this->_cols == 1)
    {
        std::cerr << "Vectors have no identity matrix" << '\n';
        throw;
    }
    else if (this->_rows != this->_cols)
    {
        std::cerr << "You must input a square matrix to compute the identity" << '\n';
        throw;
    }
    else
    {
        for (size_t i = 0; i < _rows; i++)
        {
            for (size_t j = 0; j < _cols; j++)
            {
                identity(i, j) = 0;
            }
            identity(i, i) = 1;
        }
    }
    return identity;
}

template <class Type>
Matrix<Type> Matrix<Type>::transpose()
{
    Matrix<Type> Transposed(this->_rows, this->_cols);
    Transposed.Alloc();
    for (size_t i = 0; i < this->_rows; i++)
    {
        for (size_t j = 0; j < this->_cols; j++)
        {
            Transposed(i, j) = this->_matrix[j][i];
        }
    }
    return Transposed;
}

template <class Type>
std::vector<std::vector<Type>> Matrix<Type>::get_augmented(Matrix<Type> &Vect)
{
    _compute_augmented(Vect);
    return this->_augmented;
}

template <class Type>
void Matrix<Type>::_compute_augmented(Matrix<Type> &Vect)
{
    // Matrix<Type> augmented_matrix(this->_rows, this->_cols + 1);
    size_t cols_aug = this->_cols + 1;
    Alloc_augmented();

    for (size_t i = 0; i < this->_rows; i++)
    {
        for (size_t j = 0; j < cols_aug; j++)
        {
            if (j < cols_aug - 1)
            {
                this->_augmented[i][j] = this->_matrix[i][j];
            }
            else
            {
                this->_augmented[i][j] = Vect(i, 0);
            }
        }
    }
}

template <class Type>
void Matrix<Type>::print(std::vector<std::vector<Type>> array)
{
    size_t rows = array.size();
    size_t cols = array[0].size();
    for (size_t i = 0; i < rows; i++)
    {

        for (size_t j = 0; j < cols; j++)
        {
            std::cout << array[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

template <class Type>
void Matrix<Type>::Alloc()
{
    std::vector<Type> v(_cols, 0);
    std::vector<std::vector<Type>> mat(_rows, v);
    this->_matrix.swap(mat);
}

template <class Type>
void Matrix<Type>::Alloc_augmented()
{
    std::vector<Type> v(_cols + 1, 0);
    std::vector<std::vector<Type>> mat(_rows, v);
    this->_augmented.swap(mat);
}

template <class Type>
Matrix<Type> Matrix<Type>::operator-(const Matrix<Type> &Mat)
{
    Matrix<Type> result(this->_rows, this->_cols);
    result.Alloc();
    for (size_t i = 0; i < this->_rows; i++)
    {
        for (size_t j = 0; j < this->_cols; j++)
        {
            result(i, j) = this->_matrix[i][j] - Mat(i, j);
        }
    }

    return result;
}

template <class Type>
Matrix<Type> Matrix<Type>::operator*(const Matrix<Type> &Mat)
{
    Matrix<Type> result(this->_rows, this->_cols);
    result.Alloc();
    for (size_t i = 0; i < this->_rows; i++)
    {
        for (size_t j = 0; j < this->_cols; j++)
        {
            for (size_t k = 0; k < this->_rows; k++)
            {
                result(i, j) += this->_matrix[i][k] * Mat(k, j);
            }
        }
    }
    return result;
}

template <class Type>
Type &Matrix<Type>::operator()(const size_t &row, const size_t &col)
{
    return this->_matrix[row][col];
}
template <class Type>
const Type &Matrix<Type>::operator()(const size_t &row, const size_t &col) const
{
    return this->_matrix[row][col];
}

// template <class Type>
// Matrix<Type> Matrix<Type>::zeros()
// {
//     Matrix<Type> zeros_array(this->_rows, this->_cols);
//     Alloc(zeros_array._matrix);
//     for (size_t i = 0; i < this->_rows; i++)
//     {
//         for (size_t j = 0; j < this->_cols; j++)
//         {
//             zeros_array(i, j) = 0;
//         }
//     }
//     return zeros_array;
// }

// // template <class Type>
// // void Matrix<Type>::computeAugmented(Matrix<Type> &Vect)
// // {

// // }

// // template <class Type>
// // Matrix<Type> Matrix<Type>::gaussianElimination()
// // {
// //     // Start with gaussian Elimination
// //     // Check if the first pivot is valid
// //     size_t n = Augmented._rows;
// //     // Create temporal matrix
// //     Matrix<Type> Temp(Augmented._rows, Augmented._cols);
// //     Alloc(Temp._matrix);
// //     // size_t NROW[N];
// //     // Define counters on each loop
// //     size_t p = 0; // To find the valid pivot values
// //     size_t i1 = 0;
// //     size_t j1 = 0;
// //     size_t k1 = 0;
// //     for (size_t i = 0; i < n - 1; i++)
// //     {
// //         p = i;
// //         while (Augmented(p, i) != 0 && p <= n)
// //         {
// //             p++;
// //             if (p == n)
// //             {
// //                 std::cerr << "no unique solution exists" << '\n';
// //                 throw;
// //             }
// //         }
// //         // Swap rows if needed
// //         if (p != i)
// //         {
// //             Augmented.swapRows(p, i);
// //         }
// //         for (size_t j = i; j < n; j++)
// //         {
// //             Temp(j, i) = Augmented(j, i) / Augmented(i, i);
// //         }
// //     }
// //     return Temp;
// // }

// template <class Type>
// void Matrix<Type>::swapRows(size_t row1, size_t row2)
// {
//     Type *temp_ptr = this->_matrix[row1];
//     this->_matrix[row1] = this->_matrix[row2];
//     this->_matrix[row2] = temp_ptr;
// }

// template <class Type>
// void Matrix<Type>::getSolution(Matrix<Type> &Vect)
// {
//     computeAugmented(Vect);
//     // this->augmented.print();
//     // gaussianElimination(Augmented);
// }

// // --------------------------------------------------------------------------- //
// // Compute the sum of two matrices
// // --------------------------------------------------------------------------- //
// template <class Type>
// Matrix<Type> Matrix<Type>::operator+(const Matrix<Type> &Mat)
// {
//     Matrix<Type> result(this->_rows, this->_cols);
//     result.Alloc();
//     for (size_t i = 0; i < this->_rows; i++)
//     {
//         for (size_t j = 0; j < this->_cols; j++)
//         {
//             result(i, j) = this->_matrix[i][j] + Mat(i, j);
//         }
//     }

//     return result;
// }
// // --------------------------------------------------------------------------- //
// // Compute the substraction of two matrices
// // --------------------------------------------------------------------------- //

#endif