
#include "socket/server.hpp"

/**
 * @brief basic starting point 
 *
 *      Author: gash
 */
int main(int argc, char **argv) {
    //basic::BasicServer javaSvr("127.0.0.1", 3000);
    //javaSvr.start();

    basic::BasicServer cppSvr("127.0.0.1", 2000);
    cppSvr.start();
    
    basic::BasicServer pythonSvr("127.0.0.1", 4000);
    pythonSvr.start();

    //basic::BasicServer cppSvr("127.0.0.1", 2000);
    //cppSvr.start();
    
}
