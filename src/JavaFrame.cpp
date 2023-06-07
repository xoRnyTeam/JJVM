 
#include "JavaFrame.hpp"

#include <cstring>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <typeinfo>

JavaFrame::~JavaFrame() {
    while (top_) {
        auto* temp = top_;
        top_ = top_->next;
        delete temp;
    }
}

void JavaFrame::pushFrame(int maxLocal, int maxStack) {
    auto* slots = new Slots{maxLocal, maxStack};
    slots->next = top_;
    top_ = slots;
}

void JavaFrame::popFrame() {
    auto* temp = top_;
    top_ = top_->next;
    delete temp;
}

Slots::Slots(int maxLocal, int maxStack)
    : maxLocal(maxLocal),
      maxStack(maxStack),
      next(nullptr),
      localSlots(nullptr),
      stackSlots(nullptr) {
    if (maxLocal > 0) {
        localSlots = new JType*[maxLocal];
        memset(localSlots, 0, sizeof(JType*) * maxLocal);
    }
    if (maxStack > 0) {
        stackSlots = new JType*[maxStack];
        memset(stackSlots, 0, sizeof(JType*) * maxStack);
    }

    stackTop = 0;
}

Slots::~Slots() {
    printf("Slot destructoq!!!\n");
    // for (size_t i = 0; i < maxStack; ++i)
    //     if (stackSlots[i])
    //         delete stackSlots[i];
    delete[] stackSlots;

    // for (size_t i = 0; i < maxLocal; ++i)
    //     if (localSlots[i])
    //         delete localSlots[i];
    delete[] localSlots;
}

void Slots::setLocalVariable(u1 index, JType* var) {
    if (index > maxLocal) {
        throw std::logic_error("invalid local variable slot index");
    }
    localSlots[index] = var;
}

void Slots::dump() {
    auto* temp = next;
    while (temp != nullptr) {
        printf("stack slots:%d, local variables:%d\n", temp->stackTop,
               maxLocal);
        temp = temp->next;
    }
}
