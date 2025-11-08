cmake_minimum_required(VERSION 3.10)
project(99ML C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(NEURAL_PHYSICS_SOURCES
    src/neural_physics.c
    src/scheme_neural_bridge.c
    src/third_order_cybernetics.c
)

# Create library
add_library(neural_physics STATIC ${NEURAL_PHYSICS_SOURCES})

# Link math library
target_link_libraries(neural_physics m)

# Demo executable
add_executable(neural_symbolic_demo
    examples/neural_symbolic_demo.c
)

target_link_libraries(neural_symbolic_demo neural_physics)

# Third-order cybernetics demo
add_executable(third_order_cybernetics_demo
    examples/third_order_cybernetics_demo.c
)

target_link_libraries(third_order_cybernetics_demo neural_physics)

# Installation
install(TARGETS neural_physics neural_symbolic_demo third_order_cybernetics_demo
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES include/neural_physics.h include/third_order_cybernetics.h
    DESTINATION include
)

# Print configuration
message(STATUS "99ML - Neural-Symbolic Symbiosis")
message(STATUS "  Mind Layer: Scheme (cognitive grammar)")
message(STATUS "  Brain Layer: C/ggml (tensor operations)")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
