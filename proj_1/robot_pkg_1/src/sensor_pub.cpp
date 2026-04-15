#include <chrono>
#include <functional>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <std_msgs/msg/string.hpp>
#include "robot_pkg_1/srv/set_velocity.hpp"

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

        service_ = this->create_service<robot_pkg_1::srv::SetVelocity>(
            "set_velocity",
            std::bind(&SensorPublisher::handle_set_velocity, this,
                std::placeholders::_1, std::placeholders::_2));
                
            RCLCPP_INFO(this->get_logger(), "Service set_vel is ready");

        }
    private:
        rclcpp::Service<robot_pkg_1::srv::SetVelocity>::SharedPtr service_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        double linear_x_;
        
        void timer_callback(){
            auto message{geometry_msgs::msg::Twist()}; // initialize as a Twist object

            message.linear.x = linear_x_;
            message.linear.z = 0.1;

            //logging
            RCLCPP_INFO(this->get_logger(), "Publishing: linear.x=%.2f angular.z=%.2f", 
                            message.linear.x, message.linear.z);

            publisher_->publish(message);
        }

        

        
        void handle_set_velocity(
            const std::shared_ptr<robot_pkg_1::srv::SetVelocity::Request> request,
            std::shared_ptr<robot_pkg_1::srv::SetVelocity::Response> response){
        {
            // Validate input (optional)
            if (request->linear_x < 0.0 || request->linear_x > 2.0) {
            response->success = false;
            response->message = "Velocity must be between 0.0 and 2.0";
            RCLCPP_WARN(this->get_logger(), "Invalid velocity requested: %.2f", request->linear_x);
            return;
            }
            
            linear_x_ = request->linear_x;
            response->success = true;
            response->message = "Velocity updated to " + std::to_string(linear_x_);
            RCLCPP_INFO(this->get_logger(), "Service called: velocity set to %.2f", linear_x_);
        }

        
        
    }
    };

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    auto node{std::make_shared<SensorPublisher>()};
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}