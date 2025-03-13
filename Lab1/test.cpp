#include "pch.h"
#include "PaintApplication.h"
#include <iostream>

bool compareBinFiles(const std::string& file1Path, const std::string& file2Path) {
    std::ifstream file1(file1Path, std::ios::binary);
    std::ifstream file2(file2Path, std::ios::binary);
    if (!file1.is_open() || !file2.is_open()) {
        throw std::runtime_error("Could not open one or both files.");
    }
    char byte1, byte2;
    while (file1.get(byte1) && file2.get(byte2)) {
        if (byte1 != byte2) {
            return false;
        }
    }
    return true;
}

TEST(addTest, addTest1) {

  PaintApplication* application = new PaintApplication();
  std::vector<std::string> test = { "add circle 10 10 10", "save test.bin" };
  application->AppForTest(test);

  EXPECT_EQ(compareBinFiles("test.bin", "test1.bin"), true);
  EXPECT_TRUE(true);
}

TEST(addTest, addTest2) {

    PaintApplication* application = new PaintApplication();
    std::vector<std::string> test = { "load test1.bin", "add rectangle 80 80 90 90 " "save test.bin" };
    application->AppForTest(test);

    EXPECT_EQ(compareBinFiles("test.bin", "test2.bin"), true);
    EXPECT_TRUE(true);
}

TEST(moveTest, moveTest1) {

    PaintApplication* application = new PaintApplication();
    std::vector<std::string> test = { "load test1.bin", "move 0 100 100", "save test.bin"};
    application->AppForTest(test);

    EXPECT_EQ(compareBinFiles("test.bin", "test3.bin"), true);
    EXPECT_TRUE(true);
}

TEST(moveTest, moveTest2) {

    PaintApplication* application = new PaintApplication();
    std::vector<std::string> test = { "load test1.bin","move 0 -20 -20", "save test.bin" };
    application->AppForTest(test);

    EXPECT_EQ(compareBinFiles("test.bin", "test4.bin"), true);
    EXPECT_TRUE(true);
}

TEST(removeTest, removeTest1) {

    PaintApplication* application = new PaintApplication();
    std::vector<std::string> test = { "load test1.bin","remove 0", "save test.bin" };
    application->AppForTest(test);

    EXPECT_EQ(compareBinFiles("test.bin", "test5.bin"), true);
    EXPECT_TRUE(true);
}

TEST(removeTest, removeTest2) {

    PaintApplication* application = new PaintApplication();
    std::vector<std::string> test = { "load test1.bin","remove 1", "save test.bin" };
    application->AppForTest(test);

    EXPECT_EQ(compareBinFiles("test.bin", "test1.bin"), true);
    EXPECT_TRUE(true);
}

TEST(fillTest, fillTest1) {

    PaintApplication* application = new PaintApplication();
    std::vector<std::string> test = { "load test1.bin","fill 0", "save test.bin" };
    application->AppForTest(test);

    EXPECT_EQ(compareBinFiles("test.bin", "test7.bin"), true);
    EXPECT_TRUE(true);
}

TEST(fillTest, fillTest2) {

    PaintApplication* application = new PaintApplication();
    std::vector<std::string> test = { "load test1.bin","fill 1", "save test.bin" };
    application->AppForTest(test);

    EXPECT_EQ(compareBinFiles("test.bin", "test1.bin"), true);
    EXPECT_TRUE(true);
}

TEST(undoTest, undoTest) {

    PaintApplication* application = new PaintApplication();
    std::vector<std::string> test = { "load test1.bin","fill 0", "undo" "save test.bin" };
    application->AppForTest(test);

    EXPECT_EQ(compareBinFiles("test.bin", "test1.bin"), true);
    EXPECT_TRUE(true);
}

TEST(redoTest, redoTest) {

    PaintApplication* application = new PaintApplication();
    std::vector<std::string> test = { "load test1.bin","undo","redo", "save test.bin"};
    application->AppForTest(test);

    EXPECT_EQ(compareBinFiles("test.bin", "test1.bin"), true);
    EXPECT_TRUE(true);
}