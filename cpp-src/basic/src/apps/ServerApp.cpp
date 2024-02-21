
#include "socket/server.hpp"

/**
 * @brief basic starting point 
 *
 *      Author: gash
 */
int main(int argc, char **argv) {
    basic::BasicServer cppSvr("127.0.0.1", 2000);
    cppSvr.start();
}
