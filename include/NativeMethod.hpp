 
#ifndef JJVM_NATIVEMETHOD_H
#define JJVM_NATIVEMETHOD_H

#include "JavaType.hpp"
#include "RuntimeEnv.hpp"

JType* java_lang_IO_print_str(RuntimeEnv* env, JType** args, int numArgs);
JType* java_lang_IO_print_I(RuntimeEnv* env, JType** args, int numArgs);
JType* java_lang_IO_print_C(RuntimeEnv* env, JType** args, int numArgs);
JType* java_lang_IO_print_D(RuntimeEnv* env, JType** args, int numArgs);
#endif
