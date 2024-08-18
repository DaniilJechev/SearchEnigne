#include "gtest/gtest.h"
#include "ConverterJSON.h"

#include <vector>
#include <filesystem>

namespace fs = std::filesystem;
fs::path testJsonDir = "testJsonFiles/";
fs::path testResourcesDir = "testResources/";

TEST(ConverterJSON, getResponsesLimit) {
    ASSERT_EQ(ConverterJSON::getResponsesLimit(testJsonDir), 3);
}

TEST(ConverterJSON, getRequests) {
    auto requests = ConverterJSON::getRequests(testJsonDir);
    ASSERT_EQ(requests.size(), 4);
    EXPECT_STREQ(requests[0].c_str(), "Hello world");
    EXPECT_STREQ(requests[1].c_str(), "How to cook");
    EXPECT_STREQ(requests[2].c_str(), "text.txt in subdir2");
    EXPECT_STREQ(requests[3].c_str(), "inaccessible dir");
}

TEST(ConverterJSON, getTextDocuments) {
    auto texts = ConverterJSON::getTextDocuments(testJsonDir, testResourcesDir);
    ASSERT_EQ(texts.size(), 4); // "nonExistFile.txt" and "textInSubdir.txt" must not include in the arr
    EXPECT_STREQ(texts[0].c_str(), ""); //empty.txt
    EXPECT_STREQ(texts[1].c_str(), "Hello world!"); //simpleText.txt
    EXPECT_STREQ(texts[2].c_str(), "firstLine secondLine"); //manyLines.txt
    EXPECT_STREQ(texts[3].c_str(), "text.txt in subdir2");
}
