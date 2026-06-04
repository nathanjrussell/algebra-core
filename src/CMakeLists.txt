add_library(njr_algebra_core INTERFACE)
add_library(njr::algebra_core ALIAS njr_algebra_core)
target_compile_features(njr_algebra_core INTERFACE cxx_std_20)
target_include_directories(njr_algebra_core INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)
