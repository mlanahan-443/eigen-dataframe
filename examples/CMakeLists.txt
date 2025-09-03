add_executable(basic_usage basic_usage.cpp)

# Link the DataFrame header-only library (this provides include paths and Eigen)
target_link_libraries(basic_usage PRIVATE eigen_dataframe)

# Optional: Set output directory for examples
set_target_properties(basic_usage PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
)