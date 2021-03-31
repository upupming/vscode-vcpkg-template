cmake_minimum_required(VERSION 3.14)

# Setup vcpkg script with CMake (note: should be placed before project() call)
list(APPEND VCPKG_FEATURE_FLAGS "versions")
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(vscode-vcpkg-template LANGUAGES CXX)

add_executable(vscode-vcpkg-template src/main.cpp)

find_package(dcmtk REQUIRED)
# Add the given directories to those the compiler uses to search for include files.
# Use target_* whenever possible https://stackoverflow.com/a/56565927/8242705
# Difference between PUBLIC & PRIVATE: https://zhuanlan.zhihu.com/p/82244559
message(STATUS "${DCMTK_LIBRARIES}")
message(STATUS "${DCMTK_INCLUDE_DIR}")
target_include_directories(vscode-vcpkg-template PRIVATE ${DCMTK_INCLUDE_DIR})
target_link_libraries(vscode-vcpkg-template PRIVATE ${DCMTK_LIBRARIES})


find_package(SQLite3 REQUIRED)
message(STATUS "SQLite3_INCLUDE_DIR: ${SQLite3_INCLUDE_DIR}")
message(STATUS "SQLite3_LIBRARIES: ${SQLite3_LIBRARIES}")
target_include_directories(vscode-vcpkg-template PRIVATE ${SQLite3_INCLUDE_DIR})
target_link_libraries(vscode-vcpkg-template PRIVATE ${SQLite3_LIBRARIES})

message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "EXECUTABLE_OUTPUT_PATH: ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "RUNTIME_OUTPUT_DIRECTORY_DEBUG: ${RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

file(COPY src/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

