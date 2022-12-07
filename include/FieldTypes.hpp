#pragma once

#include <vector>
#include <memory>

namespace vm
{

/// @brief 
enum class AttributeTag {
	UnknownAttribute,
	ConstantValue,
	Code,
	Deprecated,
	Exceptions,
	InnerClasses,
	SourceFile,
	Synthetic,
	LineNumberTable,
	LocalVariableTable
};

struct Exception {
	uint16_t      start_pc;
	uint16_t      end_pc;
	uint16_t      handler_pc;
	uint16_t      catch_type;
};

class AttributeBase {
	AttributeTag                    m_tag;

public:
    AttributeBase(AttributeTag tag) : m_tag(tag) {}
	virtual ~AttributeBase() = default;
    AttributeTag getTag() const { return m_tag; }
};

struct ConstantValue_attribute : public AttributeBase {
    ConstantValue_attribute() : AttributeBase(AttributeTag::ConstantValue) {}
	uint16_t      constantvalue_index;
};

struct Code_attribute : public AttributeBase {
    Code_attribute() : AttributeBase(AttributeTag::Code) {}
	uint16_t                      max_stack;
	uint16_t                      max_locals;
	std::vector<uint8_t>          code;
	std::vector<std::shared_ptr<AttributeBase>> attributes;
    std::vector<Exception>  exceptions;
    // TODO exception table
};

struct Exceptions_attribute : public AttributeBase {
    Exceptions_attribute() : AttributeBase(AttributeTag::Exceptions) {}
	std::vector<uint16_t>             exception_index_table;
};


struct InnerClass {
	uint16_t      inner_class_info_index;
	uint16_t      outer_class_info_index;
	uint16_t      inner_name_index;
	uint16_t      inner_class_access_flags;
};

struct InnerClasses_attribute : public AttributeBase {
    InnerClasses_attribute() : AttributeBase(AttributeTag::InnerClasses) {}
    std::vector<InnerClass> classes; // TODO
};

struct SourceFile_attribute : public AttributeBase {
    SourceFile_attribute() : AttributeBase(AttributeTag::SourceFile) {}
	uint16_t                      sourcefile_index;
};

struct LineNumber {
	uint16_t      start_pc;
	uint16_t      line_number;
};

struct LineNumberTable_attribute : public AttributeBase {
    LineNumberTable_attribute() : AttributeBase(AttributeTag::LineNumberTable) {}
    std::vector<LineNumber> line_number_table;
};

struct LocalVariable {
	uint16_t      start_pc;
	uint16_t      length;
	uint16_t      name_index;
	uint16_t      descriptor_index;
	uint16_t      index;
};

struct LocalVariableTable_attribute : public AttributeBase {
    LocalVariableTable_attribute() : AttributeBase(AttributeTag::LocalVariableTable) {}
    std::vector<LocalVariable> local_variable_table;
};



struct Field final {
    /// @brief 
    enum class FieldType {
	    BYTE       = 'B',
	    CHAR       = 'C',
	    DOUBLE     = 'D',
	    FLOAT      = 'F',
	    INT        = 'I',
	    LONG       = 'J',
	    REFERENCE  = 'L',
	    SHORT      = 'S',
	    VOID       = 'V',
	    BOOLEAN    = 'Z',
	    ARRAY      = '[',
	    TERMINAL   = ';',
	    SEPARATOR  = '/',
    };

	uint16_t                      access_flags;
	uint16_t                      name_index;
	uint16_t                      descriptor_index;
	std::vector<std::shared_ptr<AttributeBase>>        attributes;
}; // struct Field


struct Method {
	uint16_t                      access_flags;
	uint16_t                      name_index;
	uint16_t                      descriptor_index;
	std::vector<std::shared_ptr<AttributeBase>> attributes;
};



} // namespace vm