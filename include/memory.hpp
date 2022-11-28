#pragma once

#include <stack>
#include <vector>

namespace vm
{

union Value {
	int32_t i;
	int64_t l;
	float   f;
	double  d;
	// TODO: Heap pointer
};

/// @brief Info about code section
struct CodeInfo {
    uint16_t stack_size;
    uint16_t locals_size;
    std::vector<uint8_t> code;
    // TODO?: Exceprions
    // TODO?: Atributes
};

/// @brief Contain vm-runtime info about function frame
class Frame final {
    // TODO: ClassInfo

    // TODO: local variables
    // std::vector<Value> m_lockals;

    // tsack for operands
    std::stack<Value> m_stack;

    // TODO: instractions - code of function
    // TODO: program counter
public:
    // TODO: execute(???);
    
}; // class Frame

} // namespace vm