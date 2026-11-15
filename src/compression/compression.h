#pragma once

#include <expected>
#include <string>
#include <vector>

namespace compression {

    class Compression {
        public:
            std::expected<std::vector<char>, std::string> compress(const std::vector<char> &data, int level = -1);
            std::expected<std::vector<char>, std::string> decompress(const std::vector<char> &data);
    };
}
