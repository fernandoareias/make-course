#include "compression.h"

#include <zlib.h>

#include <cstdint>
#include <cstring>

namespace compression {

    std::expected<std::vector<char>, std::string> Compression::compress(const std::vector<char> &data, int level) {
        uLongf dest_len = compressBound(static_cast<uLong>(data.size()));
        std::vector<char> dest(sizeof(uint64_t) + dest_len);

        uint64_t original_size = data.size();
        std::memcpy(dest.data(), &original_size, sizeof(original_size));

        int result = compress2(
            reinterpret_cast<Bytef *>(dest.data() + sizeof(original_size)),
            &dest_len,
            reinterpret_cast<const Bytef *>(data.data()),
            static_cast<uLong>(data.size()),
            level
        );

        if(result != Z_OK)
            return std::unexpected("zlib compress2 failed with code: " + std::to_string(result));

        dest.resize(sizeof(original_size) + dest_len);
        return dest;
    }

    std::expected<std::vector<char>, std::string> Compression::decompress(const std::vector<char> &data) {
        if(data.size() < sizeof(uint64_t))
            return std::unexpected("Invalid compressed data: missing size header");

        uint64_t original_size = 0;
        std::memcpy(&original_size, data.data(), sizeof(original_size));

        std::vector<char> dest(original_size);
        uLongf dest_len = static_cast<uLongf>(original_size);

        int result = uncompress(
            reinterpret_cast<Bytef *>(dest.data()),
            &dest_len,
            reinterpret_cast<const Bytef *>(data.data() + sizeof(original_size)),
            static_cast<uLong>(data.size() - sizeof(original_size))
        );

        if(result != Z_OK)
            return std::unexpected("zlib uncompress failed with code: " + std::to_string(result));

        dest.resize(dest_len);
        return dest;
    }
}
