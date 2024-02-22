
#include <thread>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sstream>
#include <iostream>
#include <numeric>


#include "socket/client.hpp"
#include "payload/basicbuilder.hpp"

basic::BasicClient::BasicClient(std::string name, std::string ipaddr, unsigned int port) {
      this->name = name;
      this->group = "public";
      this->ipaddr =ipaddr;
      this->portN = port;
      this->good = false;
      this->clt = -1;

      if (this->portN <= 1024)
         throw std::out_of_range("port must be greater than 1024");
}

void basic::BasicClient::stop() {
   std::cerr << "--> closing client connection" << std::endl;
   this->good = false;

   if (this->clt > -1) {
      ::close(this->clt);
      this->clt = -1;
   }
} 

void basic::BasicClient::join(std::string group){
   this->group = group;
}

/*void basic::BasicClient::readACK(std::__1::chrono::steady_clock::time_point sentTime){
   if (!this->good) return;
   while(this->good){
      char buffer[80] = {0};
      auto m = ::read(this->clt, buffer, 80);
      if(m == -1){
         continue;
      } else if(errno == ETIMEDOUT){
         continue;
      } else{
         std::cerr << "Ack recieved in " << (std::chrono::high_resolution_clock::now() - sentTime).count();
      }  
   }
}*/

double basic::BasicClient::readACK(std::chrono::steady_clock::time_point sentTime) {
    if (!this->good) return -1.0; // Return -1 if not connected

    while(this->good) {
        char buffer[80] = {0};
        auto m = ::read(this->clt, buffer, 80); 

        if(m == -1) {
            // Handle read error
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        } else if(errno == ETIMEDOUT) {
            // Handle timeout
            continue;
        } else {
            // ACK received, calculate RTT
            auto recvTime = std::chrono::steady_clock::now();
            auto rtt = std::chrono::duration_cast<std::chrono::milliseconds>(recvTime - sentTime).count();
            std::cerr << "Ack received in " << rtt << " ms" << std::endl;
            return rtt; // Return RTT in milliseconds
        }
    }
    return -1.0; // In case loop exits without receiving ACK, indicate an error
}


//Measure Throughput
void basic::BasicClient::measureThroughput(int numMessages) {
    std::vector<double> rtts; // To store round-trip times for each message
    auto start = std::chrono::steady_clock::now();
    
    for (int i = 0; i < numMessages; ++i) {
        auto sentTime = std::chrono::steady_clock::now();
        sendMessage("OUR MESSAGE!!"); //Whatever Message planning to send
        double rtt = readACK(sentTime);
        if (rtt >= 0) { // Ensure RTT was successfully measured
            rtts.push_back(rtt);
        }
    }
    
    auto end =std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double throughput = numMessages / elapsed.count(); // Calculate messages per second
    
    // Optionally, calculate average RTT, display throughput and RTT statistics
    double totalRtt = std::accumulate(rtts.begin(), rtts.end(), 0.0);
    double averageRtt = rtts.empty() ? 0 : totalRtt / rtts.size();
    
    std::cout << "Throughput: " << throughput << " messages/second" << std::endl;
    std::cout << "Average RTT: " << averageRtt << " milliseconds" << std::endl;
}



void basic::BasicClient::sendMessage(std::string m) {
   if (!this->good) return;

   basic::Message msg(this->name,this->group,m);
   basic::BasicBuilder bldr;
   auto payload = bldr.encode(msg); 
   auto plen = payload.length();

   while (this->good) {
      auto n = ::write(this->clt, payload.c_str(), plen);
      //auto n = ::send(this->clt, payload.c_str(), plen);
      
      if (n == -1) {
         std::cerr << "--> send() error for " << m << ", n = " << n << ", errno = " << errno << std::endl;
      } else if ( errno == ETIMEDOUT) { 
         // @todo send portion not sent!
         continue;
      } else if (payload.length() != (std::size_t)n) {
         // @todo hmmmm, houston we may have a problem
         std::stringstream err;
         err << "failed to fully send(), err = " << errno << std::endl;
         throw std::runtime_error(err.str());
      } else 
         std::cerr << "sent: " << payload << ", size: " << plen << ", errno: " << errno << std::endl;
   
      break;
   }
}

void basic::BasicClient::connect() {
   if (this->good) return;

   std::cerr << "connecting..." << std::endl;

   this->clt = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if (this->clt < 0) {
      std::stringstream err;
      err << "failed to create socket, err = " << errno << std::endl;
      throw std::runtime_error(err.str());
   }

   struct sockaddr_in serv_addr;
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = inet_addr(this->ipaddr.c_str());
   serv_addr.sin_port = htons(this->portN);

   auto stat = inet_pton(AF_INET, this->ipaddr.c_str(), &serv_addr.sin_addr);
   if (stat < 0) {
      throw std::runtime_error("invalid IP address");
   }
   
   stat = ::connect(this->clt, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   if (stat < 0) {
      std::stringstream err;
      err << "failed to connect() to server, err = " << errno << std::endl;
      throw std::runtime_error(err.str());
   }

   this->good = true;
}
