
#include "CallSite.hpp"

CallSite::CallSite()
    : jc(nullptr), code(nullptr), callable(false) {}

CallSite CallSite::makeCallSite(const JavaClass *jc, MethodInfo *m) {
  CallSite cs;
  cs.callable = m != nullptr ? true : false;
  cs.accessFlags = m->accessFlags;
  cs.jc = jc;

  FOR_EACH(i, m->attributeCount) {
    if (typeid(*m->attributes[i]) == typeid(ATTR_Code)) {
      cs.code = dynamic_cast<ATTR_Code *>(m->attributes[i])->code;
      cs.codeLength = ((ATTR_Code *)m->attributes[i])->codeLength;
      cs.maxLocal = dynamic_cast<ATTR_Code *>(m->attributes[i])->maxLocals;
      cs.maxStack = dynamic_cast<ATTR_Code *>(m->attributes[i])->maxStack;
      break;
    }
  }
  return cs;
}
