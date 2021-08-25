cmake_minimum_required(VERSION 3.5)
project(gpio_led_control_node)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(gpio_msgs REQUIRED)

add_library(gpio_led_control_component_node SHARED
  src/gpio_led_control_component_node.cpp
)
rclcpp_components_register_nodes(
  gpio_led_control_component_node "ros2rasp_lecture::GpioLedControlComponentNode"
)
target_compile_definitions(gpio_led_control_component_node
  PRIVATE "MY_LIBRARY_BUILDING_LIBRARY"
)
target_compile_options(gpio_led_control_component_node
  PUBLIC -Wall -pthread
)
target_link_libraries(gpio_led_control_component_node
  pigpiod_if2
)
ament_target_dependencies(gpio_led_control_component_node
  rclcpp
  gpio_msgs
  rclcpp_components
)
target_include_directories(gpio_led_control_component_node
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
if(NOT WIN32)
  ament_environment_hooks(
    "${ament_cmake_package_templates_ENVIRONMENT_HOOK_LIBRARY_PATH}"
  )
endif()

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  rclcpp
  gpio_msgs
  rclcpp_components
)

install(
  DIRECTORY include/
  DESTINATION include
)
install(TARGETS
  gpio_led_control_component_node
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
