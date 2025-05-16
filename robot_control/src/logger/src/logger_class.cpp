#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class LoggerNode : public rclcpp::Node
{
    public:
        LoggerNode() : Node ("logger_node") {
            counter_=0;
            timer_ = create_wall_timer(
                500ms,
                std::bind(&LoggerNode::call_back,
                this)
            );
        }

        void call_back() {
            RCLCPP_INFO(get_logger(),"Hello ROS2, echo %d",counter_++);
        }

    private:
        int counter_;
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LoggerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
} 