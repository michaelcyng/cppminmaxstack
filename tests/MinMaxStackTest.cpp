//
// Created by Cho Yiu Ng on 23.09.19.
//

#include <gtest/gtest.h>
#include <MinMaxStack.h>

class MinMaxTests : public ::testing::Test {
protected:

    MinMaxTests() = default;
    ~MinMaxTests() override = default;
    void SetUp() override {}
    void TearDown() override {}

};

TEST_F(MinMaxTests, TestCopyConstruct) {

    MinMaxStack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    MinMaxStack<int> stack2(stack1);
    ASSERT_EQ(stack2.size(), 3);
    ASSERT_EQ(stack2.top(), 3);
    stack2.pop();
    ASSERT_EQ(stack2.size(), 2);
    ASSERT_EQ(stack2.top(), 2);
    stack2.pop();
    ASSERT_EQ(stack2.size(), 1);
    ASSERT_EQ(stack2.top(), 1);
    stack2.pop();
    ASSERT_EQ(stack2.size(), 0);
    ASSERT_TRUE(stack2.empty());

}

TEST_F(MinMaxTests, TestMoveConstruct) {

    MinMaxStack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    MinMaxStack<int> stack2(std::move(stack1));
    ASSERT_TRUE(stack1.empty());
    ASSERT_EQ(stack1.size(), 0);
    ASSERT_EQ(stack2.size(), 3);
    ASSERT_EQ(stack2.top(), 3);
    stack2.pop();
    ASSERT_EQ(stack2.size(), 2);
    ASSERT_EQ(stack2.top(), 2);
    stack2.pop();
    ASSERT_EQ(stack2.size(), 1);
    ASSERT_EQ(stack2.top(), 1);
    stack2.pop();
    ASSERT_EQ(stack2.size(), 0);
    ASSERT_TRUE(stack2.empty());

}

TEST_F(MinMaxTests, TestAssignmentConstruct1) {

    MinMaxStack<int> stack1, stack2;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    stack2 = stack1;
    ASSERT_EQ(stack2.size(), 3);
    ASSERT_EQ(stack2.top(), 3);
    stack2.pop();
    ASSERT_EQ(stack2.size(), 2);
    ASSERT_EQ(stack2.top(), 2);
    stack2.pop();
    ASSERT_EQ(stack2.size(), 1);
    ASSERT_EQ(stack2.top(), 1);
    stack2.pop();
    ASSERT_EQ(stack2.size(), 0);
    ASSERT_TRUE(stack2.empty());

}

TEST_F(MinMaxTests, TestAssignmentConstruct2) {

    MinMaxStack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    stack1 = stack1;
    ASSERT_EQ(stack1.size(), 3);
    ASSERT_EQ(stack1.top(), 3);
    stack1.pop();
    ASSERT_EQ(stack1.size(), 2);
    ASSERT_EQ(stack1.top(), 2);
    stack1.pop();
    ASSERT_EQ(stack1.size(), 1);
    ASSERT_EQ(stack1.top(), 1);
    stack1.pop();
    ASSERT_EQ(stack1.size(), 0);
    ASSERT_TRUE(stack1.empty());

}

TEST_F(MinMaxTests, TestEmpty) {

    MinMaxStack<int> testStack;
    ASSERT_EQ(testStack.size(), 0);
    ASSERT_TRUE(testStack.empty());
    testStack.push(1);
    ASSERT_EQ(testStack.size(), 1);
    ASSERT_FALSE(testStack.empty());
    testStack.pop();
    ASSERT_EQ(testStack.size(), 0);
    ASSERT_TRUE(testStack.empty());

}

TEST_F(MinMaxTests, TestMin) {

    MinMaxStack<int> testStack;
    testStack.push(1);  // 1
    ASSERT_EQ(testStack.min(), 1);
    testStack.push(2);  // 1 2
    ASSERT_EQ(testStack.min(), 1);
    testStack.push(0);  // 1 2 0
    ASSERT_EQ(testStack.min(), 0);
    testStack.push(0);  // 1 2 0 0
    ASSERT_EQ(testStack.min(), 0);
    testStack.pop();  // 1 2 0
    ASSERT_EQ(testStack.min(), 0);
    testStack.pop();  // 1 2
    ASSERT_EQ(testStack.min(), 1);
    testStack.pop();  // 1
    ASSERT_EQ( testStack.min(), 1);
    testStack.pop(); //
    ASSERT_TRUE(testStack.empty());
    testStack.push(2);  // 2
    ASSERT_EQ(testStack.min(), 2);
    testStack.push(1);  // 2 1
    ASSERT_EQ(testStack.min(), 1);
    testStack.pop();  // 2
    ASSERT_EQ(testStack.min(), 2);

}

TEST_F(MinMaxTests, TestMax) {

    MinMaxStack<int> testStack;
    testStack.push(1); // 1
    ASSERT_EQ(testStack.max(), 1);
    testStack.push(2); // 1 2
    ASSERT_EQ(testStack.max(), 2);
    testStack.push(2); // 1 2 2
    ASSERT_EQ(testStack.max(), 2);
    testStack.push(0); // 1 2 2 0
    ASSERT_EQ(testStack.max(), 2);
    testStack.pop(); // 1 2 2
    ASSERT_EQ(testStack.max(), 2);
    testStack.pop(); // 1 2
    ASSERT_EQ(testStack.max(), 2);
    testStack.pop(); // 1
    ASSERT_EQ(testStack.max(), 1);
    testStack.pop(); //
    ASSERT_TRUE(testStack.empty());

}

TEST_F(MinMaxTests, TestSwap) {

    MinMaxStack<int> testStack1;
    testStack1.push(1);
    testStack1.push(2);
    testStack1.push(3);

    MinMaxStack<int> testStack2;
    testStack2.push(4);
    testStack2.push(5);

    testStack1.swap(testStack2);

    ASSERT_EQ(testStack1.size(), 2);
    ASSERT_EQ(testStack1.top(), 5);
    testStack1.pop();
    ASSERT_EQ(testStack1.top(), 4);
    testStack1.pop();
    ASSERT_TRUE(testStack1.empty());

    ASSERT_EQ(testStack2.size(), 3);
    ASSERT_EQ(testStack2.top(), 3);
    testStack2.pop();
    ASSERT_EQ(testStack2.top(), 2);
    testStack2.pop();
    ASSERT_EQ(testStack2.top(), 1);
    testStack2.pop();
    ASSERT_TRUE(testStack2.empty());

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
