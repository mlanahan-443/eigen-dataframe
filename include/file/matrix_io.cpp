#include <optional>  // Add this for std::optional
#include <eigen3/Eigen/Dense>
#include <cnpy/cnpy.h>
#include <ostream>
#include <variant>
#include <filesystem>


using namespace Eigen;

// Declare Matrix types
template <typename real>
using MatrixReal = Matrix<real, Dynamic, Dynamic>;
template <typename real>
using VectorReal = Matrix<real, Dynamic, 1>;
template<typename real>
using MatrixOrVector = std::variant<MatrixReal<real>,VectorReal<real>>;


bool fileExists(const std::string& filename) {
    return std::filesystem::exists(filename);
}

std::optional<MatrixOrVector<double>> read_mat(const std::string& fname){
    
    if (!fileExists(fname)){
        std::cerr << "File: " << fname << " does not exist" << std::endl;
        return std::nullopt;
    }

    auto array = cnpy::npy_load(fname);
    if (array.shape.size() == 1){
        VectorReal<double> A(array.shape[0]);
        double* loaded_data = array.data<double>(); 
        for (size_t i = 0; i < array.shape[0]; ++i){
            A(i) = loaded_data[i];
        }
        
        return A;

    }else if (array.shape.size() == 2){
        MatrixReal<double> A(array.shape[0],array.shape[1]);
        double *loaded_data = array.data<double>();
        size_t n = array.shape[0]; 
        size_t m = array.shape[1];

        for (size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < m; ++ j){ 
                A(i,j) = loaded_data[i*m + j];
            }
        }

        return A;
    }else{
        std::cerr << "array in file has: " << array.shape.size() << " dimensions, currently read_mat() only supports 1 or 2" << std::endl;
        return std::nullopt;
    }

    return std::nullopt;
    
}