#pragma once

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <vector>

#include "utils/file.h"


namespace fs = std::filesystem;
using utils::File;

class FileTest : public ::testing::Test {
    protected:
        void SetUp() override {
            m_test_dir = fs::temp_directory_path() / "file_test_dir";
            fs::create_directories(m_test_dir);
        }

        void TearDown() override {
            fs::remove_all(m_test_dir);
        }

        fs::path m_test_dir;
};

TEST_F(FileTest, WriteAndReadFileSuccessfully) {
    File file;
    auto test_path = m_test_dir / "example.txt";
    std::vector<char> data {'h', 'e', 'l', 'l', 'o'};

    auto write_result = file.write(test_path.string(), data);

    EXPECT_TRUE(write_result.has_value());
}

TEST_F(FileTest, ReadFileSuccessfully) {
    File file;
    auto test_path = m_test_dir / "example.txt";
    std::vector<char> data {'h', 'e', 'l', 'l', 'o'};
    ASSERT_TRUE(file.write(test_path.string(), data).has_value());

    auto read_result = file.read(test_path.string());

    ASSERT_TRUE(read_result.has_value());
    EXPECT_EQ(*read_result, data);
}

TEST_F(FileTest, ReadNonExistentFileFails) {
    File file;
    auto test_path = m_test_dir / "does_not_exist.txt";

    auto read_result = file.read(test_path.string());

    EXPECT_FALSE(read_result.has_value());
}