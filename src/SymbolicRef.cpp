 
#include "SymbolicRef.hpp"

SymbolicRef parseFieldSymbolicReference(const JavaClass *jc, u2 index) {
    auto *fr = (CONSTANT_Fieldref *)jc->getConstPoolItem(index);
    auto *nat =
        (CONSTANT_NameAndType *)jc->getConstPoolItem(fr->nameAndTypeIndex);
    auto *cl = (CONSTANT_Class *)jc->getConstPoolItem(fr->classIndex);

    auto fieldName = jc->getString(nat->nameIndex);
    auto fieldDesc = jc->getString(nat->descriptorIndex);
    auto fieldClass =
        runtime.cs->loadClassIfAbsent(jc->getString(cl->nameIndex));
    runtime.cs->linkClassIfAbsent(jc->getString(cl->nameIndex));

    return SymbolicRef{fieldClass, fieldName, fieldDesc};
}

SymbolicRef parseInterfaceMethodSymbolicReference(const JavaClass *jc,
                                                  u2 index) {
    auto *imr = (CONSTANT_InterfaceMethodref *)jc->getConstPoolItem(index);
    auto *nat =
        (CONSTANT_NameAndType *)jc->getConstPoolItem(imr->nameAndTypeIndex);
    auto *cl = (CONSTANT_Class *)jc->getConstPoolItem(imr->classIndex);

    auto interfaceMethodName = jc->getString(nat->nameIndex);
    auto interfaceMethodDesc = jc->getString(nat->descriptorIndex);
    auto interfaceMethodClass =
        runtime.cs->loadClassIfAbsent(jc->getString(cl->nameIndex));
    runtime.cs->linkClassIfAbsent(jc->getString(cl->nameIndex));

    return SymbolicRef{interfaceMethodClass, interfaceMethodName,
                       interfaceMethodDesc};
}

SymbolicRef parseMethodSymbolicReference(const JavaClass *jc, u2 index) {
    auto *mr = (CONSTANT_Methodref *)jc->getConstPoolItem(index);
    auto *nat =
        (CONSTANT_NameAndType *)jc->getConstPoolItem(mr->nameAndTypeIndex);
    auto *cl = (CONSTANT_Class *)jc->getConstPoolItem(mr->classIndex);

    auto methodName = jc->getString(nat->nameIndex);
    auto methodDesc = jc->getString(nat->descriptorIndex);
    auto methodClass =
        runtime.cs->loadClassIfAbsent(jc->getString(cl->nameIndex));
    runtime.cs->linkClassIfAbsent(jc->getString(cl->nameIndex));

    return SymbolicRef{methodClass, methodName, methodDesc};
}

SymbolicRef parseClassSymbolicReference(const JavaClass *jc, u2 index) {
    auto *cl = (CONSTANT_Class *)jc->getConstPoolItem(index);
    auto className = jc->getString(cl->nameIndex);
    if (className[0] == '[') {
        className = peelArrayComponentTypeFrom(className);
    }

    auto c = runtime.cs->loadClassIfAbsent(className);
    runtime.cs->linkClassIfAbsent(className);
    return SymbolicRef{c};
}
