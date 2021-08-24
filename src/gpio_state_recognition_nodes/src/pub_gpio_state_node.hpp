#pragma once
#include <rclcpp/rclcpp.hpp>
#include "gpio_messages/msg/gpio_state.hpp"

namespace ros2rasp_lecture{

class PubGpioStateNode : public rclcpp::Node{
public:
  PubGpioStateNode(
    const std::string& name_space="",
    const rclcpp::NodeOptions& options = rclcpp::NodeOptions()
  );
  ~PubGpioStateNode();
private:
  // related to rasp. pi
  int pi_;
  // for publishing
  rclcpp::Publisher<gpio_messages::msg::GpioState>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}
