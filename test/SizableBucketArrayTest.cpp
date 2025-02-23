#include <list>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SizableBucketArray.hpp"

using testing::InSequence;
using testing::NiceMock;
using testing::StrictMock;
using testing::Mock;
using testing::ElementsAreArray;
using testing::AtLeast;

using namespace container;

TEST(SizableBucketArray, Test_1)
{
    const SizableBucketArray<int, 4> sizableBucketArray = {};

    ASSERT_EQ(sizableBucketArray.maxElemPerBucket(), 4);
    ASSERT_TRUE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 0);
    ASSERT_EQ(sizableBucketArray.capacity(), 0);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.bucketSize(1); },
                 std::out_of_range);

    const std::set<int> s;
    const SizableBucketArray<int, 4> sizableBucketArray2(s.cbegin(), s.cend());

    ASSERT_EQ(sizableBucketArray2.maxElemPerBucket(), 4);
    ASSERT_TRUE(sizableBucketArray2.empty());
    ASSERT_EQ(sizableBucketArray2.size(), 0);
    ASSERT_EQ(sizableBucketArray2.capacity(), 0);
    ASSERT_EQ(sizableBucketArray2.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.bucketSize(1); },
                 std::out_of_range);

    EXPECT_EQ(sizableBucketArray, sizableBucketArray2);

    const std::list<int> l;
    const SizableBucketArray<int, 4> sizableBucketArray3(l);

    ASSERT_EQ(sizableBucketArray3.maxElemPerBucket(), 4);
    ASSERT_TRUE(sizableBucketArray3.empty());
    ASSERT_EQ(sizableBucketArray3.size(), 0);
    ASSERT_EQ(sizableBucketArray3.capacity(), 0);
    ASSERT_EQ(sizableBucketArray3.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.bucketSize(1); },
                 std::out_of_range);

    EXPECT_EQ(sizableBucketArray2, sizableBucketArray3);

    SizableBucketArray<int, 4> sizableBucketArray4;

    ASSERT_EQ(sizableBucketArray4.maxElemPerBucket(), 4);
    ASSERT_TRUE(sizableBucketArray4.empty());
    ASSERT_EQ(sizableBucketArray4.size(), 0);
    ASSERT_EQ(sizableBucketArray4.capacity(), 0);
    ASSERT_EQ(sizableBucketArray4.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.bucketSize(1); },
                 std::out_of_range);

    sizableBucketArray4 = sizableBucketArray3;

    ASSERT_TRUE(sizableBucketArray4.empty());
    ASSERT_EQ(sizableBucketArray4.size(), 0);
    ASSERT_EQ(sizableBucketArray4.capacity(), 0);
    ASSERT_EQ(sizableBucketArray4.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.bucketSize(1); },
                 std::out_of_range);

    EXPECT_EQ(sizableBucketArray3, sizableBucketArray4);

    SizableBucketArray<int, 4> sizableBucketArray5;

    ASSERT_EQ(sizableBucketArray5.maxElemPerBucket(), 4);
    ASSERT_TRUE(sizableBucketArray5.empty());
    ASSERT_EQ(sizableBucketArray5.size(), 0);
    ASSERT_EQ(sizableBucketArray5.capacity(), 0);
    ASSERT_EQ(sizableBucketArray5.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.bucketSize(1); },
                 std::out_of_range);

    sizableBucketArray5 = std::move(sizableBucketArray4);

    ASSERT_TRUE(sizableBucketArray4.empty());
    ASSERT_EQ(sizableBucketArray4.size(), 0);
    ASSERT_EQ(sizableBucketArray4.capacity(), 0);
    ASSERT_EQ(sizableBucketArray4.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.bucketSize(1); },
                 std::out_of_range);

    ASSERT_EQ(sizableBucketArray5.maxElemPerBucket(), 4);
    ASSERT_TRUE(sizableBucketArray5.empty());
    ASSERT_EQ(sizableBucketArray5.size(), 0);
    ASSERT_EQ(sizableBucketArray5.capacity(), 0);
    ASSERT_EQ(sizableBucketArray5.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray5.bucketSize(1); },
                 std::out_of_range);

    EXPECT_EQ(sizableBucketArray4, sizableBucketArray5);
}

