# Algebra core

C++ algebraic interfaces and constrained element contracts.

```cmake
include(FetchContent)

FetchContent_Declare(
    algebra_core
    GIT_REPOSITORY git@github.com:nathanjrussell/algebra-core.git
    GIT_TAG v0.2.0
)

FetchContent_MakeAvailable(algebra_core)

target_link_libraries(my_app PRIVATE algebra::core)
```
