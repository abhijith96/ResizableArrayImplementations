//
// Created by Abhijith  K A on 19/06/23.
//
//
// Created by Abhijith  K A on 19/06/23.
//

#include "../HashedArrayTree.h"
#include <gtest/gtest.h>

class HashedArrayTreeTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void InsertElementsToBothArrays(const std::vector<int>& elements){
        for(int i : elements){
            vector_array_.push_back(i);
            hashedArrayTree_.PushBack(i);
        }
    }

    std::vector<int> CreateElementsArray(int size){
        std::vector<int> elements;
        for(int i = 0; i< size;++i){
            elements.push_back(i);
        }
        return elements;
    }

    void PopElements(int size){
        for(int i = 0; i< size;++i){
            hashedArrayTree_.PopBack();
            vector_array_.pop_back();
        }
    }

    bool CompareArrays(const HashedArrayTree<int, 2>& hashedArrayTree, const std::vector<int>& vectorArray){
        if(hashedArrayTree.GetSize() != vectorArray.size()){
            return false;
        }
        int size = hashedArrayTree.GetSize();
        for(int i = 0; i < size; ++i){
            if(hashedArrayTree[i] != vectorArray[i]){
                return false;
            }
        }
        return true;
    }

    bool CompareArraysUsingLocate(const HashedArrayTree<int, 2>& hashedArrayTree, const std::vector<int>& vectorArray){
        if(hashedArrayTree.GetSize() != vectorArray.size()){
            return false;
        }
        int size = hashedArrayTree.GetSize();
        for(int i = 0; i < size; ++i){
            if(hashedArrayTree_.Locate(i) != vectorArray[i]){
                return false;
            }
        }
        return true;
    }

    void TearDown() override {}
    HashedArrayTree<int, 2> hashedArrayTree_;
    std::vector<int> vector_array_;
};

TEST_F(HashedArrayTreeTest, IsEmptyInitially) {
    EXPECT_ANY_THROW(hashedArrayTree_.Locate(0));
}

TEST_F(HashedArrayTreeTest, WithOneElement) {
    hashedArrayTree_.PushBack(1);
    vector_array_.push_back(1);
    EXPECT_NO_THROW(hashedArrayTree_.Locate(0));
    EXPECT_ANY_THROW(hashedArrayTree_.Locate(1));
    EXPECT_ANY_THROW(hashedArrayTree_.Locate(-1));
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
}

TEST_F(HashedArrayTreeTest, _100Elements) {
    auto elements = CreateElementsArray(100);
    InsertElementsToBothArrays(elements);
    EXPECT_ANY_THROW(hashedArrayTree_.Locate(100));
    EXPECT_NO_THROW(hashedArrayTree_.Locate(99));
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
}


TEST_F(HashedArrayTreeTest, _100ElementsUsingLocate) {
    auto elements = CreateElementsArray(100);
    InsertElementsToBothArrays(elements);
    EXPECT_ANY_THROW(hashedArrayTree_.Locate(100));
    EXPECT_NO_THROW(hashedArrayTree_.Locate(99));
    EXPECT_TRUE(CompareArraysUsingLocate(hashedArrayTree_, vector_array_));
}

TEST_F(HashedArrayTreeTest, _100ElementsRandomIndexes) {
    auto elements = CreateElementsArray(100);
    InsertElementsToBothArrays(elements);
    EXPECT_EQ(hashedArrayTree_[50], vector_array_[50]);
    EXPECT_EQ(hashedArrayTree_.Locate(50), vector_array_.at(50));

    EXPECT_EQ(hashedArrayTree_.Locate(50), vector_array_.at(50));

    EXPECT_EQ(hashedArrayTree_.Locate(99), vector_array_.at(99));

    EXPECT_EQ(hashedArrayTree_.Locate(0), vector_array_.at(0));

    EXPECT_EQ(hashedArrayTree_.Locate(50), vector_array_.at(50));

    EXPECT_EQ(hashedArrayTree_.Locate(39), vector_array_.at(39));

    EXPECT_TRUE(CompareArraysUsingLocate(hashedArrayTree_, vector_array_));
}

TEST_F(HashedArrayTreeTest, _1000ElementsUsingLocate) {
    auto elements = CreateElementsArray(1000);
    InsertElementsToBothArrays(elements);
    EXPECT_TRUE(CompareArraysUsingLocate(hashedArrayTree_, vector_array_));
}

TEST_F(HashedArrayTreeTest, _Empty_Insert) {
    EXPECT_ANY_THROW(hashedArrayTree_.Insert(0, 10));
}

TEST_F(HashedArrayTreeTest, _One_Element_Insert) {
    auto elements = CreateElementsArray(1);
    InsertElementsToBothArrays(elements);
    InsertElementsToBothArrays(elements);
    hashedArrayTree_.Insert(0,10);
    vector_array_[0] = 10;
    EXPECT_TRUE(CompareArraysUsingLocate(hashedArrayTree_, vector_array_));
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}