TEST(SizableBucketArray, Test_2)
{
    const SizableBucketArray<int, 3> sizableBucketArray = {1, 2, 3, 4, 5};

    ASSERT_EQ(sizableBucketArray.maxElemPerBucket(), 3);
    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 5);
    ASSERT_EQ(sizableBucketArray.capacity(), 6);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray.at(0), 1);
    EXPECT_EQ(sizableBucketArray.at(1), 2);
    EXPECT_EQ(sizableBucketArray.at(2), 3);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 2);
    EXPECT_EQ(sizableBucketArray.at(3), 4);
    EXPECT_EQ(sizableBucketArray.at(4), 5);

    SizableBucketArray<int, 3> sizableBucketArray2 = sizableBucketArray;

    ASSERT_EQ(sizableBucketArray2.maxElemPerBucket(), 3);
    ASSERT_FALSE(sizableBucketArray2.empty());
    ASSERT_EQ(sizableBucketArray2.size(), 5);
    ASSERT_EQ(sizableBucketArray2.capacity(), 6);
    ASSERT_EQ(sizableBucketArray2.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray2.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray2.at(0), 1);
    EXPECT_EQ(sizableBucketArray2.at(1), 2);
    EXPECT_EQ(sizableBucketArray2.at(2), 3);
    ASSERT_EQ(sizableBucketArray2.bucketSize(1), 2);
    EXPECT_EQ(sizableBucketArray2.at(3), 4);
    EXPECT_EQ(sizableBucketArray2.at(4), 5);

    EXPECT_EQ(sizableBucketArray, sizableBucketArray2);

    const SizableBucketArray<int, 3> sizableBucketArray3 =
        std::move(sizableBucketArray2);

    ASSERT_EQ(sizableBucketArray2.maxElemPerBucket(), 3);
    ASSERT_TRUE(sizableBucketArray2.empty());
    ASSERT_EQ(sizableBucketArray2.size(), 0);
    ASSERT_EQ(sizableBucketArray2.capacity(), 0);
    ASSERT_EQ(sizableBucketArray2.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.bucketSize(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(4); },
                 std::out_of_range);

    ASSERT_EQ(sizableBucketArray3.maxElemPerBucket(), 3);
    ASSERT_FALSE(sizableBucketArray3.empty());
    ASSERT_EQ(sizableBucketArray3.size(), 5);
    ASSERT_EQ(sizableBucketArray3.capacity(), 6);
    ASSERT_EQ(sizableBucketArray3.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray3.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray3.at(0), 1);
    EXPECT_EQ(sizableBucketArray3.at(1), 2);
    EXPECT_EQ(sizableBucketArray3.at(2), 3);
    ASSERT_EQ(sizableBucketArray3.bucketSize(1), 2);
    EXPECT_EQ(sizableBucketArray3.at(3), 4);
    EXPECT_EQ(sizableBucketArray3.at(4), 5);

    EXPECT_NE(sizableBucketArray2, sizableBucketArray3);

    std::vector<int> v = {6, 7, 8, 9, 10, 11, 12};
    const SizableBucketArray<int, 3> sizableBucketArray4(v.begin(), v.end());

    ASSERT_EQ(sizableBucketArray4.maxElemPerBucket(), 3);
    ASSERT_FALSE(sizableBucketArray4.empty());
    ASSERT_EQ(sizableBucketArray4.size(), 7);
    ASSERT_EQ(sizableBucketArray4.capacity(), 9);
    ASSERT_EQ(sizableBucketArray4.bucketCount(), 3);
    ASSERT_EQ(sizableBucketArray4.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray4.at(0), 6);
    EXPECT_EQ(sizableBucketArray4.at(1), 7);
    EXPECT_EQ(sizableBucketArray4.at(2), 8);
    ASSERT_EQ(sizableBucketArray4.bucketSize(1), 3);
    EXPECT_EQ(sizableBucketArray4.at(3), 9);
    EXPECT_EQ(sizableBucketArray4.at(4), 10);
    EXPECT_EQ(sizableBucketArray4.at(5), 11);
    ASSERT_EQ(sizableBucketArray4.bucketSize(2), 1);
    EXPECT_EQ(sizableBucketArray4.at(6), 12);

    EXPECT_NE(sizableBucketArray3, sizableBucketArray4);

    int a[3] = {13, 14, 15};
    const SizableBucketArray<int, 3> sizableBucketArray5 = a;

    ASSERT_EQ(sizableBucketArray5.maxElemPerBucket(), 3);
    ASSERT_FALSE(sizableBucketArray5.empty());
    ASSERT_EQ(sizableBucketArray5.size(), 3);
    ASSERT_EQ(sizableBucketArray5.capacity(), 3);
    ASSERT_EQ(sizableBucketArray5.bucketCount(), 1);
    ASSERT_EQ(sizableBucketArray5.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray5.at(0), 13);
    EXPECT_EQ(sizableBucketArray5.at(1), 14);
    EXPECT_EQ(sizableBucketArray5.at(2), 15);

    EXPECT_NE(sizableBucketArray4, sizableBucketArray5);

    SizableBucketArray<int, 3> sizableBucketArray6 = {1, 2, 3, 4, 5, 6, 7};

    ASSERT_EQ(sizableBucketArray6.maxElemPerBucket(), 3);
    ASSERT_FALSE(sizableBucketArray6.empty());
    ASSERT_EQ(sizableBucketArray6.size(), 7);
    ASSERT_EQ(sizableBucketArray6.capacity(), 9);
    ASSERT_EQ(sizableBucketArray6.bucketCount(), 3);
    ASSERT_EQ(sizableBucketArray6.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray6.at(0), 1);
    EXPECT_EQ(sizableBucketArray6.at(1), 2);
    EXPECT_EQ(sizableBucketArray6.at(2), 3);
    ASSERT_EQ(sizableBucketArray6.bucketSize(1), 3);
    EXPECT_EQ(sizableBucketArray6.at(3), 4);
    EXPECT_EQ(sizableBucketArray6.at(4), 5);
    EXPECT_EQ(sizableBucketArray6.at(5), 6);
    ASSERT_EQ(sizableBucketArray6.bucketSize(2), 1);
    EXPECT_EQ(sizableBucketArray6.at(6), 7);

    sizableBucketArray6 = sizableBucketArray5;

    ASSERT_EQ(sizableBucketArray6.maxElemPerBucket(), 3);
    ASSERT_FALSE(sizableBucketArray6.empty());
    ASSERT_EQ(sizableBucketArray6.size(), 3);
    ASSERT_EQ(sizableBucketArray6.capacity(), 9);
    ASSERT_EQ(sizableBucketArray6.bucketCount(), 3);
    ASSERT_EQ(sizableBucketArray6.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray6.at(0), 13);
    EXPECT_EQ(sizableBucketArray6.at(1), 14);
    EXPECT_EQ(sizableBucketArray6.at(2), 15);
    ASSERT_EQ(sizableBucketArray6.bucketSize(1), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray6.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray6.at(4); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray6.at(5); },
                 std::out_of_range);
    ASSERT_EQ(sizableBucketArray6.bucketSize(2), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray6.at(6); },
                 std::out_of_range);

    EXPECT_EQ(sizableBucketArray5, sizableBucketArray6);

    SizableBucketArray<int, 3> sizableBucketArray7 = {1, 2, 3, 4};

    ASSERT_EQ(sizableBucketArray7.maxElemPerBucket(), 3);
    ASSERT_FALSE(sizableBucketArray7.empty());
    ASSERT_EQ(sizableBucketArray7.size(), 4);
    ASSERT_EQ(sizableBucketArray7.capacity(), 6);
    ASSERT_EQ(sizableBucketArray7.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray7.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray7.at(0), 1);
    EXPECT_EQ(sizableBucketArray7.at(1), 2);
    EXPECT_EQ(sizableBucketArray7.at(2), 3);
    ASSERT_EQ(sizableBucketArray7.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray7.at(3), 4);

    sizableBucketArray7 = std::move(sizableBucketArray6);

    ASSERT_EQ(sizableBucketArray6.maxElemPerBucket(), 3);
    ASSERT_TRUE(sizableBucketArray6.empty());
    ASSERT_EQ(sizableBucketArray6.size(), 0);
    ASSERT_EQ(sizableBucketArray6.capacity(), 0);
    ASSERT_EQ(sizableBucketArray6.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray6.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray6.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray6.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray6.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray6.bucketSize(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray6.at(3); },
                 std::out_of_range);

    ASSERT_EQ(sizableBucketArray7.maxElemPerBucket(), 3);
    ASSERT_FALSE(sizableBucketArray7.empty());
    ASSERT_EQ(sizableBucketArray7.size(), 3);
    ASSERT_EQ(sizableBucketArray7.capacity(), 9);
    ASSERT_EQ(sizableBucketArray7.bucketCount(), 3);
    ASSERT_EQ(sizableBucketArray7.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray7.at(0), 13);
    EXPECT_EQ(sizableBucketArray7.at(1), 14);
    EXPECT_EQ(sizableBucketArray7.at(2), 15);
    ASSERT_EQ(sizableBucketArray7.bucketSize(1), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray7.at(3); },
                 std::out_of_range);

    EXPECT_NE(sizableBucketArray6, sizableBucketArray7);
}

