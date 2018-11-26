cmake_minimum_required(VERSION 2.8.3)
project(turtlebot_test_kaviya)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS 
	move_base
	move_base_msgs 
	roscpp 
	rviz 
	std_msgs 
	actionlib
	actionlib_msgs
	aruco_ros
	sensor_msgs
	stereo_msgs 
	geometry_msgs 
	message_generation 
	genmsg 
	cv_bridge 
	image_transport
	costmap_2d
	rotate_recovery
	)
	
FIND_PACKAGE(aruco REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(PCL REQUIRED)
FIND_PACKAGE(Boost REQUIRED)

# catkin_python_setup()

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES turtlebot_test_kaviya
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(
 include
 ${catkin_INCLUDE_DIRS}
 ${PCL_INCLUDE_DIRS} 
 ${Boost_INCLUDE_DIRS} 
)


link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(pose_from_marker src/pose_from_marker.cpp)
target_link_libraries(pose_from_marker ${PCL_LIBRARIES} ${catkin_LIBRARIES})

add_executable(goal_generator src/goal_generator.cpp)
target_link_libraries(goal_generator ${catkin_LIBRARIES})

add_executable(aruco_test src/aruco_test.cpp)
target_link_libraries(aruco_test ${catkin_LIBRARIES} ${OpenCV_LIBS} ${aruco_LIBS})
	
	
	