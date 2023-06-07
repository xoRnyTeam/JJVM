// #include "ClassFile.hpp"
// #include <memory.hpp>
// 
// #include <stdexcept>
// #include <vector>
// 
// namespace vm
// {
// 
// 
// std::pair<Method, bool> ClassFile::getMethod(const std::string &name, const std::string &descriptor) const {
//     for(auto&& m : methods) {
//         if(name == getUTF8(m.name_index) && descriptor == getUTF8(m.descriptor_index)) {
//             return {m, true};
//         }
//     }
//     return {{}, false};
// }
// 
// std::pair<Field, bool> ClassFile::getField(const std::string &name, const std::string &descriptor) const {
//     for(auto&& m : fields) {
//         if(name == getUTF8(m.name_index) && descriptor == getUTF8(m.descriptor_index)) {
//             return {m , true};
//         }
//     }
//     return {{}, false};
// }
// 
// bool ClassFile::isTopClass() const {
//     return getClassName(super_class) == "java/lang/Object";
// }
// 
// 
// // constant pool interface
// //=-----------------------
// std::string ClassFile::getUTF8(uint16_t id) const {
//     if (cp[id]->getTag() != ConstantTag::CONSTANT_Utf8) {
//         throw std::logic_error("Call 'getUTF8', but teg is not CONSTANT_Utf8!");
//     }
//     auto&& utf = std::static_pointer_cast<CONSTANT_Utf8_info>(cp[id]);
//     return utf->bytes;
// }
// 
// std::string ClassFile::getClassName(uint16_t id) const {
//     if (cp[id]->getTag() != ConstantTag::CONSTANT_Class) {
//         throw std::logic_error("Call 'getClassName', but teg is not CONSTANT_Class!");
//     }
//     auto&& info = std::static_pointer_cast<CONSTANT_Class_info>(cp[id]);
//     return getUTF8(info->name_index);
// }
// 
// std::string ClassFile::getString(uint16_t id) const {
//     if (cp[id]->getTag() != ConstantTag::CONSTANT_String) {
//         throw std::logic_error("Call 'getString', but teg is not CONSTANT_String!");
//     }
//     auto&& info = std::static_pointer_cast<CONSTANT_String_info>(cp[id]);
//     return getUTF8(info->string_index);
// }
// 
// int32_t ClassFile::getInteger(uint16_t id) const {
//     if (cp[id]->getTag() != ConstantTag::CONSTANT_Integer) {
//         throw std::logic_error("Call 'getInteger', but teg is not CONSTANT_Integer!");
//     }
//     auto&& info = std::static_pointer_cast<CONSTANT_Integer_info>(cp[id]);
//     return *reinterpret_cast<int32_t*>(&info->bytes);
// }
// 
// float ClassFile::getFloat(uint16_t id) const {
//     if (cp[id]->getTag() != ConstantTag::CONSTANT_Float) {
//         throw std::logic_error("Call 'getFloat', but teg is not CONSTANT_Float!");
//     }
//     auto&& info = std::static_pointer_cast<CONSTANT_Float_info>(cp[id]);
//     return *reinterpret_cast<float*>(&info->bytes);
// }
// 
// int64_t ClassFile::getLong(uint16_t id) const {
//     if (cp[id]->getTag() != ConstantTag::CONSTANT_Long) {
//         throw std::logic_error("Call 'getLong', but teg is not CONSTANT_Long!");
//     }
//     auto&& info = std::static_pointer_cast<CONSTANT_Long_info>(cp[id]);
//     uint64_t tmp = static_cast<uint64_t>(info->high_bytes) << 32 | info->low_bytes;
//     return *reinterpret_cast<uint64_t*>(&tmp);
// }
// 
// double ClassFile::getDouble(uint16_t id) const {
//     if (cp[id]->getTag() != ConstantTag::CONSTANT_Double) {
//         throw std::logic_error("Call 'getDouble', but teg is not CONSTANT_Double!");
//     }
//     auto&& info = std::static_pointer_cast<CONSTANT_Double_info>(cp[id]);
//     uint64_t tmp = static_cast<uint64_t>(info->high_bytes) << 32 | info->low_bytes;
//     return *reinterpret_cast<double*>(&tmp);
// }
// 
// std::pair<std::string, std::string> ClassFile::getNameAndType(uint16_t id) const {
//     if (cp[id]->getTag() != ConstantTag::CONSTANT_NameAndType) {
//         throw std::logic_error("Call 'getNameAndType', but teg is not CONSTANT_NameAndType!");
//     }
//     auto&& info = std::static_pointer_cast<CONSTANT_NameAndType_info>(cp[id]);
//     std::string name = getUTF8(info->name_index);
//     std::string descriptor = getUTF8(info->descriptor_index);
//     return {name, descriptor};
// }
// 
// } // namespace vm