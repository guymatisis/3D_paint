cmake_minimum_required(VERSION 3.8)
project(3d_paint)
set(CMAKE_CXX_STANDARD 11)

find_package(pybind11 PATHS "/home/guy/anaconda2/pkgs/")
include_directories(${PYBIND11_INCLUDE_DIR})

find_package( PythonLibs 2.7 REQUIRED )
include_directories(/usr/include/python2.7 )
#find_package(Qt5Widgets)
find_package(OpenCV REQUIRED)
set(SOURCE_FILES main.cpp object_detection.cpp calibration.cpp cmake-build-debug/popt_pp.h  calibration.cpp object_detection.h camera.h calibration.h compute_3d_points.cpp compute_3d_points.h point_3d.h point_2d.h error_estimation.cpp error_estimation.h)




add_executable(3d_paint ${SOURCE_FILES})
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(3d_paint PRIVATE ${OpenCV_LIBS}  pybind11::embed /usr/include/python2.7)

