 
// #include "../gc/GC.h"

#include "RuntimeEnv.hpp"
#include "ClassSpace.hpp"
#include "JavaHeap.hpp"

RuntimeEnv runtime;  // JJVM runtime

RuntimeEnv::RuntimeEnv() {
    heap = new JavaHeap;
   // gc = new ConcurrentGC;
}

RuntimeEnv::~RuntimeEnv() {
    delete cs;
    delete heap;
}
