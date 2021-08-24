#include <rclcpp/rclcpp.hpp>
#include "rclcpp_components/register_node_macro.hpp"
#include "gpio_state_recognition_nodes/pub_gpio_state_component_node.hpp"
#include "gpio_messages/msg/gpio_state.hpp"
#include <pigpiod_if2.h>

namespace ros2rasp_lecture {

PubGpioStateComponentNode::PubGpioStateComponentNode(
  const rclcpp::NodeOptions& options
) : PubGpioStateComponentNode("", options){
}

PubGpioStateComponentNode::PubGpioStateComponentNode(
  const std::string& name_space,
  const rclcpp::NodeOptions& options
) : Node("pub_gpio_state_node", name_space, options){
  using namespace std::chrono_literals;

  RCLCPP_INFO(this->get_logger(), "=== Information: pub_gpio_state_node ===");
  // Set up rasp. pi
  pi_ = pigpio_start(NULL,NULL);
  if(pi_ < 0){
    throw std::runtime_error("Failed to init gpio.");
  }
  RCLCPP_INFO(this->get_logger(), "Initialize: OK");
  set_mode(pi_, 21, PI_OUTPUT);
  RCLCPP_INFO(this->get_logger(), "Set up GPIO21 as an output: OK");
  set_mode(pi_, 26, PI_INPUT);
  RCLCPP_INFO(this->get_logger(), "Set up GPIO26 as an input: OK");

  pub_ = this->create_publisher<gpio_messages::msg::GpioState>(
    "pub_gpio_state",
    rclcpp::QoS(10)
  );
  timer_ = this->create_wall_timer(
    100ms,
    [this](){
      auto msg = std::make_shared<gpio_messages::msg::GpioState>();
      msg->gpio=26;
      msg->level=gpio_read(pi_,26);
      pub_->publish(*msg);
    }
  );
  RCLCPP_INFO(this->get_logger(), "Start to observe GPIO26: OK");
  RCLCPP_INFO(this->get_logger(), "All green");
}

PubGpioStateComponentNode::~PubGpioStateComponentNode(){
  pigpio_stop(pi_);
}

}
RCLCPP_COMPONENTS_REGISTER_NODE(ros2rasp_lecture::PubGpioStateComponentNode)
