cmake_minimum_required(VERSION 3.1)
project(sfm_project)

set(CMAKE_CXX_STANDARD 14)


find_package(OpenCV REQUIRED)
find_package(Ceres REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
find_package(Threads REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Glog REQUIRED)
find_package(catkin REQUIRED COMPONENTS
        pcl_conversions
        pcl_ros
        )
find_package(Boost REQUIRED)
include_directories(
        src
        include
        ${catkin_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS}
)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/include/eigen3")
include_directories(include ${catkin_INCLUDE_DIRS})


add_executable(sfm_project main.cc feature_points/detect_points.cc feature_points/detect_points.h)

add_library(detect_points feature_points/detect_points.cc)
add_library(pose_estimate pose_estimate.cc pose_estimate.h)

target_link_libraries(sfm_project
        pose_estimate
        ${OpenCV_LIBS}
        Ceres::ceres
        ${PCL_LIBRARIES}
        ${BOOST_LIBARIES}
        Eigen3::Eigen)
