#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>

#include <chrono>
#include <memory>

using namespace std::chrono_literals;

class TestNode : public rclcpp::Node{
    public:
      TestNode() : Node("testNode"){
        publisher_ = this->create_publisher<geometry_msgs::msg::Point>("point", 10);
        timer_ = this->create_wall_timer(100ms, std::bind(&TestNode::timer_callback, this));
      }  

    private:
      void timer_callback(){
        auto message{geometry_msgs::msg::Point()};
        message.x = 1;
        message.y = 2;

        RCLCPP_INFO(this->get_logger(), "Publishing: linear.x=%.2f linear.y=%.2f", 
                            message.x, message.y);

        publisher_->publish(message);
      }

        rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TestNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}