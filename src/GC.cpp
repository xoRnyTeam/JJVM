#include "GC.hpp"

#include "ClassSpace.hpp"
#include "JJVM.hpp"
#include "JavaClass.hpp"
#include "JavaHeap.hpp"
#include "JavaType.hpp"

using namespace std;

void GC::stopTheWorld() { printf("STOP WORLD!\n"); }

void GC::gc(JavaFrame *frames, GCPolicy policy) {
  printf("GC STARTED!!!!!!!!!!!!\n");

  this->frames = frames;
//   if (!overMemoryThreshold) {
//     return;
//   }

  switch (policy) {
  case GCPolicy::GC_MARK_AND_SWEEP:
    markAndSweep();
    break;
  default:
    markAndSweep();
    break;
  }
  objectBitmap.clear();
  arrayBitmap.clear();
  overMemoryThreshold = false;
}

void GC::mark(JType *ref) {
  if (ref == nullptr) {
    // Prevent from throwing bad_typeid since local variable table slot
    // could be empty
    return;
  }
  if (typeid(*ref) == typeid(JObject)) {
    {
      // Mark() is very quickly and busy, so we use lightweight spin lock
      // instead of stl mutex
      objectBitmap.insert(dynamic_cast<JObject *>(ref)->offset);
    }
    auto fields = runtime.heap->getFields(dynamic_cast<JObject *>(ref));
    for (size_t i = 0; i < fields.size(); i++) {
      mark(fields[i]);
    }
  } else if (typeid(*ref) == typeid(JArray)) {
    { arrayBitmap.insert(dynamic_cast<JArray *>(ref)->offset); }
    auto items = runtime.heap->getElements(dynamic_cast<JArray *>(ref));

    for (size_t i = 0; i < items.first; i++) {
      mark(items.second[i]);
    }
  } else {
    SHOULD_NOT_REACH_HERE
  }
}

void GC::sweep() {
  // object
  for (auto pos = runtime.heap->objectContainer.data.begin();
       pos != runtime.heap->objectContainer.data.end();) {
    // If we can not find active object in object bitmap then clear it
    // Notice that here we don't need to lock objectBitmap since it must
    // be marked before sweeping
    if (objectBitmap.find(pos->first) == objectBitmap.cend()) {
      runtime.heap->objectContainer.data.erase(pos++);
    } else {
      ++pos;
    }
  }

  // array
  for (auto pos = runtime.heap->arrayContainer.data.begin();
       pos != runtime.heap->arrayContainer.data.end();) {
    // DITTO
    if (arrayBitmap.find(pos->first) == arrayBitmap.cend()) {
      for (size_t i = 0; i < pos->second.first; i++) {
        delete pos->second.second[i];
      }
      delete[] pos->second.second;
      runtime.heap->arrayContainer.data.erase(pos++);
    } else {
      ++pos;
    }
  }
}

void GC::markAndSweep() {
  auto *temp = frames->top();
  while (temp != nullptr) {
    // stack mark
    for (int i = 0; i < temp->maxStack; i++) {
      this->mark(temp->stackSlots[i]);
    }

    // local mark
    for (int i = 0; i < temp->maxLocal; i++) {
      this->mark(temp->localSlots[i]);
    }

    temp = temp->next;
  }

  // static fields
  for (auto c : runtime.cs->classTable) {
    for_each(c.second->staticVars.cbegin(), c.second->staticVars.cend(),
             [this](const pair<size_t, JType *> &offset) {
               if (typeid(*offset.second) == typeid(JObject)) {
                 {
                   objectBitmap.insert(offset.first);
                 }
               } else if (typeid(*offset.second) == typeid(JArray)) {
                 { arrayBitmap.insert(offset.first); }
               }
             });
  }

  sweep();
}
