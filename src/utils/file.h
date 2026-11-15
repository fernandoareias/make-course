#pragma once

#include <expected>
#include <fstream>
#include <iterator>
#include <vector>

#include "ifile.h"

namespace utils {
    class File : public IFile {
        public:
            std::expected<std::vector<char>, std::string> read(const std::string &file_name) override {
                std::ifstream stream(file_name, std::ios::binary);
                if(!stream.is_open())
                    return std::unexpected("Cannot open file: " + file_name);
                return std::vector<char>(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
            }

            std::expected<void, std::string> write(const std::string &file_name, const std::vector<char> &data) override {
                std::ofstream stream(file_name, std::ios::binary);
                if(!stream.is_open())
                    return std::unexpected("Cannot open file: " + file_name);
                stream.write(data.data(), data.size());
                if(!stream)
                    return std::unexpected("Failed to write file: " + file_name);
                return {};
            }
    };
}
