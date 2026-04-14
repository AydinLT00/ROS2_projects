#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

#include <memory>

class SubscriberNode : public rclcpp::Node {
    public:
        SubscriberNode() : Node("subscriber_node"){

            subscriber_ = this->create_subscription<geometry_msgs::msg::Twist>("cmd_vel",10,std::bind(&SubscriberNode::topic_callback, this, std::placeholders::_1) );
        }
    
    private:
        void topic_callback(const geometry_msgs::msg::Twist::SharedPtr msg) const {

            RCLCPP_INFO(this->get_logger(), "receive: %.2f, %.2f", 
                        msg->linear.x, msg->linear.z);
        }

        rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscriber_;
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SubscriberNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
