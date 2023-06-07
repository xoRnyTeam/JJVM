 
#ifndef JJVM_OPTION_H
#define JJVM_OPTION_H

//--------------------------------------------------------------------------------
// denote the default threshold value of garbage collector. GC was started when
// the memory allocation was beyond this value.
//--------------------------------------------------------------------------------
#define JJVM_GC_THRESHOLD_VALUE (1024 * 1024 * 1)

//--------------------------------------------------------------------------------
// show new spawning thread name
//--------------------------------------------------------------------------------
#define JJVM_DEBUG_SHOW_THREAD_NAME

//--------------------------------------------------------------------------------
// show byte size of internal structures
//--------------------------------------------------------------------------------
#undef JJVM_DEBUG_SHOW_SIZEOF_ALL_TYPE

//--------------------------------------------------------------------------------
// how executing bytecode and current class of method, method name and method
// descriptor
//--------------------------------------------------------------------------------
#undef JJVM_DEBUG_SHOW_BYTECODE

//--------------------------------------------------------------------------------
// output *.class parsing result, which contains constant pool table, fields,
// methods, class access flag, interfaces, etc
//--------------------------------------------------------------------------------
#undef JJVM_DEBUG_CLASS_FILE
#ifdef JJVM_DEBUG_CLASS_FILE
#define JJVM_DEBUG_SHOW_VERSION
#define JJVM_DEBUG_SHOW_CONSTANT_POOL_TABLE
#define JJVM_DEBUG_SHOW_INTERFACE
#define JJVM_DEBUG_SHOW_CLASS_FIELD
#define JJVM_DEBUG_SHOW_CLASS_ACCESS_FLAGS
#define JJVM_DEBUG_SHOW_CLASS_METHOD
#define JJVM_DEBUG_SHOW_CLASS_ATTRIBUTE
#endif

//--------------------------------------------------------------------------------
// to mark a gc safe point
//--------------------------------------------------------------------------------
#define GC_SAFE_POINT

#endif  // !JJVM_OPTION_H
