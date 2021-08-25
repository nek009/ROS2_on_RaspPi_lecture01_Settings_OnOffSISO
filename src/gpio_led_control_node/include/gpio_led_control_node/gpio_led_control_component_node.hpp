#pragma once
#include <rclcpp/rclcpp.hpp>
#include "gpio_msgs/msg/gpio_state.hpp"
#include "visibility.h"

namespace ros2rasp_lecture{

class GpioLedControlComponentNode : public rclcpp::Node{
public:
  GPIO_LED_CONTROL_NODE_PUBLIC
  GpioLedControlComponentNode(
    const rclcpp::NodeOptions& options = rclcpp::NodeOptions()
  );
  GPIO_LED_CONTROL_NODE_PUBLIC
  GpioLedControlComponentNode(
    const std::string& name_space,
    const rclcpp::NodeOptions& options = rclcpp::NodeOptions()
  );
  GPIO_LED_CONTROL_NODE_PUBLIC
  ~GpioLedControlComponentNode();
private:
  // related to rasp. pi
  int pi_;
  // for subscriginb
  rclcpp::Subscription<gpio_msgs::msg::GpioState>::SharedPtr sub_;
};

}
