#pragma once

#include <string>
#include <memory>
#include <vector>

#include <ConstantPoolTypes.hpp>
#include <FieldTypes.hpp>

namespace vm
{

/// @brief 
struct ClassFile final {
    uint16_t minor_version = {};
    uint16_t major_version = {};

    std::vector<std::shared_ptr<ConstantPoolBase>> cp;

    uint16_t access_flags = {};
    uint16_t this_class = {};
    uint16_t super_class = {};

    std::vector<uint16_t> interfaces;
    std::vector<Field> fields;
    std::vector<Method> methods;

    std::vector<std::shared_ptr<AttributeBase>> attributes;
    
    static ClassFile create(const std::string &file_name);
}; // class ClassFile

} // namespace vm