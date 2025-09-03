#include <dataframe/dataframe.hpp>
#include <iostream>
#include <vector>


int main() {
    // Example 1: Create DataFrame with data
    Eigen::MatrixXd data(4, 3);
    data << 1.5, 2.3, 3.7,
            5.1, 6.8, 7.3,
            9.4, 10.2, 11.6,
            13.2, 14.5, 15.8;
    
    std::vector<std::string> columns = {"Temperature", "Pressure", "Volume"};
    DataFrame<double> df(data, columns);
    
    std::cout << "DataFrame with experimental data:\n";
    std::cout << df << "\n\n";
    
    // Example 2: Empty DataFrame
    DataFrame<double> df_empty;
    std::cout << "Empty DataFrame:\n";
    std::cout << df_empty << "\n\n";
    
    // Example 3: DataFrame with only columns
    DataFrame<double> df_cols({"X", "Y", "Z", "W"});
    std::cout << "DataFrame with columns only:\n";
    std::cout << df_cols << "\n";
    
    return 0;
}