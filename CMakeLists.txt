# CMakeLists file to build this project
# =====================================

# Set the minimum required version of CMake
cmake_minimum_required(VERSION 2.8)

# Set project name
project(SerialPortProject)

# List of files
set(source_files
)

set(header_files
)

set(SerialPort_files
	include/SerialPort.hpp
	src/SerialPort.cpp
)

# Create SerialPort library
add_library(SerialPort ${SerialPort_files})
target_include_directories(SerialPort PUBLIC "${CMAKE_SOURCE_DIR}/include")

# Create executable
add_executable(SerialPortExecutable src/main.cpp)
target_link_libraries(SerialPortExecutable SerialPort)