TEST(SizableBucketArray, Test_3)
{
    const SizableBucketArray<int, 1> sizableBucketArray = {0, 1, 2};

    ASSERT_EQ(sizableBucketArray.maxElemPerBucket(), 1);
    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 3);
    ASSERT_EQ(sizableBucketArray.capacity(), 3);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 3);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 1);
    EXPECT_EQ(sizableBucketArray.at(0), 0);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray.at(1), 1);
    ASSERT_EQ(sizableBucketArray.bucketSize(2), 1);
    EXPECT_EQ(sizableBucketArray.at(2), 2);

    SizableBucketArray<int, 2> sizableBucketArray2;

    ASSERT_EQ(sizableBucketArray2.maxElemPerBucket(), 2);
    ASSERT_TRUE(sizableBucketArray2.empty());
    ASSERT_EQ(sizableBucketArray2.size(), 0);
    ASSERT_EQ(sizableBucketArray2.capacity(), 0);
    ASSERT_EQ(sizableBucketArray2.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.bucketSize(1); },
                 std::out_of_range);

    sizableBucketArray2 = sizableBucketArray;

    ASSERT_EQ(sizableBucketArray2.maxElemPerBucket(), 2);
    ASSERT_FALSE(sizableBucketArray2.empty());
    ASSERT_EQ(sizableBucketArray2.size(), 3);
    ASSERT_EQ(sizableBucketArray2.capacity(), 4);
    ASSERT_EQ(sizableBucketArray2.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray2.bucketSize(0), 2);
    EXPECT_EQ(sizableBucketArray2.at(0), 0);
    EXPECT_EQ(sizableBucketArray2.at(1), 1);
    ASSERT_EQ(sizableBucketArray2.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray2.at(2), 2);

    EXPECT_EQ(sizableBucketArray, sizableBucketArray2);

    SizableBucketArray<int, 10> sizableBucketArray3 = std::move(sizableBucketArray2);

    ASSERT_EQ(sizableBucketArray2.maxElemPerBucket(), 2);
    ASSERT_TRUE(sizableBucketArray2.empty());
    ASSERT_EQ(sizableBucketArray2.size(), 0);
    ASSERT_EQ(sizableBucketArray2.capacity(), 0);
    ASSERT_EQ(sizableBucketArray2.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(2); },
                 std::out_of_range);

    ASSERT_EQ(sizableBucketArray3.maxElemPerBucket(), 10);
    ASSERT_FALSE(sizableBucketArray3.empty());
    ASSERT_EQ(sizableBucketArray3.size(), 3);
    ASSERT_EQ(sizableBucketArray3.capacity(), 10);
    ASSERT_EQ(sizableBucketArray3.bucketCount(), 1);
    ASSERT_EQ(sizableBucketArray3.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray3.at(0), 0);
    EXPECT_EQ(sizableBucketArray3.at(1), 1);
    EXPECT_EQ(sizableBucketArray3.at(2), 2);

    EXPECT_NE(sizableBucketArray2, sizableBucketArray3);

    SizableBucketArray<int, 5> sizableBucketArray4;

    ASSERT_EQ(sizableBucketArray4.maxElemPerBucket(), 5);
    ASSERT_TRUE(sizableBucketArray4.empty());
    ASSERT_EQ(sizableBucketArray4.size(), 0);
    ASSERT_EQ(sizableBucketArray4.capacity(), 0);
    ASSERT_EQ(sizableBucketArray4.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.bucketSize(1); },
                 std::out_of_range);

    sizableBucketArray4 = std::move(sizableBucketArray3);

    ASSERT_EQ(sizableBucketArray3.maxElemPerBucket(), 10);
    ASSERT_TRUE(sizableBucketArray3.empty());
    ASSERT_EQ(sizableBucketArray3.size(), 0);
    ASSERT_EQ(sizableBucketArray3.capacity(), 0);
    ASSERT_EQ(sizableBucketArray3.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(2); },
                 std::out_of_range);

    ASSERT_EQ(sizableBucketArray4.maxElemPerBucket(), 5);
    ASSERT_FALSE(sizableBucketArray4.empty());
    ASSERT_EQ(sizableBucketArray4.size(), 3);
    ASSERT_EQ(sizableBucketArray4.capacity(), 5);
    ASSERT_EQ(sizableBucketArray4.bucketCount(), 1);
    ASSERT_EQ(sizableBucketArray4.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray4.at(0), 0);
    EXPECT_EQ(sizableBucketArray4.at(1), 1);
    EXPECT_EQ(sizableBucketArray4.at(2), 2);

    EXPECT_NE(sizableBucketArray3, sizableBucketArray4);

    SizableBucketArray<int, 7> sizableBucketArray5 = {1, 2, 3, 4, 5, 6, 7, 8};

    ASSERT_EQ(sizableBucketArray5.maxElemPerBucket(), 7);
    ASSERT_FALSE(sizableBucketArray5.empty());
    ASSERT_EQ(sizableBucketArray5.size(), 8);
    ASSERT_EQ(sizableBucketArray5.capacity(), 14);
    ASSERT_EQ(sizableBucketArray5.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray5.bucketSize(0), 7);
    EXPECT_EQ(sizableBucketArray5.at(0), 1);
    EXPECT_EQ(sizableBucketArray5.at(1), 2);
    EXPECT_EQ(sizableBucketArray5.at(2), 3);
    EXPECT_EQ(sizableBucketArray5.at(3), 4);
    EXPECT_EQ(sizableBucketArray5.at(4), 5);
    EXPECT_EQ(sizableBucketArray5.at(5), 6);
    EXPECT_EQ(sizableBucketArray5.at(6), 7);
    ASSERT_EQ(sizableBucketArray5.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray5.at(7), 8);

    sizableBucketArray5 = sizableBucketArray4;

    ASSERT_FALSE(sizableBucketArray5.empty());
    ASSERT_EQ(sizableBucketArray5.size(), 3);
    ASSERT_EQ(sizableBucketArray5.capacity(), 14);
    ASSERT_EQ(sizableBucketArray5.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray5.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray5.at(0), 0);
    EXPECT_EQ(sizableBucketArray5.at(1), 1);
    EXPECT_EQ(sizableBucketArray5.at(2), 2);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(4); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(5); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(6); },
                 std::out_of_range);
    ASSERT_EQ(sizableBucketArray5.bucketSize(1), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(7); },
                 std::out_of_range);

    EXPECT_EQ(sizableBucketArray4, sizableBucketArray5);

    const SizableBucketArray<int, 1> sizableBucketArray6 = sizableBucketArray5;

    ASSERT_EQ(sizableBucketArray6.maxElemPerBucket(), 1);
    ASSERT_FALSE(sizableBucketArray6.empty());
    ASSERT_EQ(sizableBucketArray6.size(), 3);
    ASSERT_EQ(sizableBucketArray6.capacity(), 3);
    ASSERT_EQ(sizableBucketArray6.bucketCount(), 3);
    ASSERT_EQ(sizableBucketArray6.bucketSize(0), 1);
    EXPECT_EQ(sizableBucketArray6.at(0), 0);
    ASSERT_EQ(sizableBucketArray6.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray6.at(1), 1);
    ASSERT_EQ(sizableBucketArray6.bucketSize(2), 1);
    EXPECT_EQ(sizableBucketArray6.at(2), 2);

    EXPECT_EQ(sizableBucketArray5, sizableBucketArray6);

    const SizableBucketArray<int, 15> sizableBucketArray7 = sizableBucketArray6;

    ASSERT_EQ(sizableBucketArray7.maxElemPerBucket(), 15);
    ASSERT_FALSE(sizableBucketArray7.empty());
    ASSERT_EQ(sizableBucketArray7.size(), 3);
    ASSERT_EQ(sizableBucketArray7.capacity(), 15);
    ASSERT_EQ(sizableBucketArray7.bucketCount(), 1);
    ASSERT_EQ(sizableBucketArray7.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray6.at(0), 0);
    EXPECT_EQ(sizableBucketArray6.at(1), 1);
    EXPECT_EQ(sizableBucketArray6.at(2), 2);

    EXPECT_EQ(sizableBucketArray6, sizableBucketArray7);
}

TEST(SizableBucketArray, Test_4)
{
    SizableBucketArray<int, 2> sizableBucketArray;

    ASSERT_EQ(sizableBucketArray.maxElemPerBucket(), 2);
    ASSERT_TRUE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 0);
    ASSERT_EQ(sizableBucketArray.capacity(), 0);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.bucketSize(1); },
                 std::out_of_range);

    sizableBucketArray.emplaceBack(1);

    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 1);
    ASSERT_EQ(sizableBucketArray.capacity(), 2);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 1);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 1);
    EXPECT_EQ(sizableBucketArray.at(0), 1);

    sizableBucketArray.emplaceBack(2);
    sizableBucketArray.emplaceBack(3);

    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 3);
    ASSERT_EQ(sizableBucketArray.capacity(), 4);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 2);
    EXPECT_EQ(sizableBucketArray.at(0), 1);
    EXPECT_EQ(sizableBucketArray.at(1), 2);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray.at(2), 3);

    sizableBucketArray.emplaceBack(4);
    sizableBucketArray.emplaceBack(5);
    sizableBucketArray.emplaceBack(6);

    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 6);
    ASSERT_EQ(sizableBucketArray.capacity(), 6);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 3);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 2);
    EXPECT_EQ(sizableBucketArray.at(0), 1);
    EXPECT_EQ(sizableBucketArray.at(1), 2);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 2);
    EXPECT_EQ(sizableBucketArray.at(2), 3);
    EXPECT_EQ(sizableBucketArray.at(3), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(2), 2);
    EXPECT_EQ(sizableBucketArray.at(4), 5);
    EXPECT_EQ(sizableBucketArray.at(5), 6);

    sizableBucketArray.emplaceFront(7);

    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 7);
    ASSERT_EQ(sizableBucketArray.capacity(), 8);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 2);
    EXPECT_EQ(sizableBucketArray.at(0), 7);
    EXPECT_EQ(sizableBucketArray.at(1), 1);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 2);
    EXPECT_EQ(sizableBucketArray.at(2), 2);
    EXPECT_EQ(sizableBucketArray.at(3), 3);
    ASSERT_EQ(sizableBucketArray.bucketSize(2), 2);
    EXPECT_EQ(sizableBucketArray.at(4), 4);
    EXPECT_EQ(sizableBucketArray.at(5), 5);
    ASSERT_EQ(sizableBucketArray.bucketSize(3), 1);
    EXPECT_EQ(sizableBucketArray.at(6), 6);

    sizableBucketArray.emplaceFront(8);
    sizableBucketArray.emplaceFront(9);

    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 9);
    ASSERT_EQ(sizableBucketArray.capacity(), 10);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 5);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 2);
    EXPECT_EQ(sizableBucketArray.at(0), 9);
    EXPECT_EQ(sizableBucketArray.at(1), 8);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 2);
    EXPECT_EQ(sizableBucketArray.at(2), 7);
    EXPECT_EQ(sizableBucketArray.at(3), 1);
    ASSERT_EQ(sizableBucketArray.bucketSize(2), 2);
    EXPECT_EQ(sizableBucketArray.at(4), 2);
    EXPECT_EQ(sizableBucketArray.at(5), 3);
    ASSERT_EQ(sizableBucketArray.bucketSize(3), 2);
    EXPECT_EQ(sizableBucketArray.at(6), 4);
    EXPECT_EQ(sizableBucketArray.at(7), 5);
    ASSERT_EQ(sizableBucketArray.bucketSize(4), 1);
    EXPECT_EQ(sizableBucketArray.at(8), 6);

    sizableBucketArray.emplaceFront(10);
    sizableBucketArray.emplaceFront(11);
    sizableBucketArray.emplaceFront(12);

    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 12);
    ASSERT_EQ(sizableBucketArray.capacity(), 12);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 6);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 2);
    EXPECT_EQ(sizableBucketArray.at(0), 12);
    EXPECT_EQ(sizableBucketArray.at(1), 11);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 2);
    EXPECT_EQ(sizableBucketArray.at(2), 10);
    EXPECT_EQ(sizableBucketArray.at(3), 9);
    ASSERT_EQ(sizableBucketArray.bucketSize(2), 2);
    EXPECT_EQ(sizableBucketArray.at(4), 8);
    EXPECT_EQ(sizableBucketArray.at(5), 7);
    ASSERT_EQ(sizableBucketArray.bucketSize(3), 2);
    EXPECT_EQ(sizableBucketArray.at(6), 1);
    EXPECT_EQ(sizableBucketArray.at(7), 2);
    ASSERT_EQ(sizableBucketArray.bucketSize(4), 2);
    EXPECT_EQ(sizableBucketArray.at(8), 3);
    EXPECT_EQ(sizableBucketArray.at(9), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(5), 2);
    EXPECT_EQ(sizableBucketArray.at(10), 5);
    EXPECT_EQ(sizableBucketArray.at(11), 6);
}

