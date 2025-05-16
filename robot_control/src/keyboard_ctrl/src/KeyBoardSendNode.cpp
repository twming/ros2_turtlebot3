#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/char.hpp"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int getch(void)
{
    int ch;
    struct termios oldt;
    struct termios newt;

    // Store old settings, and copy to new settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Make required changes and apply the settings
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_iflag |= IGNBRK;
    newt.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
    newt.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &newt);

    // Get the current character
    ch = getchar();

    // Reapply old settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc,argv);
    auto node=rclcpp::Node::make_shared("keyboard_send");
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
            if(key=='d'||key=='a'||key=='w'||key=='x'){
                message.data=key;
                _pub->publish(message);
            }
        }
        rclcpp::spin_some(node);

    }
    return 0;
}