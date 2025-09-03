#ifndef EIGEN_DATAFRAME_HPP
#define EIGEN_DATAFRAME_HPP

#include<eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

template<typename Scalar = double>
class DataFrame {
public:
    using MatrixType = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    using VectorType = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;
    using RowVectorType = Eigen::Matrix<Scalar, 1, Eigen::Dynamic>;
    
private:
    MatrixType data_;
    std::vector<std::string> columns_;
    
public:
    // Default constructor - empty DataFrame
    DataFrame() : data_(MatrixType()), columns_({}) {}
    
    // Constructor with only columns
    explicit DataFrame(const std::vector<std::string>& columns) 
        : data_(MatrixType(0, columns.size())), columns_(columns) {}
    
    // Constructor with data and columns
    DataFrame(const MatrixType& data, const std::vector<std::string>& columns) 
        : data_(data), columns_(columns) {
        if (data_.cols() != static_cast<Eigen::Index>(columns_.size())) {
            throw std::invalid_argument("Number of columns in data matrix must match number of column names");
        }
    }
    
    // Getters
    const MatrixType& data() const { return data_; }
    MatrixType& data() { return data_; }
    const std::vector<std::string>& columns() const { return columns_; }
    
    // Shape information
    Eigen::Index rows() const { return data_.rows(); }
    Eigen::Index cols() const { return data_.cols(); }
    std::pair<Eigen::Index, Eigen::Index> shape() const { return {rows(), cols()}; }
    
    // Friend function for stream output
    friend std::ostream& operator<<(std::ostream& os, const DataFrame<Scalar>& df) {
        // Handle empty DataFrame
        if (df.cols() == 0) {
            os << "Empty DataFrame";
            return os;
        }
        
        // Calculate column widths
        std::vector<size_t> col_widths;
        
        // Start with column name widths
        for (const auto& col_name : df.columns_) {
            col_widths.push_back(col_name.length());
        }
        
        // Check data widths and update if necessary
        for (Eigen::Index i = 0; i < df.rows(); ++i) {
            for (Eigen::Index j = 0; j < df.cols(); ++j) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(6) << df.data_(i, j);
                col_widths[j] = std::max(col_widths[j], oss.str().length());
            }
        }
        
        // Add padding
        for (auto& width : col_widths) {
            width += 2;  // Add padding on both sides
        }
        
        // Add index column width
        size_t index_width = std::max(size_t(5), std::to_string(df.rows() - 1).length() + 2);
        
        // Print header with column names
        os << std::setw(index_width) << " ";  // Space for index column
        for (size_t j = 0; j < df.columns_.size(); ++j) {
            os << std::setw(col_widths[j]) << df.columns_[j];
        }
        os << "\n";
        
        // Print separator line
        os << std::string(index_width, '-');
        for (size_t j = 0; j < col_widths.size(); ++j) {
            os << std::string(col_widths[j], '-');
        }
        os << "\n";
        
        // Print data rows
        for (Eigen::Index i = 0; i < df.rows(); ++i) {
            // Print row index
            os << std::setw(index_width - 1) << i << " ";
            
            // Print row data
            for (Eigen::Index j = 0; j < df.cols(); ++j) {
                os << std::setw(col_widths[j]) << std::fixed << std::setprecision(6) << df.data_(i, j);
            }
            os << "\n";
        }
        
        // Print shape information
        os << "\n[" << df.rows() << " rows x " << df.cols() << " columns]";
        
        return os;
    }
};

#endif // EIGEN_DATAFRAME_HPP