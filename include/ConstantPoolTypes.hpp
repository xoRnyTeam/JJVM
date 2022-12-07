#pragma once

#include <cstdint>
#include <string>


namespace vm
{

/// @brief 
enum class ConstantTag : uint8_t {
	CONSTANT_Untagged           = 0,
	CONSTANT_Utf8               = 1,
	CONSTANT_Integer            = 3,
	CONSTANT_Float              = 4,
	CONSTANT_Long               = 5,
	CONSTANT_Double             = 6,
	CONSTANT_Class              = 7,
	CONSTANT_String             = 8,
	CONSTANT_Fieldref           = 9,
	CONSTANT_Methodref          = 10,
	CONSTANT_InterfaceMethodref = 11,
	CONSTANT_NameAndType        = 12,
	CONSTANT_MethodHandle       = 15,
	CONSTANT_MethodType         = 16,
	CONSTANT_InvokeDynamic      = 18,
	CONSTANT_Constant           = 20,       // used to tag integers, longs, doubles, floats and strings
	CONSTANT_U1                 = 21,       // used to tag integers, floats and strings
	CONSTANT_U2                 = 22        // used to tag longs and doubles
};

enum class ReferenceKind : uint8_t {
	none                = 0,
	getField            = 1,
	getStatic           = 2,
	putField            = 3,
	putStatic           = 4,
	invokeVirtual       = 5,
	invokeStatic        = 6,
	invokeSpecial       = 7,
	newInvokeSpecial    = 8,
	invokeInterface     = 9,
	last                = 10,
};


/// @brief represent a constant from constant pool
class ConstantPoolBase {
	ConstantTag m_tag;

public:
    ConstantPoolBase(ConstantTag tag) 
        : m_tag(tag) {}
	virtual ~ConstantPoolBase() = default;

    ConstantTag getTag() const { return m_tag; };
};


struct CONSTANT_Utf8_info : public ConstantPoolBase {
    CONSTANT_Utf8_info() : ConstantPoolBase(ConstantTag::CONSTANT_Utf8) {}
	uint16_t      length;
	std::string bytes;
};

struct CONSTANT_Integer_info : public ConstantPoolBase {
    CONSTANT_Integer_info() : ConstantPoolBase(ConstantTag::CONSTANT_Integer) {}
	uint32_t      bytes;
};

struct CONSTANT_Float_info : public ConstantPoolBase {
    CONSTANT_Float_info() : ConstantPoolBase(ConstantTag::CONSTANT_Float) {}
	uint32_t      bytes;
};

struct CONSTANT_Long_info : public ConstantPoolBase {
    CONSTANT_Long_info() : ConstantPoolBase(ConstantTag::CONSTANT_Long) {}
	uint32_t      high_bytes;
	uint32_t      low_bytes;
};

struct CONSTANT_Double_info : public ConstantPoolBase {
    CONSTANT_Double_info() : ConstantPoolBase(ConstantTag::CONSTANT_Double) {}
	uint32_t      high_bytes;
	uint32_t      low_bytes;
};

struct CONSTANT_Class_info : public ConstantPoolBase {
    CONSTANT_Class_info() : ConstantPoolBase(ConstantTag::CONSTANT_Class) {}
	uint16_t      name_index;
};

struct CONSTANT_String_info : public ConstantPoolBase {
    CONSTANT_String_info() : ConstantPoolBase(ConstantTag::CONSTANT_String) {}
	uint16_t      string_index;
	std::string   string;
};

struct CONSTANT_Fieldref_info : public ConstantPoolBase {
    CONSTANT_Fieldref_info() : ConstantPoolBase(ConstantTag::CONSTANT_Fieldref) {}
	uint16_t      class_index;
	uint16_t      name_and_type_index;
};

struct CONSTANT_Methodref_info : public ConstantPoolBase {
    CONSTANT_Methodref_info() : ConstantPoolBase(ConstantTag::CONSTANT_Methodref) {}
	uint16_t      class_index;
	uint16_t      name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info : public ConstantPoolBase {
    CONSTANT_InterfaceMethodref_info() : ConstantPoolBase(ConstantTag::CONSTANT_InterfaceMethodref) {}
	uint16_t      class_index;
	uint16_t      name_and_type_index;
};

struct CONSTANT_NameAndType_info : public ConstantPoolBase {
    CONSTANT_NameAndType_info() : ConstantPoolBase(ConstantTag::CONSTANT_NameAndType) {}
	uint16_t      name_index;
	uint16_t      descriptor_index;
};

struct CONSTANT_MethodHandle_info : public ConstantPoolBase {
    CONSTANT_MethodHandle_info() : ConstantPoolBase(ConstantTag::CONSTANT_MethodHandle) {}
	ReferenceKind reference_kind;
	uint16_t      reference_index;
};

struct CONSTANT_MethodType_info : public ConstantPoolBase {
    CONSTANT_MethodType_info() : ConstantPoolBase(ConstantTag::CONSTANT_MethodType) {}
	uint16_t      descriptor_index;
};

struct CONSTANT_InvokeDynamic_info : public ConstantPoolBase {
    CONSTANT_InvokeDynamic_info() : ConstantPoolBase(ConstantTag::CONSTANT_InvokeDynamic) {}
	uint16_t      bootstrap_method_attr_index;
	uint16_t      name_and_type_index;
};



} // namespace vm