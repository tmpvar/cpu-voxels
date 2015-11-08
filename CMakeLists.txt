cmake_minimum_required(VERSION 2.6)
project(cpuvoxels)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_C_FLAGS "-O3")
# configure linmath
include_directories(deps/linmath)

# configure glfw
set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(deps/glfw)
include_directories(deps/glfw/include deps/glfw/deps)

# configure thpool
include_directories(deps/thpool)

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


