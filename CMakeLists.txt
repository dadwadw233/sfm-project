cmake_minimum_required(VERSION 3.11)
project(little_task)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(Ceres REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(little_task main.cc featurePoints/detectPoints.cc featurePoints/detectPoints.h pose_estimate.cc pose_estimate.h)

target_link_libraries(little_task
                        ${OpenCV_LIBS}
                        Ceres::ceres
                        Eigen3::Eigen)
