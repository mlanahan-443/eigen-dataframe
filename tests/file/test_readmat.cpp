#include <gtest/gtest.h>
#include <eigen3/Eigen/Dense>
#include "../../include/file/matrix_io.cpp"
#include <variant>

using namespace Eigen;

TEST(ReadMatTest, ReadMatrixFromNpy) {
    // Define the expected matrix (you will populate this)
    MatrixReal<double> expected(3, 3);
    expected << 1.0, 2.0, 3.0,
                4.0, 5.0, 6.0,
                7.0, 8.0, 9.0;

    // Read the matrix from file
    auto result = read_mat("data/read_mat_test.npy");

    // Check that the file was read successfully
    ASSERT_TRUE(result.has_value());

    // Check that we got a matrix (not a vector)
    ASSERT_TRUE(std::holds_alternative<MatrixReal<double>>(*result));

    // Extract the matrix
    MatrixReal<double> actual = std::get<MatrixReal<double>>(*result);

    // Check dimensions
    ASSERT_EQ(actual.rows(), expected.rows());
    ASSERT_EQ(actual.cols(), expected.cols());

    // Check values
    EXPECT_TRUE(actual.isApprox(expected, 1e-10));
}

TEST(ReadMatTest, FileDoesNotExist) {
    auto result = read_mat("data/nonexistent_file.npy");
    EXPECT_FALSE(result.has_value());
}