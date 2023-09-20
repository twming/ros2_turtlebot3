#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

class publisher : public rclcpp::Node {
    public:
        publisher() : Node("publisher_node") {
            publisher_ = create_publisher<std_msgs::msg::Int32>("topic_with_int",10);
            timer_ = create_wall_timer(
                500ms, 
                std::bind(&publisher::call_back,this)
            );
        }

        void call_back() {
            message_.data +=1;
            publisher_->publish(message_);
            RCLCPP_INFO(get_logger(),"Hello ROS2, sent message: %d",message_.data);
        }

    private:
        rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        std_msgs::msg::Int32 message_;
};

int main(int argc, char * argv[]) {
    
    rclcpp::init(argc,argv);

    auto node=std::make_shared<publisher>();
    
    rclcpp::spin(node);
    
    rclcpp::shutdown();
    
    return 0;
}