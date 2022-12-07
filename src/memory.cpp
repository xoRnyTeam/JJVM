#include <memory.hpp>

namespace vm
{

Frame::Frame(size_t max_locals, size_t max_stack) {
    m_lockals.resize(max_locals);
    m_maxStack = max_stack;
}

void Frame::stackPush(Value value) {
    m_stack.push(value);
}

void Frame::stackPop() {
    m_stack.pop();
}

Value Frame::stackTop() const {
    return m_stack.top();
}

void Frame::localStore(uint16_t id, Value value) {
    m_lockals.at(id) = value;
}

Value Frame::localLoad(uint16_t id) const {
    return m_lockals.at(id);
}

} // namespace vm