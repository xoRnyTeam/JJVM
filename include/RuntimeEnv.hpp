 
#ifndef JJVM_YRUNTIME_H
#define JJVM_YRUNTIME_H

#include <string>
#include <unordered_map>
#include <memory>

struct JType;
class JavaFrame;
class JavaHeap;
class ClassSpace;
class GC;

struct RuntimeEnv {
    RuntimeEnv() = default;

    void Init(const std::string &lib_path);

    std::unique_ptr<ClassSpace> cs;
    std::unique_ptr<JavaHeap> heap;
    std::unique_ptr<GC> gc;
    std::unordered_map<std::string, JType* (*)(RuntimeEnv* env, JType**, int)>
        nativeMethods;
};
extern RuntimeEnv runtime;
#endif  // !JJVM_YRUNTIME_H
