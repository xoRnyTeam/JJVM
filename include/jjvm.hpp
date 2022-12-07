#pragma once

#include <string>
#include <vector>
#include <stack>
#include <functional>
#include <array>

#include "ClassFile.hpp"
#include "Heap.hpp"
#include "memory.hpp"

namespace vm
{
    
/// @brief 
enum AccessFlags : int16_t {
	ACC_NONE         = 0x0000,
	ACC_PUBLIC       = 0x0001,
	ACC_PRIVATE      = 0x0002,
	ACC_PROTECTED    = 0x0004,
	ACC_STATIC       = 0x0008,
	ACC_FINAL        = 0x0010,
	ACC_SUPER        = 0x0020,
	ACC_SYNCHRONIZED = 0x0020,
	ACC_VOLATILE     = 0x0040,
	ACC_BRIDGE       = 0x0040,
	ACC_TRANSIENT    = 0x0080,
	ACC_VARARGS      = 0x0080,
	ACC_NATIVE       = 0x0100,
	ACC_INTERFACE    = 0x0200,
	ACC_ABSTRACT     = 0x0400,
	ACC_STRICT       = 0x0800,
	ACC_SYNTHETIC    = 0x1000,
	ACC_ANNOTATION   = 0x2000,
	ACC_ENUM         = 0x4000
};

class jjvm final {
    ClassFile         m_class;
    Heap              m_heap;
    std::stack<Frame> m_frames;

    std::array<std::function<void()>, 0xFF> m_handlers;

public:
    /// @brief 
    /// @param class_name 
    /// @param class_path 
    jjvm(const std::string &class_name, const std::vector< std::string > &class_path);

public:
    /// @brief init class
    void execute();

private:
    void methodCall(const std::string &name, const std::string &descriptor, int16_t flags);

    std::shared_ptr<AttributeBase> jjvm::getAttr(std::vector<std::shared_ptr<AttributeBase>> & attrs, AttributeTag tag) const;

    Value resolveConstant(uint16_t id);

    // handlers
    //=--------
    void intiHandlers();

    void opnop();
    void opiconst_0();
    void opiconst_1();

    void opladd();
}; // class jjvm

} // namespace vm