 
#ifndef CALLSITE_HPP
#define CALLSITE_HPP

#include "JavaClass.hpp"

struct CallSite {
    explicit CallSite();

    bool isCallable() const { return callable; }

    static CallSite makeCallSite(const JavaClass* jc, MethodInfo* m);

    const JavaClass* jc;
    u2 accessFlags;
    u1* code;
    u4 codeLength;
    u2 maxStack;
    u2 maxLocal;
    u2 exceptionLen;
    ExceptionTable* exception;
    bool callable;
};

#endif  // !CALLSITE_HPP
