#include <gtest/gtest.h>

#include "../buffer/buffer.h"

TEST(CircularBufferTest, CreatesWithZeroCapacity) {
    CircularBuffer<std::string> buf;
    buf.pushBack("a");
    buf.pushBack("a");
    EXPECT_TRUE(buf.empty());
}

TEST(CircularBufferTest, CreatesWithSpecifiedCapacity) {
    CircularBuffer<int> buf(5);
    EXPECT_EQ(buf.capacity(), 5);
}

TEST(CircularBufferTest, SetCapacityWorks) {
    CircularBuffer<int> buf = {1, 2, 3, 4};
    buf.pushFront(0);
    buf.setCapacity(2);

    EXPECT_EQ(buf.capacity(), 2);
    EXPECT_EQ(buf.size(), 2);
    EXPECT_TRUE(buf == (CircularBuffer{0, 1}));
}

TEST(CircularBufferTest, CreatesWithSpecifiedCapacityAndSpecifiedItems) {
    CircularBuffer<char> buf(5, 'a');
    EXPECT_EQ(buf.capacity(), 5);
    EXPECT_EQ(buf.size(), 5);
}

TEST(CircularBufferTest, CanAccessElements_WithoutBoundChecking) {
    CircularBuffer<char> buf(5, '0');
    buf.pushBack('0');

    for (int i = 0; i < 5; ++i) {
        buf[i] = static_cast<char>(i);
    }
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(buf[i], i);
    }
}

TEST(CircularBufferTest, CanAccessElements_WithoutBoundChecking_Const) {
    const CircularBuffer<char> buf(5, '0');
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(buf[i], '0');
    }
}

TEST(CircularBufferTest, CanAccessElements_WithBoundChecking) {
    CircularBuffer<char> buf(5, '0');
    buf.pushBack('0');

    for (int i = 0; i < 5; ++i) {
        buf.at(i) = static_cast<char>(i);
    }
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(buf.at(i), i);
    }

    EXPECT_THROW(buf.at(45), std::out_of_range);
}

TEST(CircularBufferTest, CanAccessElements_WithBoundChecking_Const) {
    const CircularBuffer<char> buf(5, '0');

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(buf.at(i), '0');
    }

    EXPECT_THROW(buf.at(45), std::out_of_range);
}

TEST(CircularBufferTest, FrontAndBackWorks) {
    CircularBuffer<char> buf(5, '0');
    buf.pushBack('0');
    EXPECT_EQ(buf.front(), '0');
    EXPECT_EQ(buf.back(), '0');
}

TEST(CircularBufferTest, FrontAndBackWorksConst) {
    const CircularBuffer<char> buf(5, '0');
    EXPECT_EQ(buf.front(), '0');
    EXPECT_EQ(buf.back(), '0');
}

TEST(CircularBufferTest, ResizeWorks_withCapacityExpand) {
    CircularBuffer<char> buf(3, '0');
    buf.resize(5, '1');
    EXPECT_EQ(buf.capacity(), 5);
    EXPECT_EQ(buf.size(), 5);
    EXPECT_TRUE(buf == (CircularBuffer<char>{'0', '0', '0', '1', '1'}));
}

TEST(CircularBufferTest, ResizeWorks_withLessSize) {
    CircularBuffer<int> buf = {1, 2, 3, 4};
    buf.resize(2);
    EXPECT_EQ(buf.capacity(), 2);
    EXPECT_EQ(buf.size(), 2);
    EXPECT_TRUE(buf == (CircularBuffer<int>{1, 2}));
}

TEST(CircularBufferTest, ResizeWorks_withShiftedBuffer_1) {
    CircularBuffer<int> buf = {1, 2, 3, 4};
    buf.resize(8, 5);
    buf.pushFront(0);
    buf.pushFront(0);
    buf.resize(8, 5);
    EXPECT_EQ(buf.size(), 8);
    EXPECT_TRUE(buf == (CircularBuffer<int>{0, 0, 1, 2, 3, 4, 5, 5}));
}

