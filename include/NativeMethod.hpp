 
#ifndef JJVM_NATIVEMETHOD_H
#define JJVM_NATIVEMETHOD_H

#include "JavaType.hpp"
#include "RuntimeEnv.hpp"

JType* ydk_lang_IO_print_str(RuntimeEnv* env, JType** args, int numArgs);
JType* ydk_lang_IO_print_I(RuntimeEnv* env, JType** args, int numArgs);
JType* ydk_lang_IO_print_C(RuntimeEnv* env, JType** args, int numArgs);

JType* java_lang_Math_random(RuntimeEnv* env, JType** args, int numArgs);
JType* java_lang_stringbuilder_append_I(RuntimeEnv* env, JType** args,
                                        int numArgs);
JType* java_lang_stringbuilder_append_C(RuntimeEnv* env, JType** args,
                                        int numArgs);
JType* java_lang_stringbuilder_append_str(RuntimeEnv* env, JType** args,
                                          int numArgs);
JType* java_lang_stringbuilder_append_D(RuntimeEnv* env, JType** args,
                                        int numArgs);
JType* java_lang_stringbuilder_tostring(RuntimeEnv* env, JType** args,
                                        int numArgs);

JType* java_lang_thread_start(RuntimeEnv* env, JType** args, int numArgs);
#endif
