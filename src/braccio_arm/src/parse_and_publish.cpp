#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int8_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/multi_array_dimension.hpp"
#include "std_msgs/msg/multi_array_layout.hpp"

#define PI 3.1416

using namespace std::chrono_literals;
using std::placeholders::_1;

uint _DataArray[8]={200,90,90,90,90,90,90,200};

class PublisherNode : public rclcpp::Node
{
public:
  PublisherNode()
  : Node("pub_node")
  {
    //message_.layout.dim[0].label="arm_angle";
    //message_.layout.dim[0].size=6;
    //message_.layout.data_offset=0;
    //message_.data=(int *)malloc(sizeof(int)*8);
    //message_.data_length=6;
    //publisher_ = create_publisher<std_msgs::msg::UInt8MultiArray>("joint_array", 6);
    publisher_ = create_publisher<std_msgs::msg::UInt8MultiArray>("serial_write", 6);
    timer_ = create_wall_timer(
      2000ms, std::bind(&PublisherNode::timer_callback, this));
  }

  void timer_callback()
  {
    message_.data.clear();
    for (int i = 0; i < 6; i++)
    {
        message_.data.push_back(_DataArray[i]);
    }
    
    publisher_->publish(message_);
    RCLCPP_INFO(get_logger(),"I publish the data");
  }

private:
  rclcpp::Publisher<std_msgs::msg::UInt8MultiArray>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std_msgs::msg::UInt8MultiArray message_;
};

class SubscriberNode : public rclcpp::Node
{
public:
  SubscriberNode()
  : Node("sub_node")
  {
    subscriber_ = create_subscription<sensor_msgs::msg::JointState>(
      "joint_states", 6,
      std::bind(&SubscriberNode::callback, this, _1));
  }

  void callback(const sensor_msgs::msg::JointState::SharedPtr msg)
  {
    int i=0;
    for(i=0; i<6; i++)
    {
        //RCLCPP_INFO(get_logger(),"I heard : [%d]",uint((msg->position[i])/PI*180));
        _DataArray[i]= uint((msg->position[i])/PI*180);    
    }
    // for (i=0; i<6; i++)
    // {
    //   RCLCPP_INFO(get_logger(),"I heard : [%d]",_DataArray[i]);
    // }
    //RCLCPP_INFO(get_logger(),"--------");
  }

private:
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscriber_;
};

int main(int argc, char * argv[]) {
    
    rclcpp::init(argc,argv);

    auto node_pub = std::make_shared<PublisherNode>();
    auto node_sub = std::make_shared<SubscriberNode>();

    rclcpp::executors::SingleThreadedExecutor executor;
  // rclcpp::executors::MultiThreadedExecutor executor(
  //   rclcpp::executor::ExecutorArgs(), 8);

    executor.add_node(node_pub);
    executor.add_node(node_sub);

    executor.spin();
    
    rclcpp::shutdown();
    
    return 0;
}


