
#include <jjvm.hpp>
#include <cstring>
#include <iostream>
//
#include "timer.hpp"

void parse(int argc, char** argv, std::string& s) {
    if (argc == 1) {
        std::cout << "Error. It is necessary to specify the file class name at the input" << std::endl;
        exit(1);
    } else if (argc == 2) {
        if ( std::strstr(argv[1], ".class")) {
            s = argv[1];
        } else {
            std::cout << "Error. File must have the extension class" << std::endl;
	    exit(2);
        }
    } else {
	    std::cout << "Error. incorrect number of input arguments" << std::endl;
	    std::cout << "Example: Usage ./jjvm Middle.class" << std::endl;
	    exit(3);
    }
}

int main(int argc, char** argv) {
    std::string name;
    parse(argc, argv, name);
    vm::jjvm jjvm(name, {"./tests/", "../tests/", "../../tests/"});

    timer::Timer timer{};
    jjvm.execute();
    std::cout << timer.elapsed<timer::Timer::microsecs>() << " microseconds\n";

    std::cout << "END!" << std::endl;
    
    return 0;
}
