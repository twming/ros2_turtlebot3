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
  BumpGoNode() : Node("bump_go"), state_(FORWARD)
  {
    scan_sub_ = create_subscription<std_msgs::msg::Float32>(
      "ultrasonic_out", rclcpp::SensorDataQoS(),
      std::bind(&BumpGoNode::scan_callback, this, _1));

    vel_pub_ = create_publisher<std_msgs::msg::Char>("output_vel", 10);
    timer_ = create_wall_timer(100ms, std::bind(&BumpGoNode::control_cycle, this));

    state_ts_ = now();
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
        
        if (check_forward_2_stop()) {
          go_state(STOP);
        }
        if (check_forward_2_back()) {
          go_state(BACK);
        }

        break;
      case BACK:
        out_vel.data = 120;

        if (check_back_2_turn()) {
          go_state(TURN);
        }

        break;
      case TURN:
        out_vel.data = 101;

        if (check_turn_2_forward()) {
          go_state(FORWARD);
        }

        break;
      case STOP:
        if (check_stop_2_forward()) {
          go_state(FORWARD);
        }
        break;
    }

    vel_pub_->publish(out_vel);

  }

  static const int FORWARD = 0;
  static const int BACK = 1;
  static const int TURN = 2;
  static const int STOP = 3;
  int state_;
  rclcpp::Time state_ts_;

  void go_state(int new_state)
  {
    state_ = new_state;
    state_ts_ = now();
  }

  bool check_forward_2_back()
  {
    // going forward when deteting an obstacle
    // at 3 cm with the front laser read
    return last_scan_->data < OBSTACLE_DISTANCE;
  }

  bool check_forward_2_stop()
  {
    // Stop if no sensor readings for 1 second
    //auto elapsed = now() - rclcpp::Time(last_scan_->header.stamp);
    return (now() - state_ts_) > SCAN_TIMEOUT;
  }
  
  bool check_back_2_turn()
  {
    // Going back for 2 seconds
    return (now() - state_ts_) > BACKING_TIME;
  }

  bool check_turn_2_forward()
  {
    // Turning for 2 seconds
    return (now() - state_ts_) > TURNING_TIME;
  }

  bool check_stop_2_forward()
  {
    // Going forward if sensor readings are available
    // again
    //auto elapsed = now() - rclcpp::Time(last_scan_->header.stamp);
    return (now() - state_ts_)  < SCAN_TIMEOUT;
  }

  const rclcpp::Duration TURNING_TIME {1s};
  const rclcpp::Duration BACKING_TIME {1s};
  const rclcpp::Duration SCAN_TIMEOUT {1s};

  //static constexpr float SPEED_LINEAR = 0.3f;
  //static constexpr float SPEED_ANGULAR = 0.3f;
  static constexpr float OBSTACLE_DISTANCE = 8.0f;

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
