
#include <jjvm.hpp>
#include <ClassFile.hpp>


int main() {

    vm::ClassFile::create("./tests/HelloWorld.class");

    return 0;
}