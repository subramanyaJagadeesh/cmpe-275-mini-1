#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <string>

#include "socket/client.hpp"

/**
 * @brief basic starting point 
 *
 *      Author: gash
 */
int main(int argc, char **argv) {
    /*basic::BasicClient clt;
    clt.connect();

    std::stringstream msg;
    msg << "hello. My name is inigo montoya." << std::ends;
    clt.sendMessage(msg.str());
     
    std::cout << "sleeping a bit before exiting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    
    */
    std::stringstream msg;
    msg << "hello. My name is Inigo Montoya." << std::ends;
    
    // Connect and send a message to the C++ server
    try {
        basic::BasicClient cltCpp("anonymous", "127.0.0.1", 2000);
        cltCpp.connect();
        cltCpp.sendMessage(msg.str());
        std::cout << "Message sent to C++ server." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to send message to C++ server: " << e.what() << std::endl;
    }
    
    // Connect and send a message to the Java server
    /*try {
        basic::BasicClient cltJava("anonymous", "127.0.0.1", 3000);
        cltJava.connect();
        cltJava.sendMessage(msg.str());
        std::cout << "Message sent to Java server." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to send message to Java server: " << e.what() << std::endl;
    }
    */
    // Connect and send a message to the Python server
    /*try {
        basic::BasicClient cltJava("anonymous", "127.0.0.1", 4000);
        cltJava.connect();
        cltJava.sendMessage(msg.str());
        std::cout << "Message sent to Python server." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to send message to Java server: " << e.what() << std::endl;
    }*/
    // Wait a bit before exiting
    std::cout << "Sleeping a bit before exiting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
