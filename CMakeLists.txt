cmake_minimum_required(VERSION 3.1)
project(sfm_project)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
find_package(Ceres REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_package(Eigen3 REQUIRED)
#find_package(Glog REQUIRED)
find_package(Boost REQUIRED)
find_package(PCL 1.8 REQUIRED)

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)



include_directories(
        src
        include
        ${catkin_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS}
)
include_directories(${PCL_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/include/eigen3")
include_directories(include ${catkin_INCLUDE_DIRS})


add_library(detect_points feature_points/detect_points.cc)
#add_library(pose_estimate pose_estimate.h pose_estimate.cc)
add_executable(sfm_project main.cc feature_points/detect_points.cc feature_points/detect_points.h)

target_link_libraries(sfm_project
        ${OpenCV_LIBS}
        Eigen3::Eigen
        ${PCL_LIBRARIES}
#        pose_estimate
        ${CERES_LIBRARIES}
        )
