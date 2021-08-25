#include <rclcpp/rclcpp.hpp>
#include "rclcpp_components/register_node_macro.hpp"
#include "gpio_led_control_node/gpio_led_control_component_node.hpp"
#include "gpio_msgs/msg/gpio_state.hpp"
#include <pigpiod_if2.h>

namespace ros2rasp_lecture{

GpioLedControlComponentNode::GpioLedControlComponentNode(
  const rclcpp::NodeOptions& options
) : GpioLedControlComponentNode("",options){
}

GpioLedControlComponentNode::GpioLedControlComponentNode(
  const std::string& name_space,
  const rclcpp::NodeOptions& options
) : Node("gpio_led_control_component_node", name_space, options){
  RCLCPP_INFO(this->get_logger(), "=== Information: gpio_led_control_component_node ===");
  // Set up rasp. pi
  pi_ = pigpio_start(NULL,NULL);
  if(pi_ < 0){
    throw std::runtime_error("Failed to init gpio.");
  }
  RCLCPP_INFO(this->get_logger(), "Initialize: OK");
  set_mode(pi_, 21, PI_OUTPUT);
  RCLCPP_INFO(this->get_logger(), "Set up GPIO21 as an output: OK");
  sub_ = this->create_subscription<gpio_msgs::msg::GpioState>(
    "pub_gpio_state",
    rclcpp::QoS(10),
    [this](const gpio_msgs::msg::GpioState::SharedPtr msg) ->void {
      unsigned level_for_led = msg->level ? 0 : 1; // level:1 -> for led:0, led turns on when gpio_write(*,0)
      gpio_write(pi_,21,level_for_led);
    }
  );
  RCLCPP_INFO(this->get_logger(), "Start to control GPIO21: OK");
  RCLCPP_INFO(this->get_logger(), "All green");
}

GpioLedControlComponentNode::~GpioLedControlComponentNode(){
  pigpio_stop(pi_);
}

}
RCLCPP_COMPONENTS_REGISTER_NODE(ros2rasp_lecture::GpioLedControlComponentNode)
