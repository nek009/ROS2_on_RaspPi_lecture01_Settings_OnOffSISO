#pragma once
#include <rclcpp/rclcpp.hpp>
#include "gpio_msgs/msg/gpio_state.hpp"
#include "visibility_control.h"

namespace ros2rasp_lecture{

class PubGpioStateComponentNode : public rclcpp::Node{
public:
  GPIO_STATE_RECOGNITION_NODE_PUBLIC
  PubGpioStateComponentNode(
    const rclcpp::NodeOptions& options = rclcpp::NodeOptions()
  );
  GPIO_STATE_RECOGNITION_NODE_PUBLIC
  PubGpioStateComponentNode(
    const std::string& name_space,
    const rclcpp::NodeOptions& options = rclcpp::NodeOptions()
  );
  GPIO_STATE_RECOGNITION_NODE_PUBLIC
  ~PubGpioStateComponentNode();
private:
  // related to rasp. pi
  int pi_;
  // for publishing
  rclcpp::Publisher<gpio_msgs::msg::GpioState>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}