TEST(SizableBucketArray, Test_5)
{
    SizableBucketArray<int, 6> sizableBucketArray;

    ASSERT_EQ(sizableBucketArray.maxElemPerBucket(), 6);
    ASSERT_TRUE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 0);
    ASSERT_EQ(sizableBucketArray.capacity(), 0);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.bucketSize(1); },
                 std::out_of_range);

    sizableBucketArray.emplaceFront(3);
    sizableBucketArray.emplaceFront(2);
    sizableBucketArray.emplaceFront(1);

    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 3);
    ASSERT_EQ(sizableBucketArray.capacity(), 6);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 1);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray.at(0), 1);
    EXPECT_EQ(sizableBucketArray.at(1), 2);
    EXPECT_EQ(sizableBucketArray.at(2), 3);

    sizableBucketArray.emplaceFront(4);
    sizableBucketArray.emplaceBack(5);
    sizableBucketArray.emplaceFront(6);
    sizableBucketArray.emplaceFront(7);
    sizableBucketArray.emplaceBack(8);
    sizableBucketArray.emplaceBack(9);

    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 9);
    ASSERT_EQ(sizableBucketArray.capacity(), 12);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 6);
    EXPECT_EQ(sizableBucketArray.at(0), 7);
    EXPECT_EQ(sizableBucketArray.at(1), 6);
    EXPECT_EQ(sizableBucketArray.at(2), 4);
    EXPECT_EQ(sizableBucketArray.at(3), 1);
    EXPECT_EQ(sizableBucketArray.at(4), 2);
    EXPECT_EQ(sizableBucketArray.at(5), 3);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 3);
    EXPECT_EQ(sizableBucketArray.at(6), 5);
    EXPECT_EQ(sizableBucketArray.at(7), 8);
    EXPECT_EQ(sizableBucketArray.at(8), 9);

    auto elementsChecker = [&sizableBucketArray](
        auto begin, auto end, auto expectations) -> void
    {
        EXPECT_TRUE(begin != end);
        EXPECT_FALSE(begin == end);

        std::vector<int> elements;

        elements.reserve(sizableBucketArray.size());

        while (begin != end)
        {
            EXPECT_EQ(begin.operator->(), &*begin);

            elements.emplace_back(*begin);
            ++begin;
        }

        EXPECT_THAT(elements, ElementsAreArray(expectations));
    };

    elementsChecker(sizableBucketArray.begin(),
                    sizableBucketArray.end(),
                    std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});
    elementsChecker(sizableBucketArray.cbegin(),
                    sizableBucketArray.cend(),
                    std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});
    elementsChecker(sizableBucketArray.rbegin(),
                    sizableBucketArray.rend(),
                    std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});
    elementsChecker(sizableBucketArray.rcbegin(),
                    sizableBucketArray.rcend(),
                    std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});

    auto elementsChecker2 = [&sizableBucketArray](
        auto begin, auto end, auto expectations) -> void
    {
        EXPECT_TRUE(begin != end);
        EXPECT_FALSE(begin == end);

        std::vector<int> elements;

        elements.reserve(sizableBucketArray.size());

        while (begin != end)
        {
            EXPECT_EQ(begin.operator->(), &*begin);

            elements.emplace_back(*begin++);
        }

        EXPECT_THAT(elements, ElementsAreArray(expectations));
    };

    elementsChecker2(sizableBucketArray.begin(),
                     sizableBucketArray.end(),
                     std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});
    elementsChecker2(sizableBucketArray.cbegin(),
                     sizableBucketArray.cend(),
                     std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});
    elementsChecker2(sizableBucketArray.rbegin(),
                     sizableBucketArray.rend(),
                     std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});
    elementsChecker2(sizableBucketArray.rcbegin(),
                     sizableBucketArray.rcend(),
                     std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});

    auto elementsChecker3 = [&sizableBucketArray](
        auto begin, auto end, auto expectations) -> void
    {
        EXPECT_TRUE(begin != end);
        EXPECT_FALSE(begin == end);

        std::vector<int> elements;

        elements.reserve(sizableBucketArray.size());

        while (begin != end)
        {
            EXPECT_EQ(begin.operator->(), &*begin);

            elements.emplace_back(*begin);
            begin += 1;
        }

        EXPECT_THAT(elements, ElementsAreArray(expectations));
    };

    elementsChecker3(sizableBucketArray.begin(),
                     sizableBucketArray.end(),
                     std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});
    elementsChecker3(sizableBucketArray.cbegin(),
                     sizableBucketArray.cend(),
                     std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});
    elementsChecker3(sizableBucketArray.rbegin(),
                     sizableBucketArray.rend(),
                     std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});
    elementsChecker3(sizableBucketArray.rcbegin(),
                     sizableBucketArray.rcend(),
                     std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});

    auto elementsChecker4 = [&sizableBucketArray](
        auto it, auto expectations) -> void
    {
        const size_t sizableBucketArraySize = sizableBucketArray.size();
        std::vector<int> elements;

        elements.reserve(sizableBucketArraySize);

        for (uint32_t index = 0; index < sizableBucketArraySize; ++index)
        {
            EXPECT_EQ(it.operator->(), &*it);

            elements.emplace_back(*it);
            --it;
        }

        EXPECT_THAT(elements, ElementsAreArray(expectations));
    };

    elementsChecker4(
        sizableBucketArray.begin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});
    elementsChecker4(
        sizableBucketArray.cbegin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});
    elementsChecker4(
        sizableBucketArray.rbegin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});
    elementsChecker4(
        sizableBucketArray.rcbegin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});

    auto elementsChecker5 = [&sizableBucketArray](
        auto it, auto expectations) -> void
    {
        const size_t sizableBucketArraySize = sizableBucketArray.size();
        std::vector<int> elements;

        elements.reserve(sizableBucketArraySize);

        for (uint32_t index = 0; index < sizableBucketArraySize; ++index)
        {
            EXPECT_EQ(it.operator->(), &*it);

            elements.emplace_back(*it--);
        }

        EXPECT_THAT(elements, ElementsAreArray(expectations));
    };

    elementsChecker5(
        sizableBucketArray.begin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});
    elementsChecker5(
        sizableBucketArray.cbegin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});
    elementsChecker5(
        sizableBucketArray.rbegin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});
    elementsChecker5(
        sizableBucketArray.rcbegin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});

    auto elementsChecker6 = [&sizableBucketArray](
        auto it, auto expectations) -> void
    {
        const size_t sizableBucketArraySize = sizableBucketArray.size();
        std::vector<int> elements;

        elements.reserve(sizableBucketArraySize);

        for (uint32_t index = 0; index < sizableBucketArraySize; ++index)
        {
            EXPECT_EQ(it.operator->(), &*it);

            elements.emplace_back(*it);
            it -= 1;
        }

        EXPECT_THAT(elements, ElementsAreArray(expectations));
    };

    elementsChecker6(
        sizableBucketArray.begin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});
    elementsChecker6(
        sizableBucketArray.cbegin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{9, 8, 5, 3, 2, 1, 4, 6, 7});
    elementsChecker6(
        sizableBucketArray.rbegin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});
    elementsChecker6(
        sizableBucketArray.rcbegin() + (sizableBucketArray.size() - 1),
        std::initializer_list<int>{7, 6, 4, 1, 2, 3, 5, 8, 9});
}

