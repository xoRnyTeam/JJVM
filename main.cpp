
#include <jjvm.hpp>

#include <iostream>

int main() {
    vm::jjvm jjvm("HelloWorld.class", {"./tests/", "../tests/", "../../tests/"});

    return 0;
}