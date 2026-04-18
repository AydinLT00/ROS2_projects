#include <chrono>
#include <memory>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class CarterCommander : public rclcpp::Node {
	public:
		CarterCommander() : Node("carter_commander") {
			
			publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel",10);
			timer_ = this->create_wall_timer(100ms, 
				std::bind(&CarterCommander::velocity_callback, 
				this));
			
			RCLCPP_INFO(this->get_logger(), "CarterCommander Initialized...");
}

	private:
		rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
		rclcpp::TimerBase::SharedPtr timer_;
		
		void velocity_callback(){
			auto message = geometry_msgs::msg::Twist();
			
			message.linear.x = 0.5;
			message.angular.z = 0.2;

			publisher_->publish(message);}
};

int main(int argv, char * argc[]){
	rclcpp::init(argv, argc);
	auto node = std::make_shared<CarterCommander>();
	rclcpp::spin(node);
	rclcpp::shutdown();

	return 0;}