TEST(SizableBucketArray, Test_6)
{
    SizableBucketArray<int, 1> sizableBucketArray;

    ASSERT_EQ(sizableBucketArray.maxElemPerBucket(), 1);
    ASSERT_TRUE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 0);
    ASSERT_EQ(sizableBucketArray.capacity(), 0);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.bucketSize(1); },
                 std::out_of_range);

    sizableBucketArray.emplaceFront(1);
    sizableBucketArray.emplaceBack(2);
    sizableBucketArray.emplaceFront(3);
    sizableBucketArray.emplaceBack(4);

    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 4);
    ASSERT_EQ(sizableBucketArray.capacity(), 4);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 1);
    EXPECT_EQ(sizableBucketArray.at(0), 3);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray.at(1), 1);
    ASSERT_EQ(sizableBucketArray.bucketSize(2), 1);
    EXPECT_EQ(sizableBucketArray.at(2), 2);
    ASSERT_EQ(sizableBucketArray.bucketSize(3), 1);
    EXPECT_EQ(sizableBucketArray.at(3), 4);

    SizableBucketArray<int, 1>::Iterator it =
        sizableBucketArray.begin();

    EXPECT_EQ(it[0], 3);
    EXPECT_EQ(it[1], 1);
    EXPECT_EQ(it[2], 2);
    EXPECT_EQ(it[3], 4);

    it = it + 2;

    EXPECT_EQ(*it, 2);

    it = sizableBucketArray.erase(it);

    EXPECT_EQ(*it, 4);

    ASSERT_EQ(sizableBucketArray.size(), 3);
    ASSERT_EQ(sizableBucketArray.capacity(), 4);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 1);
    EXPECT_EQ(sizableBucketArray.at(0), 3);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray.at(1), 1);
    ASSERT_EQ(sizableBucketArray.bucketSize(2), 1);
    EXPECT_EQ(sizableBucketArray.at(2), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(3), 0);

    SizableBucketArray<int, 1>::ConstIterator it2 = it;

    EXPECT_EQ(it, it2);

    it2 = it2 - 2;
    it2 = sizableBucketArray.erase(it2);

    EXPECT_EQ(*it2, 1);

    ASSERT_EQ(sizableBucketArray.size(), 2);
    ASSERT_EQ(sizableBucketArray.capacity(), 4);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 1);
    EXPECT_EQ(sizableBucketArray.at(0), 1);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray.at(1), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(2), 0);
    ASSERT_EQ(sizableBucketArray.bucketSize(3), 0);

    SizableBucketArray<int, 1>::ReverseIterator it3 =
        sizableBucketArray.rbegin();

    EXPECT_EQ(it3[0], 1);
    EXPECT_EQ(it3[1], 4);

    SizableBucketArray<int, 1>::ConstReverseIterator it4 = it3 + 1;

    EXPECT_NE(it3, it4);
    EXPECT_EQ(*it4, 1);

    it4 = it4 - 1;

    EXPECT_EQ(it3, it4);
    EXPECT_EQ(*it4, 4);

    it2 = it2 + 1;

    EXPECT_EQ(*it2, 4);

    it2 = sizableBucketArray.erase(it2);

    EXPECT_EQ(*it2, 4);

    ASSERT_EQ(sizableBucketArray.size(), 1);
    ASSERT_EQ(sizableBucketArray.capacity(), 4);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 1);
    EXPECT_EQ(sizableBucketArray.at(0), 1);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 0);
    ASSERT_EQ(sizableBucketArray.bucketSize(2), 0);
    ASSERT_EQ(sizableBucketArray.bucketSize(3), 0);

    it2 = it2 - 1;

    EXPECT_EQ(*it2, 1);

    it2 = sizableBucketArray.erase(it2);

    EXPECT_EQ(*it2, 1);

    ASSERT_EQ(sizableBucketArray.size(), 0);
    ASSERT_EQ(sizableBucketArray.capacity(), 4);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 0);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 0);
    ASSERT_EQ(sizableBucketArray.bucketSize(2), 0);
    ASSERT_EQ(sizableBucketArray.bucketSize(3), 0);

    sizableBucketArray.emplaceFront(6);
    sizableBucketArray.emplaceBack(7);
    sizableBucketArray.emplaceFront(5);

    ASSERT_EQ(sizableBucketArray.size(), 3);
    ASSERT_EQ(sizableBucketArray.capacity(), 4);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 1);
    EXPECT_EQ(sizableBucketArray.at(0), 5);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray.at(1), 6);
    ASSERT_EQ(sizableBucketArray.bucketSize(2), 1);
    EXPECT_EQ(sizableBucketArray.at(2), 7);
    ASSERT_EQ(sizableBucketArray.bucketSize(3), 0);
}

