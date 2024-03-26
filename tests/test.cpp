#include <lib/allocator.h>

#include <gtest/gtest.h>


TEST(AllocatorTestSuite, Test1) {

    std::vector<double, Allocator<double>> myVector(Allocator<double>({{1,  50},
                                                                       {20, 10},
                                                                       {4,  10}}));

    myVector.push_back(1);
    myVector.push_back(2);
    myVector.push_back(3);
    myVector.push_back(4);
    myVector.push_back(5);

    myVector.push_back(6);
    myVector.push_back(7);
    myVector.push_back(1);
    myVector.push_back(2);
    myVector.push_back(3);

    ASSERT_EQ(myVector[0], 1);
    ASSERT_EQ(myVector[1], 2);
    ASSERT_EQ(myVector[2], 3);
    ASSERT_EQ(myVector[3], 4);
    ASSERT_EQ(myVector[4], 5);

    ASSERT_EQ(myVector[5], 6);
    ASSERT_EQ(myVector[6], 7);
    ASSERT_EQ(myVector[7], 1);
    ASSERT_EQ(myVector[8], 2);
    ASSERT_EQ(myVector[9], 3);
}

TEST(AllocatorTestSuite, TestInt) {
    Allocator<int> alloc({
                                 {1, 5}
                         });
    int* a = alloc.allocate(1);
    *a = 5;

    int* b = alloc.allocate(1);
    *b = 4;

    ASSERT_EQ(*a, 5);
    ASSERT_EQ(*b, 4);
}

TEST(AllocatorTestSuite, TestDouble) {
    Allocator<double> alloc({
                                    {1, 5}
                            });
    double* a = alloc.allocate(1);
    *a = 5;

    double* b = alloc.allocate(1);
    *b = 4;

    ASSERT_EQ(*a, 5);
    ASSERT_EQ(*b, 4);
}