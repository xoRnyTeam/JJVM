 
#ifndef JJVM_JJVM_H
#define JJVM_JJVM_H

#include "Interpreter.hpp"
#include "RuntimeEnv.hpp"

extern RuntimeEnv runtime;

struct JJVM {
    explicit JJVM();

    static void callMain(const std::string& name);
    static void initialize(const std::string& libPath);
};

#endif  // JJVM_JJVM_H