TEST(SizableBucketArray, Test_7)
{
    SizableBucketArray<int, 4> sizableBucketArray = {1, 2, 3, 4, 5};

    ASSERT_EQ(sizableBucketArray.maxElemPerBucket(), 4);
    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 5);
    ASSERT_EQ(sizableBucketArray.capacity(), 8);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 4);
    EXPECT_EQ(sizableBucketArray.at(0), 1);
    EXPECT_EQ(sizableBucketArray.at(1), 2);
    EXPECT_EQ(sizableBucketArray.at(2), 3);
    EXPECT_EQ(sizableBucketArray.at(3), 4);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray.at(4), 5);

    SizableBucketArray<int, 4>::ConstIterator it =
        sizableBucketArray.cbegin() + 2;

    EXPECT_EQ(*it, 3);

    it = sizableBucketArray.erase(it);

    EXPECT_EQ(*it, 4);

    it = sizableBucketArray.erase(it);

    EXPECT_EQ(*it, 5);

    ASSERT_FALSE(sizableBucketArray.empty());
    ASSERT_EQ(sizableBucketArray.size(), 3);
    ASSERT_EQ(sizableBucketArray.capacity(), 8);
    ASSERT_EQ(sizableBucketArray.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray.at(0), 1);
    EXPECT_EQ(sizableBucketArray.at(1), 2);
    EXPECT_EQ(sizableBucketArray.at(2), 5);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(3); },
                 std::out_of_range);
    ASSERT_EQ(sizableBucketArray.bucketSize(1), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(4); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(5); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(6); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray.at(7); },
                 std::out_of_range);

    SizableBucketArray<int, 2> sizableBucketArray2 = sizableBucketArray;

    ASSERT_EQ(sizableBucketArray2.maxElemPerBucket(), 2);
    ASSERT_FALSE(sizableBucketArray2.empty());
    ASSERT_EQ(sizableBucketArray2.size(), 3);
    ASSERT_EQ(sizableBucketArray2.capacity(), 4);
    ASSERT_EQ(sizableBucketArray2.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray2.bucketSize(0), 2);
    EXPECT_EQ(sizableBucketArray2.at(0), 1);
    EXPECT_EQ(sizableBucketArray2.at(1), 2);
    ASSERT_EQ(sizableBucketArray2.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray2.at(2), 5);

    EXPECT_EQ(sizableBucketArray, sizableBucketArray2);

    sizableBucketArray2.clear();

    ASSERT_TRUE(sizableBucketArray2.empty());
    ASSERT_EQ(sizableBucketArray2.size(), 0);
    ASSERT_EQ(sizableBucketArray2.capacity(), 4);
    ASSERT_EQ(sizableBucketArray2.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray2.bucketSize(0), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(1); },
                 std::out_of_range);
    ASSERT_EQ(sizableBucketArray2.bucketSize(1), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(2); },
                 std::out_of_range);

    sizableBucketArray2.emplaceFront(3);

    ASSERT_FALSE(sizableBucketArray2.empty());
    ASSERT_EQ(sizableBucketArray2.size(), 1);
    ASSERT_EQ(sizableBucketArray2.capacity(), 4);
    ASSERT_EQ(sizableBucketArray2.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray2.bucketSize(0), 1);
    EXPECT_EQ(sizableBucketArray2.at(0), 3);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(1); },
                 std::out_of_range);
    ASSERT_EQ(sizableBucketArray2.bucketSize(1), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(2); },
                 std::out_of_range);

    SizableBucketArray<int, 7> sizableBucketArray3 = {1, 2, 3, 4, 5, 6, 7, 8};

    ASSERT_EQ(sizableBucketArray3.maxElemPerBucket(), 7);
    ASSERT_FALSE(sizableBucketArray3.empty());
    ASSERT_EQ(sizableBucketArray3.size(), 8);
    ASSERT_EQ(sizableBucketArray3.capacity(), 14);
    ASSERT_EQ(sizableBucketArray3.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray3.bucketSize(0), 7);
    EXPECT_EQ(sizableBucketArray3.at(0), 1);
    EXPECT_EQ(sizableBucketArray3.at(1), 2);
    EXPECT_EQ(sizableBucketArray3.at(2), 3);
    EXPECT_EQ(sizableBucketArray3.at(3), 4);
    EXPECT_EQ(sizableBucketArray3.at(4), 5);
    EXPECT_EQ(sizableBucketArray3.at(5), 6);
    EXPECT_EQ(sizableBucketArray3.at(6), 7);
    ASSERT_EQ(sizableBucketArray3.bucketSize(1), 1);
    EXPECT_EQ(sizableBucketArray3.at(7), 8);

    sizableBucketArray3 = std::move(sizableBucketArray2);
    sizableBucketArray2.clear();

    ASSERT_TRUE(sizableBucketArray2.empty());
    ASSERT_EQ(sizableBucketArray2.size(), 0);
    ASSERT_EQ(sizableBucketArray2.capacity(), 0);
    ASSERT_EQ(sizableBucketArray2.bucketCount(), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.bucketSize(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.bucketSize(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray2.at(2); },
                 std::out_of_range);

    ASSERT_FALSE(sizableBucketArray3.empty());
    ASSERT_EQ(sizableBucketArray3.size(), 1);
    ASSERT_EQ(sizableBucketArray3.capacity(), 14);
    ASSERT_EQ(sizableBucketArray3.bucketCount(), 2);
    ASSERT_EQ(sizableBucketArray3.bucketSize(0), 1);
    EXPECT_EQ(sizableBucketArray3.at(0), 3);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(4); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(5); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(6); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray3.at(7); },
                 std::out_of_range);

    EXPECT_NE(sizableBucketArray2, sizableBucketArray3);

    SizableBucketArray<int, 7>::Iterator it2 =
        sizableBucketArray3.begin();

    *it2 = 42;

    EXPECT_EQ(sizableBucketArray3.at(0), 42);

    sizableBucketArray3.emplaceBack(43);
    sizableBucketArray3.emplaceBack(44);

    it2++;
    *it2 = 83;

    EXPECT_EQ(sizableBucketArray3.at(1), 83);

    it2 = it2 + 1;
    *it2 = 124;

    EXPECT_EQ(sizableBucketArray3.at(2), 124);

    it2 = sizableBucketArray3.erase(it2);

    EXPECT_EQ(it2, sizableBucketArray3.cend());

    it2 -= 2;

    EXPECT_EQ(it2, sizableBucketArray3.cbegin());

    sizableBucketArray3.emplaceBack(124);

    EXPECT_EQ(sizableBucketArray3.at(2), 124);

    SizableBucketArray<int, 5> sizableBucketArray4 = {1, 2, 3, 4, 5};

    ASSERT_EQ(sizableBucketArray4.maxElemPerBucket(), 5);
    ASSERT_FALSE(sizableBucketArray4.empty());
    ASSERT_EQ(sizableBucketArray4.size(), 5);
    ASSERT_EQ(sizableBucketArray4.capacity(), 5);
    ASSERT_EQ(sizableBucketArray4.bucketCount(), 1);
    ASSERT_EQ(sizableBucketArray4.bucketSize(0), 5);
    EXPECT_EQ(sizableBucketArray4.at(0), 1);
    EXPECT_EQ(sizableBucketArray4.at(1), 2);
    EXPECT_EQ(sizableBucketArray4.at(2), 3);
    EXPECT_EQ(sizableBucketArray4.at(3), 4);
    EXPECT_EQ(sizableBucketArray4.at(4), 5);

    sizableBucketArray4 = sizableBucketArray3;

    ASSERT_FALSE(sizableBucketArray4.empty());
    ASSERT_EQ(sizableBucketArray4.size(), 3);
    ASSERT_EQ(sizableBucketArray4.capacity(), 5);
    ASSERT_EQ(sizableBucketArray4.bucketCount(), 1);
    ASSERT_EQ(sizableBucketArray4.bucketSize(0), 3);
    EXPECT_EQ(sizableBucketArray4.at(0), 42);
    EXPECT_EQ(sizableBucketArray4.at(1), 83);
    EXPECT_EQ(sizableBucketArray4.at(2), 124);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(4); },
                 std::out_of_range);

    EXPECT_EQ(sizableBucketArray3, sizableBucketArray4);

    SizableBucketArray<int, 5>::ReverseIterator it3 =
        sizableBucketArray4.rbegin();

    *it3 = 100;

    EXPECT_EQ(sizableBucketArray4.at(2), 100);

    it3 = it3 + 1;
    *it3 = 50;

    EXPECT_EQ(sizableBucketArray4.at(1), 50);

    it3 += 2;

    EXPECT_EQ(it3, sizableBucketArray4.rcend());

    it3 = it3 - 3;

    EXPECT_EQ(it3, sizableBucketArray4.rbegin());

    sizableBucketArray4.emplaceFront(21);
    sizableBucketArray4.emplaceFront(14);

    ASSERT_FALSE(sizableBucketArray4.empty());
    ASSERT_EQ(sizableBucketArray4.size(), 5);
    ASSERT_EQ(sizableBucketArray4.capacity(), 5);
    ASSERT_EQ(sizableBucketArray4.bucketCount(), 1);
    ASSERT_EQ(sizableBucketArray4.bucketSize(0), 5);
    EXPECT_EQ(sizableBucketArray4.at(0), 14);
    EXPECT_EQ(sizableBucketArray4.at(1), 21);
    EXPECT_EQ(sizableBucketArray4.at(2), 42);
    EXPECT_EQ(sizableBucketArray4.at(3), 50);
    EXPECT_EQ(sizableBucketArray4.at(4), 100);

    sizableBucketArray4.clear();

    ASSERT_TRUE(sizableBucketArray4.empty());
    ASSERT_EQ(sizableBucketArray4.size(), 0);
    ASSERT_EQ(sizableBucketArray4.capacity(), 5);
    ASSERT_EQ(sizableBucketArray4.bucketCount(), 1);
    ASSERT_EQ(sizableBucketArray4.bucketSize(0), 0);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(0); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(1); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(2); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(3); },
                 std::out_of_range);
    EXPECT_THROW({ [[maybe_unused]] auto _ = sizableBucketArray4.at(4); },
                 std::out_of_range);

    EXPECT_EQ(sizableBucketArray4, (SizableBucketArray<int, 12>{}));
    EXPECT_NE(sizableBucketArray4, (SizableBucketArray<int, 3>{1, 2, 3}));

    SizableBucketArray<int, 7> sizableBucketArray5 = {14, 21, 42, 50, 100};

    ASSERT_EQ(sizableBucketArray5.maxElemPerBucket(), 7);
    ASSERT_FALSE(sizableBucketArray5.empty());
    ASSERT_EQ(sizableBucketArray5.size(), 5);
    ASSERT_EQ(sizableBucketArray5.capacity(), 7);
    ASSERT_EQ(sizableBucketArray5.bucketCount(), 1);
    ASSERT_EQ(sizableBucketArray5.bucketSize(0), 5);
    EXPECT_EQ(sizableBucketArray5.at(0), 14);
    EXPECT_EQ(sizableBucketArray5.at(1), 21);
    EXPECT_EQ(sizableBucketArray5.at(2), 42);
    EXPECT_EQ(sizableBucketArray5.at(3), 50);
    EXPECT_EQ(sizableBucketArray5.at(4), 100);

    sizableBucketArray5.clear();

    EXPECT_EQ(sizableBucketArray4, sizableBucketArray5);
}

