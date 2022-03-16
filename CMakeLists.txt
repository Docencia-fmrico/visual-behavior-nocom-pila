cmake_minimum_required(VERSION 2.8.3)
project(fsm_visual_behavior)

# set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CONFIG_PATH ${CMAKE_MODULE_PATH}  "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CONFIG_PATH}")

find_package(ZMQ)
if(ZMQ_FOUND)
    message(STATUS "ZeroMQ found.")
    add_definitions(-DZMQ_FOUND)
else()
  message(WARNING "ZeroMQ NOT found. Not including PublisherZMQ.")
endif()

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  behaviortree_cpp_v3
  roslint

  sensor_msgs
  tf
  cv_bridge
  image_transport
  pcl_conversions
  pcl_ros
  darknet_ros_msgs

)
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

catkin_package(
CATKIN_DEPENDS 
  roscpp 
  std_msgs 
  behaviortree_cpp_v3 
  sensor_msgs 
  tf
  cv_bridge
  image_transport
  pcl_conversions
  pcl_ros
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${ZMQ_INCLUDE_DIRS}
)

add_library(nc_person_detected SHARED src/fsm_visual_behavior/Person_detected.cpp)
add_library(nc_perceive_person SHARED src/fsm_visual_behavior/Perceive_person.cpp)
add_library(nc_ball_detected SHARED src/fsm_visual_behavior/Ball_detected.cpp)
add_library(nc_perceive_ball SHARED src/fsm_visual_behavior/Perceive_ball.cpp)
add_library(nc_follow_point SHARED src/fsm_visual_behavior/Follow_point.cpp)
add_library(nc_turn_node SHARED src/fsm_visual_behavior/Turn.cpp)
list(APPEND plugin_libs
  nc_person_detected
  nc_perceive_person
  nc_ball_detected
  nc_perceive_ball
  nc_follow_point
  nc_turn_node
)

foreach(bt_plugin ${plugin_libs})
  target_link_libraries(${bt_plugin} ${catkin_LIBRARIES})
  target_compile_definitions(${bt_plugin} PRIVATE BT_PLUGIN_EXPORT)
endforeach()

add_executable(nodo_follow_person 
  src/nodo_follow_person.cpp
)
target_link_libraries(nodo_follow_person ${catkin_LIBRARIES} ${ZMQ_LIBRARIES})

add_executable(nodo_follow_ball 
  src/nodo_follow_ball.cpp
)
target_link_libraries(nodo_follow_ball ${catkin_LIBRARIES} ${ZMQ_LIBRARIES})

add_executable(nodo_follow_complete 
  src/nodo_follow_complete.cpp
)
target_link_libraries(nodo_follow_complete ${catkin_LIBRARIES} ${ZMQ_LIBRARIES})


roslint_cpp(
  src/nodo_follow_ball.cpp
  src/nodo_follow_person.cpp
  src/nodo_follow_complete.cpp
  include/fsm_visual_behavior/Person_detected.h src/fsm_visual_behavior/Person_detected.cpp
  include/fsm_visual_behavior/Perceive_person.h src/fsm_visual_behavior/Perceive_person.cpp
  include/fsm_visual_behavior/Ball_detected.h src/fsm_visual_behavior/Ball_detected.cpp
  include/fsm_visual_behavior/Perceive_ball.h src/fsm_visual_behavior/Perceive_ball.cpp
  include/fsm_visual_behavior/Follow_point.h src/fsm_visual_behavior/Follow_point.cpp
  include/fsm_visual_behavior/Turn.h src/fsm_visual_behavior/Turn.cpp
)
