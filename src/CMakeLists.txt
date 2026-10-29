add_library(algebra_core INTERFACE)
add_library(algebra::core ALIAS algebra_core)
target_compile_features(algebra_core INTERFACE cxx_std_20)
target_include_directories(algebra_core INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)
