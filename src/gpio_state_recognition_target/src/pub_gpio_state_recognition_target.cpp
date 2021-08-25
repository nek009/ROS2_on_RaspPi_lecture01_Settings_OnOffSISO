#include <rclcpp/rclcpp.hpp>
#include "gpio_state_recognition_node/pub_gpio_state_component_node.hpp"

int main(int argc, char* argv[]){
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<ros2rasp_lecture::PubGpioStateComponentNode>());
  rclcpp::shutdown();
  return 0;
}
