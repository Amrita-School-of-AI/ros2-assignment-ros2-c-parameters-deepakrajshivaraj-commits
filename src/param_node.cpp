#include <chrono>
#include <functional>
#include <string>
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class ParamNode : public rclcpp::Node {
public:
  ParamNode() : Node("param_node") {
    this->declare_parameter("robot_name", "ROS2Bot");
    this->declare_parameter("max_speed", 1.5);
    this->declare_parameter("enabled", true);

    timer_ = this->create_wall_timer(
      2000ms, std::bind(&ParamNode::timer_callback, this));
  }

private:
  void timer_callback() {
    std::string name = this->get_parameter("robot_name").as_string();
    double speed = this->get_parameter("max_speed").as_double();
    bool enabled = this->get_parameter("enabled").as_bool();

    RCLCPP_INFO(this->get_logger(), "Robot: %s, Max Speed: %f, Enabled: %s",
                name.c_str(), speed, (enabled ? "true" : "false"));
  }
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ParamNode>());
  rclcpp::shutdown();
  return 0;
}
