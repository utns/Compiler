import sys
f = open('tests.cpp', 'w')

header = """#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "scanner.h"

std::string fileToString(std::string name) {
    std::ifstream fout(name);
    std::stringstream sout;
    sout << fout.rdbuf();
    return sout.str();
}

"""

f.write(header)

test = """TEST(ScannerTests, {0}) {{
    Scanner scanner("{0}.in");
    EXPECT_EQ(fileToString("{0}.out"), scanner.getTokensString()) << "Input: " << std::endl << fileToString("{0}.in");
}}

"""

for i in range(0, int(sys.argv[1]) + 1):
    f.write(test.format('test{0:03d}'.format(i)))

