
#include <jjvm.hpp>

#include <iostream>

int main() {
    vm::jjvm jjvm("Middle.class", {"./tests/", "../tests/", "../../tests/"});

    jjvm.execute();

    std::cout << "END!" << std::endl;
    
    return 0;
}