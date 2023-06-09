#include <iostream>
// dependencies
#include <rclcpp/rclcpp.hpp>
#include <turtlesim/srv/kill.hpp> 
#include <memory>

class turtleControl : public rclcpp::Node{ //create turtleControl class (to implement the challenge functionalities) and inherit the node class of the ros client lib (rcl)

    public:
    turtleControl();
    ~turtleControl();

    void killCallback(const std::shared_ptr<turtlesim::srv::Kill::Request> request,
                      std::shared_ptr<turtlesim::srv::Kill::Response> response);


    private:
    //server and client for component 1 - killing all turtles
    rclcpp::Service<turtlesim::srv::Kill>::SharedPtr serviceKill;
    rclcpp::Client<turtlesim::srv::Kill>::SharedPtr clientKill;

}
