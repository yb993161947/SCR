cmake_minimum_required(VERSION 3.5)
project(ACL)

#set(CMAKE_BUILD_TYPE "Release") #using CMAKE_BUILD_TYPE to set the cmake method [Debug | Release]
# CMAKE_CXX_FLAGS CMake C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -pthread -fPIE")  #-fopenmp add-on 


set(CMAKE_AUTOMOC ON)
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

aux_source_directory(. SRC_LIST)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
#find_package(opencv REQUIRED)

qt5_wrap_ui(ui_FILES ACLwidget.ui)
qt5_add_resources(qrc_FILES resources.qrc)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${ui_FILES} ${qrc_FILES})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Resources)
#find_package(Eigen3 REQUIRED)
include_directories(E:/eigen-eigen-07105f7124f9)
find_package(DCMTK REQUIRED)
include_directories(${DCMTK_INCLUDE_DIR})

# add_executable(ACL
# ACLwidget.cpp
# ACLwidget.h
# DxArray.h
# DxMath.cpp
# DxMath.h
# DxPoint.cpp
# DxPoint.h
# DxSpatialMatching.cpp
# DxSpatialMatching.h
# ImageRectify.cpp
# ImageRectify.h
# ImageScene.cpp
# ImageScene.h
# thread_get_ndi_marker.cpp
# thread_get_ndi_marker.h
# main.cpp

# ${ui_FILES} 
# )
target_link_libraries(ACL 
Qt5::Core 
Qt5::Widgets
Qt5::Network
${OpenCV_LIBS}
${DCMTK_LIBRARIES}
)