TEST(CircularBufferTest, ResizeWorks_withShiftedBuffer_2) {
    CircularBuffer<int> buf = {1, 2, 3, 4};
    buf.resize(6, 5);
    buf.popFront();
    buf.popFront();
    buf.resize(5, 0);
    EXPECT_EQ(buf.size(), 5);
    EXPECT_TRUE(buf == (CircularBuffer<int>{3, 4, 5, 5, 0}));
}

TEST(CircularBufferTest, PushFrontWorks) {
    CircularBuffer buf = {'1', '2'};
    buf.setCapacity(4);
    buf.pushFront('3');
    EXPECT_EQ(buf[0], '3');
    EXPECT_EQ(buf[1], '1');
    EXPECT_EQ(buf[2], '2');
    EXPECT_EQ(buf.size(), 3);
}

TEST(CircularBufferTest, PushFrontWorks_withFullBuffer) {
    CircularBuffer buf(3, '0');
    buf.pushFront('1');
    buf.pushFront('2');
    EXPECT_EQ(buf[0], '2');
    EXPECT_EQ(buf[1], '1');
    EXPECT_EQ(buf[2], '0');
}

TEST(CircularBufferTest, PushFrontWorks_withZeroCapacity) {
    CircularBuffer<char> buf;
    buf.pushFront('1');
    buf.pushFront('2');
    EXPECT_EQ(buf.size(), 0);
    EXPECT_EQ(buf.capacity(), 0);
}

TEST(CircularBufferTest, PushBackWorks_withFullBuffer) {
    CircularBuffer<char> buf(3, '0');
    buf.pushBack('1');
    buf.pushBack('2');
    EXPECT_EQ(buf[0], '0');
    EXPECT_EQ(buf[1], '1');
    EXPECT_EQ(buf[2], '2');
}

TEST(CircularBufferTest, PushBackWorks_withZeroCapacity) {
    CircularBuffer<char> buf;
    buf.pushBack('1');
    buf.pushBack('2');
    EXPECT_EQ(buf.capacity(), 0);
    EXPECT_EQ(buf.size(), 0);
}

TEST(CircularBufferTest, PushBackWorks) {
    CircularBuffer<char> buf = {'1', '2'};
    buf.setCapacity(3);
    buf.pushBack('3');
    EXPECT_EQ(buf[0], '1');
    EXPECT_EQ(buf[1], '2');
    EXPECT_EQ(buf[2], '3');
    EXPECT_EQ(buf.size(), 3);
}

TEST(CircularBufferTest, PopBackWorks) {
    CircularBuffer<char> buf = {'1', '2', '3'};
    buf.popBack();
    EXPECT_EQ(buf.size(), 2);
    buf.popBack();
    EXPECT_EQ(buf.size(), 1);
    EXPECT_EQ(buf[0], '1');
}

TEST(CircularBufferTest, PopFrontWorks) {
    CircularBuffer<char> buf = {'1', '2', '3'};
    buf.popFront();
    EXPECT_EQ(buf.size(), 2);
    buf.popFront();
    EXPECT_EQ(buf.size(), 1);
    EXPECT_EQ(buf[0], '3');
}

TEST(CircularBufferTest, CreatesWithInitializerList) {
    CircularBuffer<char> buf = {'1', '2', '3'};
    EXPECT_EQ(buf[0], '1');
    EXPECT_EQ(buf[1], '2');
    EXPECT_EQ(buf[2], '3');
}

TEST(CircularBufferTest, LinearizeWorks) {
    CircularBuffer<char> buf = {'1', '2', '3', '4'};
    buf.pushFront('0');
    buf.pushFront('0');
    EXPECT_FALSE(buf.isLinearized());
    buf.linearize();
    EXPECT_TRUE(buf.isLinearized());
    EXPECT_EQ(buf[0], '0');
    EXPECT_EQ(buf[1], '0');
    EXPECT_EQ(buf[2], '1');
    EXPECT_EQ(buf[3], '2');
}

TEST(CircularBufferTest, RotateWorks) {
    CircularBuffer<char> buf = {'1', '2', '3', '4'};
    buf.pushFront('0');
    buf.pushFront('0');
    buf.rotate(3);
    EXPECT_EQ(buf[0], '2');
    EXPECT_EQ(buf[1], '0');
    EXPECT_EQ(buf[2], '0');
    EXPECT_EQ(buf[3], '1');
}

