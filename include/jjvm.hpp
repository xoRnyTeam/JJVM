#pragma once

#include <string>
#include <vector>

namespace vm
{

class jjvm final {

public:
    /// @brief 
    /// @param class_name 
    /// @param class_path 
    jjvm(const std::string &class_name, std::vector< const std::string > &class_path);



}; // class jjvm

} // namespace vm