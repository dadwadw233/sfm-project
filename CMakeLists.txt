cmake_minimum_required(VERSION 3.20)
project(little_task)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(Ceres REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(g2o CONFIG REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(little_task main.cpp featurePoints/detectPoints.cpp featurePoints/detectPoints.h)

target_link_libraries(little_task
                        ${OpenCV_LIBS}
                        Ceres::ceres
                        Eigen3::Eigen
                        g2o::core g2o::stuff g2o::types_icp g2o::types_sba)
