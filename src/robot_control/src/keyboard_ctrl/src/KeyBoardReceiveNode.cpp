#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/char.hpp"

using std::placeholders::_1;

class SubscriberNode : public rclcpp::Node
{
public:
  SubscriberNode()
  : Node("keyboard_receive")
  {
    subscriber_ = create_subscription<std_msgs::msg::Char>(
      "key_out", 10,
      std::bind(&SubscriberNode::callback, this, _1));
  }

  void callback(const std_msgs::msg::Char::SharedPtr msg)
  {
    RCLCPP_INFO(get_logger(), "%c received\n", msg->data);
  }

private:
  rclcpp::Subscription<std_msgs::msg::Char>::SharedPtr subscriber_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<SubscriberNode>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}
