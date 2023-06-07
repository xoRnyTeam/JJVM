 
#ifndef JJVM_JAVAHEAP_H
#define JJVM_JAVAHEAP_H

#include <map>
#include <string>
#include <vector>

#include "Allocator.hpp"
#include "JavaType.hpp"
#include "Utils.hpp"

template <typename Type>
class Container {
    friend class GC;

public:
    explicit Container() = default;
    virtual ~Container() {}

    virtual size_t place();
    void remove(size_t offset);
    Type& find(size_t offset) { return data.find(offset)->second; }
    bool has(size_t offset) { return data.find(offset) != data.end(); }

protected:
    auto& getContainer() { return data; }

private:
    std::map<size_t, Type, std::less<>, HeapAllocator<std::pair<const size_t, Type>>> data;
};

template <typename Type>
void Container<Type>::remove(size_t offset) {
    if (data.find(offset) != data.end()) {
        data.erase(offset);
    }
}

template <typename Type>
size_t Container<Type>::place() {   
    size_t lastOffset = 0;
    if (!data.empty()) {
        lastOffset = (--data.end())->first;
    }
    data.insert(make_pair(lastOffset + 1, Type{}));
    return lastOffset + 1;
}


using InternalArray = std::pair<size_t, JType**>;
struct ArrayContainer : public Container<InternalArray> {
    ~ArrayContainer() override {
        for (auto intPairPair : getContainer()) {
            for (size_t i = 0; i < intPairPair.second.first; i++) {
                delete intPairPair.second.second[i];
            }
            delete[] intPairPair.second.second;
        }
    }
};

using InternalObject = std::vector<JType*>;
struct ObjectContainer : public Container<InternalObject> {
    ~ObjectContainer() override {
        for (auto intVecPair : getContainer()) {
            for (auto ptr : intVecPair.second) {
                delete ptr;
            }
        }
    }
};

class JavaHeap {
    friend class Interpreter;
    friend class GC;

public:
    JavaHeap() = default;

    JObject* createObject(const JavaClass& javaClass);
    JArray* createPODArray(int atype, int length);
    JArray* createObjectArray(const JavaClass& jc, int length);
    JArray* createCharArray(const std::string& source, size_t length);

    // template<typename T>
    // JType * createJType() {
    //     JType* type = new T;
    //     auto offset = objectContainer.place();
    //     vector<JType*> instanceFields = {type};

    //     objectContainer.find(offset) = instanceFields;
    //     return type;
    // } 

    auto getFieldByName(const JavaClass* jc, const std::string& name,
                        const std::string& descriptor, JObject* object) {
        return getFieldByNameImpl(jc, object->jc, name, descriptor, object, 0);
    }
    void putFieldByName(const JavaClass* jc, const std::string& name,
                        const std::string& descriptor, JObject* object,
                        JType* value) {
        putFieldByNameImpl(jc, object->jc, name, descriptor, object, value, 0);
    }
    void putFieldByOffset(const JObject& object, size_t fieldOffset,
                          JType* value) {
        objectContainer.find(object.offset)[fieldOffset] = value;
    }
    auto getFieldByOffset(const JObject& object, size_t fieldOffset) {
        return objectContainer.find(object.offset)[fieldOffset];
    }
    auto getFields(JObject* object) {
        return objectContainer.find(object->offset);
    }

    void putElement(const JArray& array, size_t index, JType* value) {
        arrayContainer.find(array.offset).second[index] = value;
    }
    auto getElement(const JArray& array, size_t index) {
        return arrayContainer.find(array.offset).second[index];
    }
    auto getElements(JArray* array) {
        return arrayContainer.find(array->offset);
    }

    void removeArray(size_t offset) {
        arrayContainer.remove(offset);
    }
    void removeObject(size_t offset) {
        objectContainer.remove(offset);
    }

private:
    void createSuperFields(const JavaClass& javaClass, const JObject* object);

    JType* getFieldByNameImpl(const JavaClass* desireLookup,
                              const JavaClass* currentLookup,
                              const std::string& name, const std::string& descriptor,
                              JObject* object, size_t offset = 0);
    void putFieldByNameImpl(const JavaClass* desireLookup,
                            const JavaClass* currentLookup, const std::string& name,
                            const std::string& descriptor, JObject* object,
                            JType* value, size_t offset = 0);

private:
    ObjectContainer objectContainer;
    ArrayContainer arrayContainer;
};
#endif  // JJVM_JAVAHEAP_H