// SBA = SizableBucketArray
template <template <typename> class MockWrapper>
class SBAFixtureBase : public testing::Test
{
protected :
    /* to check the right number of call on constructors, destructors and
       assignment operators in SizableBucketArray code */
    class MyMock
    {
    public :
        MOCK_METHOD(void, onDefaultConstructor, (), (const, noexcept));
        MOCK_METHOD(void, onCopyConstructor, (), (const, noexcept));
        MOCK_METHOD(void, onMoveConstructor, (), (const, noexcept));
        MOCK_METHOD(void, onDestructor, (), (const, noexcept));
        MOCK_METHOD(void, onCopyAssignment, (), (const, noexcept));
        MOCK_METHOD(void, onMoveAssignment, (), (const, noexcept));
    };

    void SetUp() override { Element::mockPtr = &_mock; }
    void TearDown() override { Element::mockPtr = nullptr; }

    template <typename Functor>
    void startTest(Functor test)
    {
        InSequence s;

        test(_mock);
        Mock::VerifyAndClear(&_mock);
    }

public :
    using Mock_t = MockWrapper<MyMock>;

    /* to test with a element of class type if everything works
       fine + right number of call on constructors, destructor
       and assignment operators */
    class Element
    {
    public :
        static Mock_t *mockPtr;

        Element() noexcept { mockPtr->onDefaultConstructor(); }
        Element(const Element&) noexcept { mockPtr->onCopyConstructor(); }
        Element(Element&&) noexcept { mockPtr->onMoveConstructor(); }
        ~Element() noexcept { mockPtr->onDestructor(); }

        Element& operator=(const Element&) noexcept
        {
            mockPtr->onCopyAssignment();

            return *this;
        }

        Element& operator=(Element&&) noexcept
        {
            mockPtr->onMoveAssignment();

            return *this;
        }
    };

private :
    Mock_t _mock;
};

class SBAFixture_1 : public SBAFixtureBase<StrictMock> { };
class SBAFixture_2 : public SBAFixtureBase<NiceMock> { };

using Mock_t_1 = typename SBAFixtureBase<StrictMock>::Mock_t;
using Mock_t_2 = typename SBAFixtureBase<NiceMock>::Mock_t;

using Element_t_1 = typename SBAFixtureBase<StrictMock>::Element;
using Element_t_2 = typename SBAFixtureBase<NiceMock>::Element;

template <>
Mock_t_1 *Element_t_1::mockPtr = nullptr;

template <>
Mock_t_2 *Element_t_2::mockPtr = nullptr;

TEST_F(SBAFixture_1, Test_8)
{
    using Mock_t = Mock_t_1;
    using Element_t = Element_t_1;

    startTest([](Mock_t&) -> void
    {
        const SizableBucketArray<Element_t, 4> sizableBucketArray;
    });

    startTest([](Mock_t&) -> void
    {
        const SizableBucketArray<Element_t, 4> sizableBucketArray;
        const SizableBucketArray<Element_t, 4> sizableBucketArray2 =
            sizableBucketArray;
    });

    startTest([](Mock_t&) -> void
    {
        SizableBucketArray<Element_t, 4> sizableBucketArray;
        const SizableBucketArray<Element_t, 4> sizableBucketArray2 =
            std::move(sizableBucketArray);
    });

    startTest([](Mock_t&) -> void
    {
        const SizableBucketArray<Element_t, 4> sizableBucketArray;
        SizableBucketArray<Element_t, 4> sizableBucketArray2;

        sizableBucketArray2 = sizableBucketArray;
    });

    startTest([](Mock_t&) -> void
    {
        SizableBucketArray<Element_t, 4> sizableBucketArray;
        SizableBucketArray<Element_t, 4> sizableBucketArray2;

        sizableBucketArray2 = std::move(sizableBucketArray);
    });

    startTest([](Mock_t&) -> void
    {
        const std::initializer_list<Element_t> l;
        const SizableBucketArray<Element_t, 4> sizableBucketArray(l);
    });

    startTest([](Mock_t&) -> void
    {
        const std::vector<Element_t> v;
        const SizableBucketArray<Element_t, 4> sizableBucketArray(
            v.cbegin(), v.cend());
    });

    startTest([](Mock_t&) -> void
    {
        const std::list<Element_t> l;
        const SizableBucketArray<Element_t, 4> sizableBucketArray(l);
    });
}

TEST_F(SBAFixture_2, Test_9)
{
    using Mock_t = Mock_t_2;
    using Element_t = Element_t_2;

    startTest([](Mock_t& mock) -> void
    {
        SizableBucketArray<Element_t, 3> sizableBucketArray = {
            Element_t(),
            Element_t(),
            Element_t()};

        EXPECT_CALL(mock, onCopyConstructor()).Times(3);

        SizableBucketArray<Element_t, 3> sizableBucketArray2 =
            sizableBucketArray;

        sizableBucketArray.clear();

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });

    startTest([](Mock_t& mock) -> void
    {
        SizableBucketArray<Element_t, 3> sizableBucketArray = {
            Element_t(),
            Element_t(),
            Element_t()};
        SizableBucketArray<Element_t, 3> sizableBucketArray2 =
            std::move(sizableBucketArray);

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });

    startTest([](Mock_t& mock) -> void
    {
        SizableBucketArray<Element_t, 3> sizableBucketArray = {
            Element_t(),
            Element_t(),
            Element_t()};
        SizableBucketArray<Element_t, 3> sizableBucketArray2;

        EXPECT_CALL(mock, onDefaultConstructor()).Times(3);
        EXPECT_CALL(mock, onCopyAssignment()).Times(3);

        sizableBucketArray2 = sizableBucketArray;
        sizableBucketArray.clear();

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });

    startTest([](Mock_t& mock) -> void
    {
        SizableBucketArray<Element_t, 3> sizableBucketArray = {
            Element_t(),
            Element_t(),
            Element_t()};
        SizableBucketArray<Element_t, 3> sizableBucketArray2;

        sizableBucketArray2 = std::move(sizableBucketArray);

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });

    startTest([](Mock_t& mock) -> void
    {
        EXPECT_CALL(mock, onCopyConstructor()).Times(3);

        SizableBucketArray<Element_t, 3> sizableBucketArray = {
            Element_t(),
            Element_t(),
            Element_t()};

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });

    startTest([](Mock_t& mock) -> void
    {
        std::vector<Element_t> v(3);

        EXPECT_CALL(mock, onCopyConstructor()).Times(3);

        SizableBucketArray<Element_t, 3> sizableBucketArray(v.cbegin(), v.cend());

        v.clear();

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });

    startTest([](Mock_t& mock) -> void
    {
        std::list<Element_t> l(3);

        EXPECT_CALL(mock, onCopyConstructor()).Times(3);

        SizableBucketArray<Element_t, 3> sizableBucketArray(l);

        l.clear();

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });
}

TEST_F(SBAFixture_2, Test_10)
{
    using Mock_t = Mock_t_2;
    using Element_t = Element_t_2;

    startTest([](Mock_t& mock) -> void
    {
        SizableBucketArray<Element_t, 5> sizableBucketArray = {
            Element_t(),
            Element_t(),
            Element_t()};

        EXPECT_CALL(mock, onCopyConstructor()).Times(3);

        SizableBucketArray<Element_t, 1> sizableBucketArray2 =
            sizableBucketArray;

        sizableBucketArray.clear();

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });

    startTest([](Mock_t& mock) -> void
    {
        SizableBucketArray<Element_t, 1> sizableBucketArray = {
            Element_t(),
            Element_t(),
            Element_t()};

        EXPECT_CALL(mock, onMoveConstructor()).Times(3);
        EXPECT_CALL(mock, onDestructor()).Times(3);

        SizableBucketArray<Element_t, 2> sizableBucketArray2 =
            std::move(sizableBucketArray);

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });

    startTest([](Mock_t& mock) -> void
    {
        SizableBucketArray<Element_t, 5> sizableBucketArray = {
            Element_t(),
            Element_t(),
            Element_t()};
        SizableBucketArray<Element_t, 1> sizableBucketArray2;

        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onCopyAssignment());
        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onCopyAssignment());
        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onCopyAssignment());

        sizableBucketArray2 = sizableBucketArray;
        sizableBucketArray.clear();

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });

    startTest([](Mock_t& mock) -> void
    {
        SizableBucketArray<Element_t, 1> sizableBucketArray = {
            Element_t(),
            Element_t(),
            Element_t()};
        SizableBucketArray<Element_t, 2> sizableBucketArray2;

        EXPECT_CALL(mock, onDefaultConstructor()).Times(2);
        EXPECT_CALL(mock, onMoveAssignment()).Times(2);
        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onMoveAssignment());
        EXPECT_CALL(mock, onDestructor()).Times(3);

        sizableBucketArray2 = std::move(sizableBucketArray);

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });
}

