#pragma once 

#include <string>
#include <vector>
#include <expected>

namespace utils {

    class IFile {
        public:
            virtual std::expected<std::vector<char>, std::string> read(const std::string &file_name) = 0;
            virtual std::expected<void, std::string> write(const std::string &file_name, const std::vector<char> &data) = 0;
            
    };
}