#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <string>

#include "socket/client.hpp"


int main(int argc, char **argv) {
    basic::BasicClient clt;
    clt.connect();

    std::stringstream msg;
    msg << "Hello, Connecting to the java Server!" << std::ends;
    clt.sendMessage(msg.str());
     
    std::cout << "sleeping a bit before exiting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
