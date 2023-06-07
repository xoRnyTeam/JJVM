#ifndef _JJVM_ALLOCATOR_H
#define _JJVM_ALLOCATOR_H

#include <memory>
#include <unordered_set>

#include "Option.hpp"
#include "RuntimeEnv.hpp"

template <class T>
struct HeapAllocator {
    typedef T value_type;
    HeapAllocator() = default;
    HeapAllocator(const HeapAllocator& rhs) {
        this->thresholdVal = rhs.thresholdVal;
    }
    HeapAllocator& operator=(const HeapAllocator& rhs) {
        this->thresholdVal = rhs.thresholdVal;
        return *this;
    }

    template <class U>
    constexpr HeapAllocator(const HeapAllocator<U>&) noexcept {}
    T* allocate(size_t n) {
        if (n > size_t(-1) / sizeof(T)) throw std::bad_alloc();
        if (auto p = static_cast<T*>(malloc(n * sizeof(T)))) {
            thresholdVal += n * sizeof(T);
            if (thresholdVal >= JJVM_GC_THRESHOLD_VALUE) {
                // runtime.gc->notifyGC();
                thresholdVal = 0;
            }
            return p;
        }
        throw std::bad_alloc();
    }
    void deallocate(T* p, size_t val) noexcept {
        free(p);
        thresholdVal -= val;
    }

private:
    size_t thresholdVal = 0;
};

#endif  // _JJVM_ALLOCATOR_H