#include "ClassFile.hpp"
#include "instructions.hpp"


#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

// Magic first 4 bytes at class file
#define MAGIC           0xCAFEBABE


namespace vm
{

template< typename T, typename F >
T read_reverse(std::basic_istream<F> &stream) {
    std::array<char, sizeof(T)> buff = {};
    stream.read(buff.data(), sizeof(T));
    std::reverse(buff.begin(), buff.end());
    T result = *reinterpret_cast<T*>(buff.data());
    return result;
}

template< typename F >
std::vector<std::shared_ptr<ConstantPoolBase>> read_constant_pools(std::basic_istream<F> &stream, uint16_t count) {

	if (count == 0) {
		return {};
	}

    std::vector<std::shared_ptr<ConstantPoolBase>> res(count, nullptr);

	for (uint16_t i = 1; i < count; i++) {
        auto tag = read_reverse<ConstantTag>(stream);
		switch (tag) {
		case ConstantTag::CONSTANT_Utf8: {
            auto&& info = std::make_shared<CONSTANT_Utf8_info>();
            info->length = read_reverse<uint16_t>(stream);
			
			std::vector<char> tmp(info->length + 1, 0);
            stream.read(tmp.data(), info->length);

			info->bytes = tmp.data();
            res[i] = info;
			break;
        }
		case ConstantTag::CONSTANT_Integer: {
            auto&& info = std::make_shared<CONSTANT_Integer_info>();
			info->bytes = read_reverse<uint32_t>(stream);
            res[i] = info;
			break;
        }
		case ConstantTag::CONSTANT_Float: {
            auto&& info = std::make_shared<CONSTANT_Float_info>();
			info->bytes = read_reverse<uint32_t>(stream);
            res[i] = info;
			break;
        }
		case ConstantTag::CONSTANT_Long: {
            auto&& info = std::make_shared<CONSTANT_Long_info>();
            info->high_bytes = read_reverse<uint32_t>(stream);
            info->low_bytes = read_reverse<uint32_t>(stream);
            res[i] = info;
			i++;
			break;
        }
		case ConstantTag::CONSTANT_Double: {
            auto&& info = std::make_shared<CONSTANT_Double_info>();
            info->high_bytes = read_reverse<uint32_t>(stream);
            info->low_bytes = read_reverse<uint32_t>(stream);
            res[i] = info;
			i++;
			break;
        }
		case ConstantTag::CONSTANT_Class: {
            auto&& info = std::make_shared<CONSTANT_Class_info>();
            info->name_index = read_reverse<uint16_t>(stream);
            res[i] = info;
			break;
        }
		case ConstantTag::CONSTANT_String: {
            auto&& info = std::make_shared<CONSTANT_String_info>();
			info->string_index = read_reverse<uint16_t>(stream);
            res[i] = info;
			break;
        }
		case ConstantTag::CONSTANT_Fieldref: {
            auto&& info = std::make_shared<CONSTANT_Fieldref_info>();
            info->class_index = read_reverse<uint16_t>(stream);
            info->name_and_type_index = read_reverse<uint16_t>(stream);
            res[i] = info;
			break;
        }
		case ConstantTag::CONSTANT_Methodref: {
            auto&& info = std::make_shared<CONSTANT_Methodref_info>();
            info->class_index = read_reverse<uint16_t>(stream);
            info->name_and_type_index = read_reverse<uint16_t>(stream);
            res[i] = info;
			break;
        }
		case ConstantTag::CONSTANT_InterfaceMethodref: {
            auto&& info = std::make_shared<CONSTANT_InterfaceMethodref_info>();
            info->class_index = read_reverse<uint16_t>(stream);
            info->name_and_type_index = read_reverse<uint16_t>(stream);
            res[i] = info;
			break;
        }
		case ConstantTag::CONSTANT_NameAndType: {
            auto&& info = std::make_shared<CONSTANT_NameAndType_info>();
            info->name_index = read_reverse<uint16_t>(stream);
            info->descriptor_index = read_reverse<uint16_t>(stream);
            res[i] = info;
			break;
        }
		case ConstantTag::CONSTANT_MethodHandle: {
            auto&& info = std::make_shared<CONSTANT_MethodHandle_info>();
            info->reference_kind = read_reverse<ReferenceKind>(stream);
            info->reference_index = read_reverse<uint16_t>(stream);
            res[i] = info;
			break;
        }
		case ConstantTag::CONSTANT_MethodType: {
            auto&& info = std::make_shared<CONSTANT_MethodType_info>();
            info->descriptor_index = read_reverse<uint16_t>(stream);
            res[i] = info;
			break;
        }
		case ConstantTag::CONSTANT_InvokeDynamic: {
            auto&& info = std::make_shared<CONSTANT_InvokeDynamic_info>();
            info->bootstrap_method_attr_index = read_reverse<uint16_t>(stream);
            info->name_and_type_index = read_reverse<uint16_t>(stream);
            res[i] = info;
			break;
        }
		default:
			throw std::runtime_error("Uncnovn constant pool tag!");
		}
	}

	// TODO check kind of tag and descriptors
	for (uint8_t i = 1; i < count; i++) {
		switch (res[i]->getTag()) {
		case ConstantTag::CONSTANT_Utf8:
		case ConstantTag::CONSTANT_Integer:
		case ConstantTag::CONSTANT_Float:
			break;
		case ConstantTag::CONSTANT_Long:
		case ConstantTag::CONSTANT_Double:
			i++;
			break;
		case ConstantTag::CONSTANT_Class:
			break;
		case ConstantTag::CONSTANT_String: {
			auto info = std::static_pointer_cast<CONSTANT_String_info>(res[i]);
			auto utf8_infp = std::static_pointer_cast<CONSTANT_Utf8_info>(res[info->string_index]);
			info->string = utf8_infp->bytes;
			break;
		}
		case ConstantTag::CONSTANT_Fieldref:
		case ConstantTag::CONSTANT_Methodref:
		case ConstantTag::CONSTANT_InterfaceMethodref:
		case ConstantTag::CONSTANT_NameAndType:
		case ConstantTag::CONSTANT_MethodHandle:
		case ConstantTag::CONSTANT_MethodType:
		case ConstantTag::CONSTANT_InvokeDynamic:
			break;
		default:
			break;
		}
	}

    return res;
}


template< typename F >
std::vector<uint16_t> read_interfaces(std::basic_istream<F> &stream, uint16_t count) {
	std::vector<uint16_t> res(count, 0);

	for(uint16_t i = 0; i < count; ++i) {
		res[i] = read_reverse<uint16_t>(stream);
	}

	return res;
}

static AttributeTag getattributetag(const std::string &tagstr) {
	static struct {
		AttributeTag t;
		std::string s;
	} tags[] = {
		{AttributeTag::ConstantValue,      "ConstantValue"},
		{AttributeTag::Code,               "Code"},
		{AttributeTag::Deprecated,         "Deprecated"},
		{AttributeTag::Exceptions,         "Exceptions"},
		{AttributeTag::InnerClasses,       "InnerClasses"},
		{AttributeTag::SourceFile,         "SourceFile"},
		{AttributeTag::Synthetic,          "Synthetic"},
		{AttributeTag::LineNumberTable,    "LineNumberTable"},
		{AttributeTag::LocalVariableTable, "LocalVariableTable"},
		{AttributeTag::UnknownAttribute,   {}},
	};

	for (auto&& t : tags)
		if (tagstr == t.s)
			return t.t;
	return AttributeTag::UnknownAttribute;
}

template< typename F >
std::vector<uint8_t> read_code(std::basic_istream<F> &stream, uint32_t count) {
	std::vector<uint8_t> res(count);

	int32_t j, npairs, off, high, low;
	int64_t base, i;

	for (i = 0; i < count; i++) {
		res[i] = read_reverse<uint8_t>(stream);

		if (res[i] >= Instruction::CODE_LAST)
			throw std::logic_error("Uncnown opcode: " + std::to_string(res[i]));

		switch (res[i]) {
		case Instruction::WIDE:
			res[++i] = read_reverse<uint8_t>(stream);
			switch (res[i]) {
			case Instruction::IINC:
				res[++i] = read_reverse<uint8_t>(stream);
				res[++i] = read_reverse<uint8_t>(stream);
				/* FALLTHROUGH */
			case Instruction::ILOAD:
			case Instruction::FLOAD:
			case Instruction::ALOAD:
			case Instruction::LLOAD:
			case Instruction::DLOAD:
			case Instruction::ISTORE:
			case Instruction::FSTORE:
			case Instruction::ASTORE:
			case Instruction::LSTORE:
			case Instruction::DSTORE:
			case Instruction::RET:
				res[++i] = read_reverse<uint8_t>(stream);
				res[++i] = read_reverse<uint8_t>(stream);
				break;
			default:
				throw std::logic_error("Uncnown opcode!");
				break;
			}
			break;
		case Instruction::LOOKUPSWITCH:
			while ((3 - (i % 4)) > 0) {
				res[++i] = read_reverse<uint8_t>(stream);
			}
			for (j = 0; j < 8; j++) {
				res[++i] = read_reverse<uint8_t>(stream);
			}
			npairs = (res[i-3] << 24) | (res[i-2] << 16) | (res[i-1] << 8) | res[i];
			if (npairs < 0) {
				throw std::logic_error("WTF!");
			}
			for (j = 8 * npairs; j > 0; j--) {
				res[++i] = read_reverse<uint8_t>(stream);
			}
			break;
		case Instruction::TABLESWITCH:
			base = i;
			while ((3 - (i % 4)) > 0) {
				res[++i] = read_reverse<uint8_t>(stream);
			}
			for (j = 0; j < 12; j++) {
				res[++i] = read_reverse<uint8_t>(stream);
			}
			off = (res[i-11] << 24) | (res[i-10] << 16) | (res[i-9] << 8) | res[i-8];
			low = (res[i-7] << 24) | (res[i-6] << 16) | (res[i-5] << 8) | res[i-4];
			high = (res[i-3] << 24) | (res[i-2] << 16) | (res[i-1] << 8) | res[i];
			if (base + off < 0 || base + off >= count) {
				throw std::logic_error("WTF!");
			}
			if (low > high) {
				throw std::logic_error("WTF!");
			}
			for (j = low; j <= high; j++) {
				res[++i] = read_reverse<uint8_t>(stream);
				res[++i] = read_reverse<uint8_t>(stream);
				res[++i] = read_reverse<uint8_t>(stream);
				res[++i] = read_reverse<uint8_t>(stream);
				off = (res[i-3] << 24) | (res[i-2] << 16) | (res[i-1] << 8) | res[i];
				if (base + off < 0 || base + off >= count) {
					throw std::logic_error("WTF!");
				}
			}
			break;
		case Instruction::LDC:
			res[++i] = read_reverse<uint8_t>(stream);
			break;
		case Instruction::LDC_W:
			res[++i] = read_reverse<uint8_t>(stream);
			res[++i] = read_reverse<uint8_t>(stream);
			break;
		case Instruction::LDC2_W:
			res[++i] = read_reverse<uint8_t>(stream);
			res[++i] = read_reverse<uint8_t>(stream);
			break;
		case Instruction::GETSTATIC: 
		case Instruction::PUTSTATIC: 
		case Instruction::GETFIELD: 
		case Instruction::PUTFIELD:
			res[++i] = read_reverse<uint8_t>(stream);
			res[++i] = read_reverse<uint8_t>(stream);
			break;
		case Instruction::INVOKESTATIC:
			res[++i] = read_reverse<uint8_t>(stream);
			res[++i] = read_reverse<uint8_t>(stream);
			break;
		case Instruction::MULTIANEWARRAY:
			res[++i] = read_reverse<uint8_t>(stream);
			res[++i] = read_reverse<uint8_t>(stream);
			res[++i] = read_reverse<uint8_t>(stream);
			if (res[i] < 1) {
				throw std::logic_error("WTF!");
			}
			break;
		default:
			for (j = getnoperands(res[i]); j > 0; j--) {
				res[++i] = read_reverse<uint8_t>(stream);
			}
			break;
		}
	}

	return res;
}


template< typename F >
std::vector<Exception> read_exceptions(std::basic_istream<F> &stream, uint16_t count) {
	std::vector<Exception> res(count);

	for(uint16_t k = 0; k < count; ++k) {
		res[k].start_pc = read_reverse<uint16_t>(stream);
		res[k].end_pc = read_reverse<uint16_t>(stream);
		res[k].handler_pc = read_reverse<uint16_t>(stream);
		res[k].catch_type = read_reverse<uint16_t>(stream);
	}

	return res;
}


template< typename F >
std::vector<std::shared_ptr<AttributeBase>> read_attributes(std::basic_istream<F> &stream, uint16_t count, const std::vector<std::shared_ptr<ConstantPoolBase>> &cp) {
	std::vector<std::shared_ptr<AttributeBase>> res(count);

	for (uint16_t i = 0; i < count; i++) {
		uint16_t index = read_reverse<uint16_t>(stream);
		uint32_t length = read_reverse<uint32_t>(stream);

		auto&& utf8_info = std::static_pointer_cast<CONSTANT_Utf8_info>(cp[index]);
		AttributeTag tag = getattributetag(utf8_info->bytes);
		switch (tag) {
		case AttributeTag::ConstantValue: {
			auto attr = std::make_shared<ConstantValue_attribute>();
			attr->constantvalue_index = read_reverse<uint16_t>(stream);
			res[i] = attr;
			break;
		}
		case AttributeTag::Code: {
			auto attr = std::make_shared<Code_attribute>();
			attr->max_stack = read_reverse<uint16_t>(stream);
			attr->max_locals = read_reverse<uint16_t>(stream);
			
			uint32_t code_size = read_reverse<uint32_t>(stream);
			attr->code = read_code(stream, code_size);

			uint16_t exception_size = read_reverse<uint16_t>(stream);
			attr->exceptions = read_exceptions(stream, exception_size);

			uint16_t attr_count = read_reverse<uint16_t>(stream);
			attr->attributes = read_attributes(stream, attr_count, cp);
			
			res[i] = attr;
			break;
		}
		case AttributeTag::Deprecated:
			break;
		case AttributeTag::Exceptions: {
			auto attr = std::make_shared<Exceptions_attribute>();
			uint16_t number_of_exceptions = read_reverse<uint16_t>(stream);
			attr->exception_index_table.resize(number_of_exceptions);	
			for(uint16_t k = 0; k < number_of_exceptions; ++k) {
				attr->exception_index_table[k] = read_reverse<uint16_t>(stream);
			}
			res[i] = attr;
			break;
		}
		case AttributeTag::InnerClasses: {
			auto attr = std::make_shared<InnerClasses_attribute>();
			
			uint16_t number = read_reverse<uint16_t>(stream);
			attr->classes.resize(number);

			for(uint16_t k = 0; k < number; ++k) {
				attr->classes[k].inner_class_info_index = read_reverse<uint16_t>(stream);
				attr->classes[k].outer_class_info_index = read_reverse<uint16_t>(stream);
				attr->classes[k].inner_name_index = read_reverse<uint16_t>(stream);
				attr->classes[k].inner_class_access_flags = read_reverse<uint16_t>(stream);
			}

			res[i] = attr;
			break;
		}
		case AttributeTag::SourceFile: {
			auto attr = std::make_shared<SourceFile_attribute>();
			attr->sourcefile_index = read_reverse<uint16_t>(stream);
			res[i] = attr;
			break;
		}
		case AttributeTag::Synthetic:
			break;
		case AttributeTag::LineNumberTable: {
			auto attr = std::make_shared<LineNumberTable_attribute>();

			uint16_t number = read_reverse<uint16_t>(stream);
			attr->line_number_table.resize(number);

			for(uint16_t k = 0; k < number; ++k) {
				attr->line_number_table[k].start_pc = read_reverse<uint16_t>(stream);
				attr->line_number_table[k].line_number = read_reverse<uint16_t>(stream);
			}
			res[i] = attr;
			break;
		}
		case AttributeTag::LocalVariableTable: {
			auto attr = std::make_shared<LocalVariableTable_attribute>();

			uint16_t number = read_reverse<uint16_t>(stream);
			attr->local_variable_table.resize(number);

			for(uint16_t k = 0; k < number; ++k) {
				attr->local_variable_table[k].start_pc = read_reverse<uint16_t>(stream);
				attr->local_variable_table[k].length = read_reverse<uint16_t>(stream);
				attr->local_variable_table[k].name_index = read_reverse<uint16_t>(stream);
				attr->local_variable_table[k].descriptor_index = read_reverse<uint16_t>(stream);
				attr->local_variable_table[k].index = read_reverse<uint16_t>(stream);
			}
			res[i] = attr;
			break;
		}
		case AttributeTag::UnknownAttribute:
			stream.seekg(length, std::ios::cur);
			//while (length-- > 0)
			//	readb(stream, &b, 1);
			break;
		}
	}

	return res;
}

template< typename F >
std::vector<Field> read_fields(std::basic_istream<F> &stream, uint16_t count, const std::vector<std::shared_ptr<ConstantPoolBase>> &cp) {
	std::vector<Field> res(count);

	for(uint16_t i = 0; i < count; ++i) {
		res[i].access_flags = read_reverse<uint16_t>(stream);
		res[i].name_index = read_reverse<uint16_t>(stream);
		res[i].descriptor_index = read_reverse<uint16_t>(stream);

		uint16_t attr_count = read_reverse<uint16_t>(stream);
		res[i].attributes = read_attributes(stream, attr_count, cp);
	}

	return res;
}


template< typename F >
std::vector<Method> read_methods(std::basic_istream<F> &stream, uint16_t count, const std::vector<std::shared_ptr<ConstantPoolBase>> &cp) {
	std::vector<Method> res(count);

	for(uint16_t i = 0; i < count; ++i) {
		res[i].access_flags = read_reverse<uint16_t>(stream);
		res[i].name_index = read_reverse<uint16_t>(stream);
		res[i].descriptor_index = read_reverse<uint16_t>(stream);

		uint16_t attr_count = read_reverse<uint16_t>(stream);
		res[i].attributes = read_attributes(stream, attr_count, cp);
	}

	return res;
}


/* static */
ClassFile ClassFile::create(const std::string &file_name) {
    
    std::ifstream fb(file_name, std::ios::in | std::ios::binary);
    if(!fb.is_open()) {
        throw std::runtime_error("open file: " + file_name);
    }

    uint32_t magic = read_reverse<uint32_t>(fb);
    if(magic != MAGIC) {
        throw std::runtime_error("Error magic number!");
    }

	ClassFile res = {};

    res.minor_version = read_reverse<uint16_t>(fb);
    res.major_version = read_reverse<uint16_t>(fb);

    uint16_t ConstantPool_count = read_reverse<uint16_t>(fb);
    res.cp = read_constant_pools(fb, ConstantPool_count);

	res.access_flags = read_reverse<uint16_t>(fb);
	res.this_class = read_reverse<uint16_t>(fb);
	res.super_class = read_reverse<uint16_t>(fb);

	uint16_t interfaces_count = read_reverse<uint16_t>(fb);
	res.interfaces = read_interfaces(fb, interfaces_count);

	uint16_t fields_count = read_reverse<uint16_t>(fb);
	res.fields = read_fields(fb, fields_count, res.cp);

	uint16_t methods_count = read_reverse<uint16_t>(fb);
	res.methods = read_methods(fb, methods_count, res.cp);

	uint16_t attr_count = read_reverse<uint16_t>(fb);
	res.attributes = read_attributes(fb, attr_count, res.cp);

    return res;
}

} // namespace vm