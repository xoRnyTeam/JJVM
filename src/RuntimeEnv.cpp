

#include "GC.hpp"
#include "RuntimeEnv.hpp"
#include "ClassSpace.hpp"
#include "JavaHeap.hpp"

RuntimeEnv runtime; // JJVM runtime

void RuntimeEnv::Init(const std::string &lib_path) {
    cs = std::make_unique<ClassSpace>(lib_path);
    gc = std::make_unique<GC>();
    heap = std::make_unique<JavaHeap>();
}