TEST(CircularBufferTest, FullWorks) {
    CircularBuffer<char> buf = {'1', '2', '3', '4'};
    EXPECT_TRUE(buf.full());
    buf.popBack();
    EXPECT_FALSE(buf.full());
}

TEST(CircularBufferTest, InsertWorks) {
    CircularBuffer<int> buf = {1, 2, 3, 4};
    buf.pushFront(0);
    buf.pushFront(0);
    buf.insert(0, 9);
    EXPECT_EQ(buf.size(), 4);
    EXPECT_TRUE(buf == (CircularBuffer<int>{9, 0, 1, 2}));

    buf.resize(10, 0);

    buf.insert(6, 4);
    EXPECT_EQ(buf.size(), 10);
    EXPECT_TRUE(buf == (CircularBuffer<int>{9, 0, 1, 2, 0, 0, 4, 0, 0, 0}));
}

TEST(CircularBufferTest, EraseWorks_1) {
    CircularBuffer<int> buf = {1, 2, 3, 4};
    buf.pushFront(0);
    buf.pushFront(0);
    buf.erase(1, 3);
    EXPECT_EQ(buf.size(), 2);

    EXPECT_TRUE(buf == (CircularBuffer{0, 2}));
}

TEST(CircularBufferTest, EraseWorks_2) {
    CircularBuffer<int> buf = {1, 2, 3, 4, 5, 6, 7, 8};
    buf.pushFront(0);
    buf.pushFront(0);
    buf.pushFront(0);
    buf.erase(1, 5);
    EXPECT_EQ(buf.size(), 4);

    EXPECT_TRUE(buf == (CircularBuffer<int>{0, 3, 4, 5}));
}

TEST(CircularBufferTest, EraseWorks_3) {
    CircularBuffer<int> buf = {0, 0, 0, 0, 1, 2, 3, 4};
    buf.pushBack(5);
    buf.pushBack(6);
    buf.pushBack(7);
    buf.pushBack(8);
    buf.erase(0, 2);
    EXPECT_EQ(buf.size(), 6);

    EXPECT_TRUE(buf == (CircularBuffer<int>{3, 4, 5, 6, 7, 8}));
}

TEST(CircularBufferTest, ClearWorks) {
    CircularBuffer<char> buf = {'1', '2', '3', '4'};
    buf.clear();
    EXPECT_EQ(buf.size(), 0);
    EXPECT_EQ(buf.capacity(), 4);

    buf.pushFront('0');
    EXPECT_EQ(buf[0], '0');
}

TEST(CircularBufferTest, ReserveWorks) {
    CircularBuffer<char> buf(3);
    EXPECT_EQ(buf.reserve(), 3);
    buf.pushFront('0');
    EXPECT_EQ(buf.reserve(), 2);
    buf.pushFront('0');
    EXPECT_EQ(buf.reserve(), 1);
    buf.pushFront('0');
    EXPECT_EQ(buf.reserve(), 0);

}

TEST(CircularBufferTest, OperatorEqualsWorks) {
    CircularBuffer<char> buf1 = {'1', '2', '3', '4'};
    CircularBuffer<char> buf2 = {'1', '2', '9', '4', '5'};
    CircularBuffer<char> buf3 = {'1', '2', '3', '4'};
    EXPECT_FALSE(buf1 == buf2);
    EXPECT_TRUE(buf1 == buf3);
}

TEST(CircularBufferTest, SwapWorks) {
    CircularBuffer<char> buf1 = {'1', '2', '3'};
    CircularBuffer<char> buf2 = {'1', '4', '9'};
    buf1.swap(buf2);
    EXPECT_EQ(buf1[0], '1');
    EXPECT_EQ(buf1[1], '4');
    EXPECT_EQ(buf1[2], '9');
    EXPECT_EQ(buf2[0], '1');
    EXPECT_EQ(buf2[1], '2');
    EXPECT_EQ(buf2[2], '3');
}

TEST(CircularBufferTest, CopyAssignmentOperatorWorks) {
    CircularBuffer<char> buf1 = {'1', '2', '3', '4'};
    CircularBuffer<char> buf2 = {'1', '2', '9', '4'};
    buf1 = buf2;
    EXPECT_TRUE(buf1 == buf2);
}