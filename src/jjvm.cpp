#include <fstream>
#include <iostream>
#include <jjvm.hpp>

#include "GC.hpp"
#include "ClassSpace.hpp"
#include "JavaClass.hpp"
#include "JavaHeap.hpp"
#include "NativeMethod.hpp"
#include "Option.hpp"
#include "RuntimeEnv.hpp"
#include "Utils.hpp"

namespace vm {

static const char *((nativeFunctionTable[])[4]) = {
    {"lang/IO", "print", "(Ljava/lang/String;)V",
     reinterpret_cast<char *>(java_lang_IO_print_str)},
    {"lang/IO", "print", "(I)V",
     reinterpret_cast<char *>(java_lang_IO_print_I)},
    {"lang/IO", "print", "(C)V",
     reinterpret_cast<char *>(java_lang_IO_print_C)},
    {"lang/IO", "print", "(D)V",
     reinterpret_cast<char *>(java_lang_IO_print_D)},
};

jjvm::jjvm(const std::string &class_path) {
  runtime.Init(class_path);

  std::cout << class_path << std::endl;
  // register native methods
  int p = sizeof nativeFunctionTable / sizeof nativeFunctionTable[0];
  for (int i = 0; i < p; i++) {
    registerNativeMethod(
        nativeFunctionTable[i][0], nativeFunctionTable[i][1],
        nativeFunctionTable[i][2],
        reinterpret_cast<JType *(*)(RuntimeEnv *, JType **, int)>(
            const_cast<char *>(nativeFunctionTable[i][3])));
  }
}

void jjvm::execute(const std::string &main_class) {
  // init class file
  //=---------------
  auto *jc = runtime.cs->loadClassIfAbsent(main_class);
  std::cout << main_class << std::endl;
  runtime.cs->linkClassIfAbsent(main_class);

  Interpreter exec;
  runtime.cs->initClassIfAbsent(exec, main_class);
  exec.invokeByName(jc, "main", "([Ljava/lang/String;)V");
}

std::shared_ptr<AttributeBase>
jjvm::getAttr(std::vector<std::shared_ptr<AttributeBase>> &attrs,
              AttributeTag tag) const {
  std::shared_ptr<AttributeBase> res = nullptr;
  for (auto &&attr : attrs) {
    if (attr->getTag() == tag) {
      res = attr;
      break;
    }
  }
  return res;
}

} // namespace vm