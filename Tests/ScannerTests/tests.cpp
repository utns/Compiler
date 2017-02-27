#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "scanner.h"

std::string fileToString(std::string name) {
    std::ifstream fout(name);
    std::stringstream sout;
    sout << fout.rdbuf();
    return sout.str();
}

TEST(ScannerTests, test000) {
    Scanner scanner("test000.in");
    EXPECT_EQ(fileToString("test000.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test000.in");
}

TEST(ScannerTests, test001) {
    Scanner scanner("test001.in");
    EXPECT_EQ(fileToString("test001.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test001.in");
}

TEST(ScannerTests, test002) {
    Scanner scanner("test002.in");
    EXPECT_EQ(fileToString("test002.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test002.in");
}

TEST(ScannerTests, test003) {
    Scanner scanner("test003.in");
    EXPECT_EQ(fileToString("test003.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test003.in");
}

TEST(ScannerTests, test004) {
    Scanner scanner("test004.in");
    EXPECT_EQ(fileToString("test004.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test004.in");
}

TEST(ScannerTests, test005) {
    Scanner scanner("test005.in");
    EXPECT_EQ(fileToString("test005.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test005.in");
}

TEST(ScannerTests, test006) {
    Scanner scanner("test006.in");
    EXPECT_EQ(fileToString("test006.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test006.in");
}

TEST(ScannerTests, test007) {
    Scanner scanner("test007.in");
    EXPECT_EQ(fileToString("test007.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test007.in");
}

TEST(ScannerTests, test008) {
    Scanner scanner("test008.in");
    EXPECT_EQ(fileToString("test008.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test008.in");
}

TEST(ScannerTests, test009) {
    Scanner scanner("test009.in");
    EXPECT_EQ(fileToString("test009.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test009.in");
}

TEST(ScannerTests, test010) {
    Scanner scanner("test010.in");
    EXPECT_EQ(fileToString("test010.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test010.in");
}

TEST(ScannerTests, test011) {
    Scanner scanner("test011.in");
    EXPECT_EQ(fileToString("test011.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test011.in");
}

TEST(ScannerTests, test012) {
    Scanner scanner("test012.in");
    EXPECT_EQ(fileToString("test012.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test012.in");
}

TEST(ScannerTests, test013) {
    Scanner scanner("test013.in");
    EXPECT_EQ(fileToString("test013.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test013.in");
}

TEST(ScannerTests, test014) {
    Scanner scanner("test014.in");
    EXPECT_EQ(fileToString("test014.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test014.in");
}

TEST(ScannerTests, test015) {
    Scanner scanner("test015.in");
    EXPECT_EQ(fileToString("test015.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test015.in");
}

TEST(ScannerTests, test016) {
    Scanner scanner("test016.in");
    EXPECT_EQ(fileToString("test016.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test016.in");
}

TEST(ScannerTests, test017) {
    Scanner scanner("test017.in");
    EXPECT_EQ(fileToString("test017.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test017.in");
}

TEST(ScannerTests, test018) {
    Scanner scanner("test018.in");
    EXPECT_EQ(fileToString("test018.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test018.in");
}

TEST(ScannerTests, test019) {
    Scanner scanner("test019.in");
    EXPECT_EQ(fileToString("test019.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test019.in");
}

TEST(ScannerTests, test020) {
    Scanner scanner("test020.in");
    EXPECT_EQ(fileToString("test020.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test020.in");
}

TEST(ScannerTests, test021) {
    Scanner scanner("test021.in");
    EXPECT_EQ(fileToString("test021.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test021.in");
}

TEST(ScannerTests, test022) {
    Scanner scanner("test022.in");
    EXPECT_EQ(fileToString("test022.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test022.in");
}

TEST(ScannerTests, test023) {
    Scanner scanner("test023.in");
    EXPECT_EQ(fileToString("test023.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test023.in");
}

TEST(ScannerTests, test024) {
    Scanner scanner("test024.in");
    EXPECT_EQ(fileToString("test024.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test024.in");
}

TEST(ScannerTests, test025) {
    Scanner scanner("test025.in");
    EXPECT_EQ(fileToString("test025.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test025.in");
}

TEST(ScannerTests, test026) {
    Scanner scanner("test026.in");
    EXPECT_EQ(fileToString("test026.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test026.in");
}

TEST(ScannerTests, test027) {
    Scanner scanner("test027.in");
    EXPECT_EQ(fileToString("test027.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test027.in");
}

TEST(ScannerTests, test028) {
    Scanner scanner("test028.in");
    EXPECT_EQ(fileToString("test028.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test028.in");
}

TEST(ScannerTests, test029) {
    Scanner scanner("test029.in");
    EXPECT_EQ(fileToString("test029.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test029.in");
}

TEST(ScannerTests, test030) {
    Scanner scanner("test030.in");
    EXPECT_EQ(fileToString("test030.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test030.in");
}

TEST(ScannerTests, test031) {
    Scanner scanner("test031.in");
    EXPECT_EQ(fileToString("test031.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("test031.in");
}

