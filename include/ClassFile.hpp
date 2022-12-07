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

    // FIXME mb conver to constructor    
    static ClassFile create(const std::string &file_name);

public:
    std::pair<Method, bool> getMethod(const std::string &name, const std::string &descriptor) const;
    std::pair<Field, bool> getField(const std::string &name, const std::string &descriptor) const;

    /// @brief check if super class is java.lang.Object
    /// @note super class is not supported yet
    bool isTopClass() const;

    // constant pool interface
    //=-----------------------
    std::string getUTF8(uint16_t id) const;
    std::string getClassName(uint16_t id) const;
    std::string getString(uint16_t id) const;

    int32_t getInteger(uint16_t id) const;
    float getFloat(uint16_t id) const;
    int64_t getLong(uint16_t id) const;
    double getDouble(uint16_t id) const;

    std::pair<std::string, std::string> getNameAndType(uint16_t id) const;

private:

}; // class ClassFile

} // namespace vm