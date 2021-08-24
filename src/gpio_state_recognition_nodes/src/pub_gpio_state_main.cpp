#include <rclcpp/rclcpp.hpp>
#include "pub_gpio_state_node.hpp"

int main(int argc, char* argv[]){
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<ros2rasp_lecture::PubGpioStateNode>());
  rclcpp::shutdown();
  return 0;
}
