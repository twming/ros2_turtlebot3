#include <utility>
#include <memory>
#include <iostream>
using namespace std;
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/char.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;  // NOLINT
using std::placeholders::_1;

class BumpGoNode : public rclcpp::Node
{
public:
  BumpGoNode() : Node("bump_go_node"), state_(FORWARD)
  {
    scan_sub_ = create_subscription<std_msgs::msg::Float32>(
      "ultrasonic_out", 10,
      std::bind(&BumpGoNode::scan_callback, this, _1));

    vel_pub_ = create_publisher<std_msgs::msg::Char>("output_vel", 10);
    timer_ = create_wall_timer(100ms, std::bind(&BumpGoNode::control_cycle, this));

    state_ts_ = now();
  }

  ~BumpGoNode()
  {
    std_msgs::msg::Char out_vel_for_stop;
    out_vel_for_stop.data = 115;
    vel_pub_->publish(out_vel_for_stop);
  }

private:
  void scan_callback(std_msgs::msg::Float32::UniquePtr msg)
  {
      last_scan_ = std::move(msg);
      cout<<"Measured Distance = "<<last_scan_->data<<endl;
  }


  void control_cycle() {
    // Do nothing until the first sensor read
    if (last_scan_ == nullptr) {return;}

    std_msgs::msg::Char out_vel;

    switch (state_) {
      case FORWARD:
        out_vel.data = 119;
        
        if (check_obstacle()) {
          go_state(TURN);
          state_ts_ = now();
        }

        break;
      case TURN:
        out_vel.data = 100;

        if (check_turn_2_forward()) {
          go_state(FORWARD);
        }

        break;
    }

    vel_pub_->publish(out_vel);

  }

  static const int FORWARD = 0;
  static const int TURN = 2;
  static const int STOP = 3;
  int state_;
  rclcpp::Time state_ts_;

  void go_state(int new_state)
  {
    state_ = new_state;
    state_ts_ = now();
  }

  bool check_obstacle()
  {
    // Check obstacle in front
    return last_scan_->data < OBSTACLE_DISTANCE && last_scan_->data > 0;
  }

  bool check_turn_2_forward()
  {
    // Turning for 3 seconds
    return ((now() - state_ts_) > TURNING_TIME);
  }

  const rclcpp::Duration TURNING_TIME {1s};
  const rclcpp::Duration BACKING_TIME {1s};
  const rclcpp::Duration SCAN_TIMEOUT {1s};

  static constexpr float OBSTACLE_DISTANCE = 30.0f;

  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr scan_sub_;
  rclcpp::Publisher<std_msgs::msg::Char>::SharedPtr vel_pub_;
  rclcpp::TimerBase::SharedPtr timer_;

  std_msgs::msg::Float32::UniquePtr last_scan_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto bumpgo_node = std::make_shared<BumpGoNode>();
  rclcpp::spin(bumpgo_node);

  rclcpp::shutdown();

  return 0;
}
