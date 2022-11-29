cmake_minimum_required(VERSION 3.0.2)
project(laser_filter)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
)

find_package(Boost COMPONENTS program_options REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES laser_filter
  CATKIN_DEPENDS sensor_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(cone_filter
  src/cone_filter.cpp
)

add_dependencies(cone_filter
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(cone_filter
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
install(TARGETS cone_filter
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
