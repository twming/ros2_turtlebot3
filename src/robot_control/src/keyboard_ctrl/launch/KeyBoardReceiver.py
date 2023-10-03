
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    sub_cmd = Node(
        package='keyboard_ctrl',
        executable='keyboard_receive',
        output='screen'
    )

    ld = LaunchDescription()
    ld.add_action(sub_cmd)

    return ld
