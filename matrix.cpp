/**
 * @file matrix.cpp
 * @author Jacob Hicks (jhicks70@ut.utm.edu)
 * @brief Implementation of the Matrix class and operators.
 * @version 0.1
 * @date 2024-10-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "matrix.h"
#include <iomanip>

/**
 * @brief Construct a new Matrix object
 * 
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 */
Matrix::Matrix(unsigned int rows, unsigned int cols) : m(rows), n(cols)
{
    // Allocate the 2D array
    ar = new double*[m];
    for (int i = 0; i < m; ++i) {
        ar[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            ar[i][j] = 0.0;
        }
    }
}

/**
 * @brief Copy constructor
 * 
 * @param rhs The matrix to copy.
 */
Matrix::Matrix(const Matrix& rhs) : m(rhs.m), n(rhs.n)
{
    // Allocate the 2D array
    ar = new double*[m];
    for (int i = 0; i < m; ++i) {
        ar[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            ar[i][j] = rhs.ar[i][j];
        }
    }
}

/**
 * @brief Destroy the Matrix object
 * 
 */
Matrix::~Matrix()
{
    // Deallocate the 2D array
    for (int i = 0; i < m; ++i) {
        delete[] ar[i];
    }
    delete[] ar;
}

/**
 * @brief Get the number of rows in the matrix.
 * 
 * @return int The number of rows in the matrix.
 */
int Matrix::getRows() const
{
    return m;
}

/**
 * @brief Get the number of columns in the matrix.
 * 
 * @return int The number of columns in the matrix.
 */
int Matrix::getCols() const
{
    return n;
}

/**
 * @brief Return a reference to the element at the specified row and column.
 *
 * @param row The row of the element.
 * @param col The column of the element.
 * @return double& A reference to the element at the specified row and column. 
 */
double& Matrix::at(unsigned int row, unsigned int col)
{
    return ar[row][col];
}

/**
 * @brief Return a const reference to the element at the specified row and column.
 *
 * @param row The row of the element.
 * @param col The column of the element.
 * @return double& A reference to the element at the specified row and column. 
 */
const double& Matrix::at(unsigned int row, unsigned int col) const
{
    return ar[row][col];
}

/**
 * @brief Overloaded assignment operator.
 * 
 * @param rhs The matrix to assign.
 */
Matrix& Matrix::operator=(const Matrix& rhs)
{
    // Copy the dimensions
    m = rhs.m;
    n = rhs.n;
    
    // Deallocate old array if it exists
    for (int i = 0; i < m; ++i) {
        delete[] ar[i];
    }
    delete[] ar;
    
    // Allocate new array
    ar = new double*[m];
    for (int i = 0; i < m; ++i) {
        ar[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            ar[i][j] = rhs.ar[i][j];
        }
    }
    
    return *this;
}

/**
 * @brief Overloaded operator for the addition of two matrices.
 * 
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return Matrix The sum of the two matrices.
 */
Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    Matrix result(m1.getRows(), m1.getCols());
    
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getCols(); ++j) {
            result.at(i, j) = m1.at(i, j) + m2.at(i, j);
        }
    }
    
    return result;
}

/**
 * @brief Overloaded operator for the subtraction of two matrices.
 * 
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return Matrix The difference of the two matrices.
 */
Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    Matrix result(m1.getRows(), m1.getCols());
    
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getCols(); ++j) {
            result.at(i, j) = m1.at(i, j) - m2.at(i, j);
        }
    }
    
    return result;
}

/**
 * @brief Overloaded operator for the multiplication of two matrices.
 * 
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return Matrix The product of the two matrices.
 */
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    // m1 is m1.getRows() x m1.getCols()
    // m2 is m2.getRows() x m2.getCols()
    // result is m1.getRows() x m2.getCols()
    
    Matrix result(m1.getRows(), m2.getCols());
    
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m2.getCols(); ++j) {
            double sum = 0.0;
            for (int k = 0; k < m1.getCols(); ++k) {
                sum += m1.at(i, k) * m2.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    
    return result;
}

/**
 * @brief Overloaded operator for the multiplication of a matrix by a scalar.
 * @param scalar The scalar value.
 * @param m The matrix.
 * @return Matrix The product of the matrix and the scalar.
 */
Matrix operator*(double scalar, const Matrix& m)
{
    Matrix result(m.getRows(), m.getCols());
    
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            result.at(i, j) = scalar * m.at(i, j);
        }
    }
    
    return result;
}

/**
 * @brief Overloaded operator for the multiplication of a matrix by a scalar.
 * @param m The matrix.
 * @param scalar The scalar value.
 * @return Matrix The product of the matrix and the scalar.
 */
Matrix operator*(const Matrix& m, double scalar)
{
    return scalar * m;
}

/**
 * @brief Overloaded operator for the output of a matrix.
 * 
 * @param os The output stream.
 * @param m The matrix.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            os << std::setw(10) << m.at(i, j);
        }
        os << " \n";
    }
    return os;
}

/**
 * @brief Overloaded operator for the input of a matrix.
 * 
 * @param is The input stream.
 * @param m The matrix.
 * @return std::istream& The input stream.
 */
std::istream& operator>>(std::istream& is, Matrix& m)
{
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            is >> m.at(i, j);
        }
    }
    return is;
}
