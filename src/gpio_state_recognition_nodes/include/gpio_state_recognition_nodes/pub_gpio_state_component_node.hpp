#pragma once
#include <rclcpp/rclcpp.hpp>
#include "gpio_messages/msg/gpio_state.hpp"
#include "visibility.h"

namespace ros2rasp_lecture{

class PubGpioStateComponentNode : public rclcpp::Node{
public:
  ROS2RASP_LECTURE_PUBGPIOSTATECOMPONENTNODE_PUBLIC
  PubGpioStateComponentNode(
    const rclcpp::NodeOptions& options = rclcpp::NodeOptions()
  );
  ROS2RASP_LECTURE_PUBGPIOSTATECOMPONENTNODE_PUBLIC
  PubGpioStateComponentNode(
    const std::string& name_space,
    const rclcpp::NodeOptions& options = rclcpp::NodeOptions()
  );
  ROS2RASP_LECTURE_PUBGPIOSTATECOMPONENTNODE_PUBLIC
  ~PubGpioStateComponentNode();
private:
  // related to rasp. pi
  int pi_;
  // for publishing
  rclcpp::Publisher<gpio_messages::msg::GpioState>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}
