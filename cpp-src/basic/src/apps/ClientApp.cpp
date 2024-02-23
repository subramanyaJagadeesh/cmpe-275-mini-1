#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <string>
#include <random>
#include <numeric>

#include "socket/client.hpp"


// Function to generate a message of a given length
std::string generateMessageOfSize(size_t size) {
    std::string msg(size, 'x'); // Fill the message with 'x' characters
    return msg;
}


/**
 * @brief basic starting point 
 *
 *   
 */
int main(int argc, char **argv) {
  
   const int NUM_MASSAGE=1;  //Example: measure throughput over 100 messages
   std::vector<size_t> messageSizes = {1000}; // Example sizes

    std::stringstream msg;
    std::cout << "hello. My name is Inigo Montoya." << std::ends;
    for (size_t size : messageSizes) {
        std::string msg1 = generateMessageOfSize(size);
        std::cout << "Testing message of size: " << size << std::endl;

    // Connect and send a message to the C++ server
        try {
            basic::BasicClient cltCpp("anonymous", "127.0.0.1", 2000);
            cltCpp.connect();
            auto sendTime = std::chrono::steady_clock::now();

            cltCpp.sendMessage(msg1);
            std::cout << "Message sent to C++ server." << std::endl;
            double rtt = cltCpp.readACK(sendTime);
            std::cout << "RTT: " << rtt << " ms" << std::endl;
            
            /////Measuring Throuphut
            std::vector<double> rtts; // To store round-trip times for each message
        
            auto end =std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed = end - sendTime;

            size_t totalBytesSent = NUM_MASSAGE * size; // Assuming each message is of 'size' bytes
            double throughputBytesPerSecond = totalBytesSent / elapsed.count();

            
            // Optionally, calculate average RTT, display throughput and RTT statistics
            double totalRtt = std::accumulate(rtts.begin(), rtts.end(), 0.0);
            double averageRtt = rtts.empty() ? 0 : totalRtt / rtts.size();
            
            //std::cout << "Throughput: " << throughput << " messages/second" << std::endl;
            std::cout << "throughputBytesPerSecond: " << throughputBytesPerSecond << " Byte/second" << std::endl;
            std::cout << "Average RTT: " << averageRtt << " milliseconds" << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "Failed to send message to C++ server: " << e.what() << std::endl;
        }
        try {
            basic::BasicClient cltCpp("anonymous", "127.0.0.1", 3000);
            cltCpp.connect();
            auto sendTime = std::chrono::steady_clock::now();

            cltCpp.sendMessage(msg1);
            std::cout << "Message sent to Java server." << std::endl;
            double rtt = cltCpp.readACK(sendTime);
            std::cout << "RTT: " << rtt << " ms" << std::endl;
            //cltCpp.measureThroughput(100); // Example: measure throughput over 100 messages
            
            /////Measuring Throuphut
            std::vector<double> rtts; // To store round-trip times for each message
        
            auto end =std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed = end - sendTime;
            //double throughput = NUM_MASSAGE / elapsed.count(); // Calculate messages per second

            size_t totalBytesSent = NUM_MASSAGE * size; // Assuming each message is of 'size' bytes
            double throughputBytesPerSecond = totalBytesSent / elapsed.count();

            
            // Optionally, calculate average RTT, display throughput and RTT statistics
            double totalRtt = std::accumulate(rtts.begin(), rtts.end(), 0.0);
            double averageRtt = rtts.empty() ? 0 : totalRtt / rtts.size();
            
            std::cout << "throughputBytesPerSecond: " << throughputBytesPerSecond << " Byte/second" << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "Failed to send message to C++ server: " << e.what() << std::endl;
        }
        try {
            basic::BasicClient cltCpp("anonymous", "127.0.0.1", 4000);
            cltCpp.connect();
            auto sendTime = std::chrono::steady_clock::now();

            cltCpp.sendMessage(msg1);
            std::cout << "Message sent to Python server." << std::endl;
            double rtt = cltCpp.readACK(sendTime);
            std::cout << "RTT: " << rtt << " ms" << std::endl;
            
            /////Measuring Throuphut
            std::vector<double> rtts; // To store round-trip times for each message
        
            auto end =std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed = end - sendTime;

            size_t totalBytesSent = NUM_MASSAGE * size; // Assuming each message is of 'size' bytes
            double throughputBytesPerSecond = totalBytesSent / elapsed.count();

            
            // Optionally, calculate average RTT, display throughput and RTT statistics
            double totalRtt = std::accumulate(rtts.begin(), rtts.end(), 0.0);
            double averageRtt = rtts.empty() ? 0 : totalRtt / rtts.size();
            
            //std::cout << "Throughput: " << throughput << " messages/second" << std::endl;
            std::cout << "throughputBytesPerSecond: " << throughputBytesPerSecond << " Byte/second" << std::endl;
            // std::cout << "Average RTT: " << averageRtt << " milliseconds" << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "Failed to send message to C++ server: " << e.what() << std::endl;
        }
    } 

    // Wait a bit before exiting
    std::cout << "Sleeping a bit before exiting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
