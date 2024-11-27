#include <gtest/gtest.h>
#include "archive.hpp"

std::string testCompressDecompress(const std::string& str)
{
    ZlibArchive arh(std::vector<byte>(str.begin(), str.end()));
    arh.Compress();
    arh.Decompress();
    auto data = std::move(arh).ExtractData();

    return std::string(data.begin(), data.end());
}
void testException()
{
    std::string str = "test";
    ZlibArchive arh(std::vector<byte>(str.begin(), str.end()));
    arh.Decompress();
}
TEST(TEST, CompressDecompress)
{
    EXPECT_EQ(testCompressDecompress("testing archiving"), "testing archiving");
    EXPECT_NE(testCompressDecompress("testing archiving 1"), "testing archiving 2");
}

TEST(TEST, Exception)
{
    EXPECT_THROW(testException(), ArchiveDecompressException);
    EXPECT_NO_THROW(testCompressDecompress("testing archiving"));
}