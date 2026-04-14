#include <chrono>
#include <functional>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class SensorPublisher : public rclcpp::Node {
    public:
        SensorPublisher() : Node("sensor_publisher") {
            /* here this is basically the self in python and "this" refer to the class
            of Node we are inherting from and to access the underlying objects like create_publisher 
            we use -> and the methods but why -> are we in the here as pointer?
            */
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        timer_ = this->create_wall_timer(100ms, std::bind(&SensorPublisher::timer_callback, this));

        }
    private:

        void timer_callback(){
            auto message{geometry_msgs::msg::Twist()}; // initialize as a Twist object

            message.linear.x{0.5};
            message.linear.z{0.1};

            //logging
            RCLCPP_INFO(this->get_logger(), "Publishing: linear.x=%.2f angular.z=%.2f", 
                            message.linear.x, message.angular.z);

            publisher_->publish(message);
        }

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
  };

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    auto node{std::make_shared<SensorPublisher>()};
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}