TEST_F(SBAFixture_2, Test_11)
{
    using Mock_t = Mock_t_2;
    using Element_t = Element_t_2;

    startTest([](Mock_t& mock) -> void
    {
        SizableBucketArray<Element_t, 1> sizableBucketArray;

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray.emplaceFront();

        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(AtLeast(1));
        sizableBucketArray.emplaceFront();

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray.emplaceBack();

        EXPECT_CALL(mock, onDestructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(1);
        sizableBucketArray.erase(sizableBucketArray.cbegin() + 1);

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray.emplaceBack();

        EXPECT_CALL(mock, onDestructor()).Times(3);
    });

    startTest([](Mock_t& mock) -> void
    {
        SizableBucketArray<Element_t, 3> sizableBucketArray;

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray.emplaceBack();

        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onMoveAssignment());
        sizableBucketArray.emplaceFront();

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray.emplaceBack();

        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(AtLeast(3));
        sizableBucketArray.emplaceFront();

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray.emplaceBack();

        EXPECT_CALL(mock, onDestructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(0);
        sizableBucketArray.erase(sizableBucketArray.cend() - 1);

        EXPECT_CALL(mock, onDestructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(3);
        sizableBucketArray.erase(sizableBucketArray.cbegin());

        EXPECT_CALL(mock, onDestructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(1);
        sizableBucketArray.erase(sizableBucketArray.cbegin() + 1);

        EXPECT_CALL(mock, onDestructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(0);
        sizableBucketArray.erase(sizableBucketArray.cend() - 1);

        EXPECT_CALL(mock, onDestructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(0);
        sizableBucketArray.erase(sizableBucketArray.cbegin());

        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(0);
        sizableBucketArray.emplaceFront();

        EXPECT_CALL(mock, onDestructor()).Times(1);
    });
}

TEST_F(SBAFixture_2, Test_12)
{
    using Mock_t = Mock_t_2;
    using Element_t = Element_t_2;

    startTest([](Mock_t& mock) -> void
    {
        EXPECT_CALL(mock, onCopyConstructor()).Times(3);

        SizableBucketArray<Element_t, 1> sizableBucketArray = {
            Element_t(),
            Element_t(),
            Element_t()};

        EXPECT_CALL(mock, onCopyConstructor()).Times(2);

        SizableBucketArray<Element_t, 4> sizableBucketArray2 = {
            Element_t(),
            Element_t()};

        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(AtLeast(2));
        sizableBucketArray2.emplaceFront();

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray2.emplaceBack();

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray2.emplaceBack();

        EXPECT_CALL(mock, onCopyAssignment()).Times(3);
        EXPECT_CALL(mock, onDestructor()).Times(2);
        sizableBucketArray2 = sizableBucketArray;

        EXPECT_CALL(mock, onDestructor()).Times(3);
        sizableBucketArray.clear();

        EXPECT_CALL(mock, onDestructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(2);
        sizableBucketArray2.erase(sizableBucketArray2.cbegin());

        EXPECT_CALL(mock, onDestructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(0);
        sizableBucketArray2.erase(sizableBucketArray2.cend());

        // workaround : should not be necessary normally
        Mock::VerifyAndClear(&mock);

        EXPECT_CALL(mock, onCopyConstructor()).Times(9);

        SizableBucketArray<Element_t, 10> sizableBucketArray3 = {
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t()};

        EXPECT_CALL(mock, onDestructor());
        EXPECT_CALL(mock, onDefaultConstructor()).Times(4);
        EXPECT_CALL(mock, onCopyAssignment()).Times(4);
        EXPECT_CALL(mock, onDefaultConstructor()).Times(4);
        EXPECT_CALL(mock, onCopyAssignment()).Times(4);
        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onCopyAssignment());
        sizableBucketArray2 = sizableBucketArray3;

        EXPECT_CALL(mock, onDestructor()).Times(9);
        sizableBucketArray3.clear();

        EXPECT_CALL(mock, onDestructor()).Times(9);
        sizableBucketArray2.clear();

        SizableBucketArray<Element_t, 7> sizableBucketArray4;

        EXPECT_CALL(mock, onCopyAssignment()).Times(0);
        sizableBucketArray2 = sizableBucketArray4;

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray2.emplaceBack();

        // workaround : should not be necessary normally
        Mock::VerifyAndClear(&mock);

        EXPECT_CALL(mock, onCopyConstructor()).Times(6);

        SizableBucketArray<Element_t, 13> sizableBucketArray5 = {
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t()};

        EXPECT_CALL(mock, onDefaultConstructor()).Times(3);
        EXPECT_CALL(mock, onCopyAssignment()).Times(4);
        EXPECT_CALL(mock, onDefaultConstructor()).Times(2);
        EXPECT_CALL(mock, onCopyAssignment()).Times(2);
        sizableBucketArray2 = sizableBucketArray5;

        EXPECT_CALL(mock, onDestructor()).Times(6);
        sizableBucketArray5.clear();

        EXPECT_CALL(mock, onDestructor()).Times(6);
    });

    startTest([](Mock_t& mock) -> void
    {
        EXPECT_CALL(mock, onCopyConstructor()).Times(5);

        SizableBucketArray<Element_t, 4> sizableBucketArray = {
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t()};
        SizableBucketArray<Element_t, 2> sizableBucketArray2;

        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(0);
        sizableBucketArray2.emplaceFront();

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray2.emplaceBack();

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray2.emplaceBack();

        EXPECT_CALL(mock, onDestructor()).Times(3);
        EXPECT_CALL(mock, onDefaultConstructor()).Times(2);
        EXPECT_CALL(mock, onMoveAssignment()).Times(2);
        EXPECT_CALL(mock, onDefaultConstructor()).Times(2);
        EXPECT_CALL(mock, onMoveAssignment()).Times(2);
        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onMoveAssignment());
        EXPECT_CALL(mock, onDestructor()).Times(5);

        sizableBucketArray2 = std::move(sizableBucketArray);

        // workaround : should not be necessary normally
        Mock::VerifyAndClear(&mock);

        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(AtLeast(5));
        sizableBucketArray2.emplaceFront();

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray2.emplaceBack();

        // workaround : should not be necessary normally
        Mock::VerifyAndClear(&mock);

        EXPECT_CALL(mock, onCopyConstructor()).Times(10);

        SizableBucketArray<Element_t, 3> sizableBucketArray3 = {
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t()};

        EXPECT_CALL(mock, onMoveAssignment()).Times(7);
        EXPECT_CALL(mock, onDestructor()).Times(10);
        sizableBucketArray3 = std::move(sizableBucketArray2);

        EXPECT_CALL(mock, onDestructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(0);
        sizableBucketArray3.erase(sizableBucketArray3.cend() - 1);

        EXPECT_CALL(mock, onDestructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(2);
        sizableBucketArray3.erase(sizableBucketArray3.cend() - 3);

        // workaround : should not be necessary normally
        Mock::VerifyAndClear(&mock);

        EXPECT_CALL(mock, onCopyConstructor()).Times(5);

        SizableBucketArray<Element_t, 1> sizableBucketArray4 = {
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t(),
            Element_t()};

        EXPECT_CALL(mock, onMoveAssignment()).Times(5);
        EXPECT_CALL(mock, onDestructor()).Times(5);
        sizableBucketArray4 = std::move(sizableBucketArray3);

        EXPECT_CALL(mock, onDestructor()).Times(5);
        sizableBucketArray4.clear();

        SizableBucketArray<Element_t, 13> sizableBucketArray5;

        EXPECT_CALL(mock, onMoveAssignment()).Times(0);
        sizableBucketArray4 = std::move(sizableBucketArray5);

        EXPECT_CALL(mock, onDefaultConstructor());
        EXPECT_CALL(mock, onMoveAssignment()).Times(0);
        sizableBucketArray4.emplaceFront();

        EXPECT_CALL(mock, onDefaultConstructor());
        sizableBucketArray4.emplaceBack();

        EXPECT_CALL(mock, onDestructor()).Times(2);
    });
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
