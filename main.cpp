
#include <jjvm.hpp>

#include <iostream>

int main() {
    vm::jjvm jjvm("HelloWorld.class", {"./tests/", "../tests/", "../../tests/"});

    jjvm.execute();
    
    return 0;
}