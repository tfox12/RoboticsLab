#include "network.h"

#include <iostream>
#include <string>

int main()
{
    std::cout << "Waiting for a connection from the Pi" << std::endl;
    Server::Socket * client = Server::NetworkInterface::instance()->accept_new_connection();
    
    std::string command;
    std::cout << "send the robot commands: forward, back, left, right. Or \"end\" to stop";
    do
    {
        std::cin >> command;
        if( !( command == "forward" 
            || command == "back"
            || command == "left"
            || command == "right"
            || command == "end"
            ))
        {
            std::cerr << "invalid command" << std::endl;
        }
        else
        {
            client->send_all(command);
        }
    }
    while(command != "end");
}

