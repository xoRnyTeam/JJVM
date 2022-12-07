#pragma once 

#include <unordered_map>
#include <vector>

namespace vm 
{

class Heap final {
    struct HeapInfo final {
        size_t member_size = 0;
        size_t num_members = 0;
        std::vector<uint8_t> data;
    }; // struct HeapInfo

private:
    std::unordered_map<size_t, HeapInfo> m_heap;
    size_t m_counter = 0;

public:
    size_t allocate(size_t member_size, size_t count) {
        size_t id = m_counter++;
        HeapInfo info;
        info.member_size = member_size;
        info.num_members = count;
        info.data.resize(member_size * count);

        m_heap[id] = std::move(info);
        return id;
    }

    void free(size_t id) {
        m_heap.erase(id);
    }

    size_t get_nmembers(size_t id) const { return m_heap.at(id).num_members; }

    template<typename T>
    void store(size_t id, size_t place, const T& val) {
        auto&& heap = m_heap.at(id);
        // OMG
        *reinterpret_cast<T*>(&heap.data.at(heap.member_size * place)) = val;
    }

    template<typename T>
    T load(size_t id, size_t place) const {
        auto&& heap = m_heap.at(id);
        // OMG 2
        return *reinterpret_cast<T*>(const_cast<uint8_t*>(&heap.data.at(heap.member_size * place)));
    }

}; // class Heap

} // namespace vm