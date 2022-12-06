#pragma once

#include <stack>
#include <vector>

#include "FieldTypes.hpp"

namespace vm
{

union Value {
	int32_t i;
	int64_t l;
	float   f;
	double  d;
	size_t heapID;
};

/// @brief Contain vm-runtime info about function frame
class Frame final {
    // TODO: ClassInfo

    // local variables
    std::vector<Value> m_lockals;

    // tsack for operands
    std::stack<Value> m_stack;
    size_t m_maxStack = 0; // UNUSED!

public:
    // program counter
    uint16_t pc = {};

    // array of instractions
    std::shared_ptr<Code_attribute> code;

public:
    Frame(size_t max_locals, size_t max_stack) {
        m_lockals.resize(max_locals);
        m_maxStack = max_stack;
    }
    void stackPush(Value value);
    void stackPop();
    Value stackTop() const;
    
    void lockalStore(uint16_t id, Value value);
    Value lockalLoad(uint16_t id) const;


}; // class Frame

} // namespace vm