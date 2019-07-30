cmake_minimum_required(VERSION 3.1)

# c+++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# opencv DirPath
set(OpenCV_DIR "/usr/local/utils/opencv/4.1.0/lib/cmake/opencv4/")

project(svmdigits)

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    inlcude path: ${OpenCV_INCLUDE_DIRS}")

add_executable(svmdigits main.cpp)

target_link_libraries(svmdigits LINK_PRIVATE ${OpenCV_LIBS})
