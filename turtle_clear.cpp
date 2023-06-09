#include <iostream>
// dependencies
#include <rclcpp/rclcpp.hpp>
#include <turtle_clear.hpp> 
#include <memory>


turtleControl::turtleControl(){
    // node initialization
    auto node = rclcpp::Node::make_shared("controlTurtles"); // only one node "program" to control everything

    //initialize the server and the client for component 1 
    auto serviceKill = node-> rclcpp::create_service<turtlesim::srv::Kill>("clear_turtles");
    auto clientKIll = node -> rclcpp::create_client<turtlesim::srv::Kill> ("clear_turtles", std::bind(&turtleControl::callback, this, std::placeholders::_1, std::placeholders::_2)) ;

}       

void turtleControl::killCallback (const std::shared_ptr<turtlesim::srv::Kill::Request> request,
                                  std::shared_ptr<turtlesim::srv::Kill::Response> response){

   
    // Wait for the service to become available
    if (!clientKill->wait_for_service(std::chrono::seconds(2)))
    {
        RCLCPP_ERROR(node->get_logger(), "error - cannot find the service");
        return;
    }

    // Create the request - are the requests for services done in function definitions??
    auto request_to_kill = std::make_shared<turtlesim::srv::Kill::Request>();
    request->name = ""; // kill all turtles

    // Send the request asynchronously and wait for the response
    auto result_future = clientKill->async_send_request(request_to_kill);

    //if not successful, provide an error message to the user and remove the request
    if (rclcpp::spin_until_future_complete(node, result_future) !=
        rclcpp::executor::FutureReturnCode::SUCCESS){
        RCLCPP_ERROR(node->get_logger(), "service call failed :(");
        clientKill->remove_pending_request(result_future);
        return;
    }
    
    //if reached here, response has been created
    //when the result of the request available, provide that result to the variable "result"
    auto result = result_future.get(); //result is the response to the request
    rclcpp::spin(node); //keep the node running - restart the main event loop
    rclcpp::shutdown();
    return;
}


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  turtleControl(); //initialize the node for the program

  //killCallback(); //call the function to kill all the turtles

  //note: you do not need to call the kill function separetly since
  //when you create a service, it is automatically invoked???

  rclcpp::spin(node);
  rclcpp::shutdown();
}