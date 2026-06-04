# Algebra core

C++ algebraic interfaces and constrained element contracts.

```cmake
include(FetchContent)

FetchContent_Declare(
    njr_algebra_core
    GIT_REPOSITORY git@github.com:nathanjrussell/algebra-core.git
    GIT_TAG v0.1.0
)

FetchContent_MakeAvailable(njr_algebra_core)

target_link_libraries(my_app PRIVATE njr::algebra_core)
```
