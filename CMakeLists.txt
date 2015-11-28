cmake_minimum_required(VERSION 2.6)
project(cpuvoxels)

set(CMAKE_C_FLAGS "-O3 -march=native -msse4.2 -mavx")
set(CMAKE_LINKER_FLAGS "-lpthread")

# configure glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW docs")
set(GLFW_INSTALL OFF CACHE BOOL "Build the GLFW installation target")
add_subdirectory(deps/glfw)
include_directories(deps/glfw/include)

# configure thpool
include_directories(deps/thpool)
include_directories(src)

# configure benchmark
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Build the BENCHMARK tests")
add_subdirectory(deps/benchmark)
include_directories(deps/benchmark/include)

add_executable(
    cpuvoxels
    src/main.c
    deps/thpool/thpool.c
    ${GLFW_LIBRARIES}
)

target_link_libraries(
    cpuvoxels
    glfw
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARIES}
)

# testing
add_executable(
    testvoxels
    test/test.c
)

# micro-benchmarks
add_executable(
    benchvoxels
    test/bench.cc
    ${BENCHMARK_SOURCE_FILES}
)

target_link_libraries(
    benchvoxels
    benchmark
)
