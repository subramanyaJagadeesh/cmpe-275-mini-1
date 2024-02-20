
#include "socket/server.hpp"

/**
 * @brief basic starting point 
 *
 *      Author: gash
 */
int main(int argc, char **argv) {
    basic::BasicServer svrCpp;
    basic::BasicServer svrjava("127.0.0.1",2000);
    svrCpp.start();
    svrjava.start();
}