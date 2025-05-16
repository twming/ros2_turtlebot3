#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/char.hpp"
#include "teleop/keyboarddecode.hpp"


int main(int argc, char * argv[])
{
    rclcpp::init(argc,argv);
    auto node=rclcpp::Node::make_shared("keyboard_node");
    auto _pub=node->create_publisher<std_msgs::msg::Char>("key_out",10);

    std_msgs::msg::Char message;
      
    char key(' ');
    while (rclcpp::ok()) {

        key = getch();
        if (key == '\x03')
        {
            break;
        }
        else {
            if(key=='d'||key=='a'||key=='w'||key=='x'||key=='q'||key=='e'||key=='z'||key=='c'){
                message.data=key;
                _pub->publish(message);
            }
        }
        rclcpp::spin_some(node);

    }
    return 0;
}
