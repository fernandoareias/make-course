#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "compression/compression.h"

using compression::Compression;

TEST(CompressionTest, CompressProducesSmallerOutputForRepetitiveData) {
    Compression compression;
    std::string text(1000, 'a');
    std::vector<char> data(text.begin(), text.end());

    auto result = compression.compress(data);

    ASSERT_TRUE(result.has_value());
    EXPECT_LT(result->size(), data.size());
}

TEST(CompressionTest, DecompressRestoresOriginalData) {
    Compression compression;
    std::string text = "Hello, world! Hello, world! Hello, world!";
    std::vector<char> data(text.begin(), text.end());

    auto compressed = compression.compress(data);
    ASSERT_TRUE(compressed.has_value());

    auto decompressed = compression.decompress(*compressed);

    ASSERT_TRUE(decompressed.has_value());
    EXPECT_EQ(*decompressed, data);
}

TEST(CompressionTest, RoundTripWithEmptyData) {
    Compression compression;
    std::vector<char> data;

    auto compressed = compression.compress(data);
    ASSERT_TRUE(compressed.has_value());

    auto decompressed = compression.decompress(*compressed);

    ASSERT_TRUE(decompressed.has_value());
    EXPECT_EQ(*decompressed, data);
}

TEST(CompressionTest, DecompressFailsOnTruncatedHeader) {
    Compression compression;
    std::vector<char> truncated {'a', 'b', 'c'};

    auto result = compression.decompress(truncated);

    EXPECT_FALSE(result.has_value());
}

TEST(CompressionTest, DecompressFailsOnCorruptedData) {
    Compression compression;
    std::string text = "Hello, world! Hello, world! Hello, world!";
    std::vector<char> data(text.begin(), text.end());

    auto compressed = compression.compress(data);
    ASSERT_TRUE(compressed.has_value());
    for(size_t i = sizeof(uint64_t); i < compressed->size(); ++i)
        (*compressed)[i] = static_cast<char>(~(*compressed)[i]);

    auto result = compression.decompress(*compressed);

    EXPECT_FALSE(result.has_value());
}
