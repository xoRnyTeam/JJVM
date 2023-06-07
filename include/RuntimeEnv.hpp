 
#ifndef JJVM_YRUNTIME_H
#define JJVM_YRUNTIME_H

#include <string>
#include <unordered_map>

struct JType;
class JavaFrame;
class JavaHeap;
class ClassSpace;

struct RuntimeEnv {
    RuntimeEnv();
    ~RuntimeEnv();

    ClassSpace* cs;
    JavaHeap* heap;
    std::unordered_map<std::string, JType* (*)(RuntimeEnv* env, JType**, int)>
        nativeMethods;
};

extern RuntimeEnv runtime;
#endif  // !JJVM_YRUNTIME_H
