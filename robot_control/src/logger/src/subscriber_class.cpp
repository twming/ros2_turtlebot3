#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using std::placeholders::_1;

class subscriber : public rclcpp::Node {
    public:
        subscriber() : Node ("subscriber_node") {
        subscriber_ = create_subscription<std_msgs::msg::Int32>(
            "topic_with_int",
            10,
            std::bind(&subscriber::call_back,this,_1)
            );
        }

        void call_back(const std_msgs::msg::Int32::SharedPtr msg) {
            RCLCPP_INFO(get_logger(),"Hello ROS2, received message: %d",msg->data);
        }

    private:
        rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber_;

};

int main(int argc, char * argv[]) {

    rclcpp::init(argc, argv);

    auto node = std::make_shared<subscriber>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}