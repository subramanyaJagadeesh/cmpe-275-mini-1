
#include "socket/server.hpp"

/**
 * @brief basic starting point 
 *
 *      Author: gash
 */
int main(int argc, char **argv) {
    basic::BasicServer javaSvr("192.168.1.100", 8080);
    javaSvr.start();

    basic::BasicServer cppSvr;
    cppSvr.start();
}