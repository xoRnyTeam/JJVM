#ifndef _JJVM_GC_H
#define _JJVM_GC_H

#include <memory>
#include <unordered_set>

#include "Option.hpp"

struct JType;
class JavaFrame;

enum class GCPolicy { GC_MARK_AND_SWEEP };

class GC {
public:
  GC() : overMemoryThreshold(false) {}

  bool shallGC() const { return overMemoryThreshold; }
  void notifyGC() { overMemoryThreshold = true; }
  void stopTheWorld();
  void gc(JavaFrame *frames, GCPolicy policy = GCPolicy::GC_MARK_AND_SWEEP);

private:
  inline void pushObjectBitmap(size_t offset) { objectBitmap.insert(offset); }

  void markAndSweep();
  void mark(JType *ref);
  void sweep();
  std::unordered_set<size_t> objectBitmap;

  std::unordered_set<size_t> arrayBitmap;
  bool overMemoryThreshold = false;

private:
  JavaFrame *frames;
};

#endif
