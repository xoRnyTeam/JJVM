
#include "NativeMethod.hpp"

#include <future>
#include <iostream>
#include <random>
#include <string>

#include "ClassSpace.hpp"
#include "JavaClass.hpp"
#include "JavaHeap.hpp"
#include "JJVM.hpp"

JType* java_lang_IO_print_str(RuntimeEnv* env, JType** args, int numArgs) {
    JObject* str = (JObject*)args[0];
    if (nullptr != str) {
        auto fields = env->heap->getFields(str);
        JArray* chararr = (JArray*)fields[0];
        auto lengthAndData = env->heap->getElements(chararr);
        char* s = new char[lengthAndData.first + 1];
        for (int i = 0; i < lengthAndData.first; i++) {
            s[i] = (char)((JInt*)lengthAndData.second[i])->val;
        }
        s[lengthAndData.first] = '\0';
        std::cout << s;
        delete[] s;
    } else {
        std::cout << "null";
    }

    return nullptr;
}

JType* java_lang_IO_print_I(RuntimeEnv* env, JType** args, int numArgs) {
    JInt* num = (JInt*)args[0];
    std::cout << num->val;
    return nullptr;
}

JType* java_lang_IO_print_C(RuntimeEnv* env, JType** args, int numArgs) {
    JInt* num = (JInt*)args[0];
    std::cout << (char)num->val;
    return nullptr;
}

JType* java_lang_IO_print_D(RuntimeEnv* env, JType** args, int numArgs) {
    JDouble* num = (JDouble*)args[0];
    std::cout << (double)num->val;
    return nullptr;
}
