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

    void TearDown() override {}
    HashedArrayTree<int, 2> hashedArrayTree_;
    std::vector<int> vector_array_;
};

TEST_F(HashedArrayTreeTest, IsEmptyInitially) {
    EXPECT_EQ(hashedArrayTree_.GetSize(), 0);
    EXPECT_NO_THROW(hashedArrayTree_.PopBack());
}

TEST_F(HashedArrayTreeTest, WithOneElement) {
    hashedArrayTree_.PushBack(1);
    vector_array_.push_back(1);
    hashedArrayTree_.PopBack();
    vector_array_.pop_back();
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
}

TEST_F(HashedArrayTreeTest, TwoElements) {
    hashedArrayTree_.PushBack(1);
    hashedArrayTree_.PushBack(2);
    vector_array_.push_back(1);
    vector_array_.push_back(2);
    hashedArrayTree_.PopBack();
    vector_array_.pop_back();
    hashedArrayTree_.PopBack();
    vector_array_.pop_back();
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
}

TEST_F(HashedArrayTreeTest, ThreeElements) {
    std::vector<int> elements = {1,2,3};
    InsertElementsToBothArrays(elements);
    PopElements(2);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
}

TEST_F(HashedArrayTreeTest, FourElements) {
    std::vector<int> elements = {1,2,3,4};
    InsertElementsToBothArrays(elements);
    PopElements(3);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
}

TEST_F(HashedArrayTreeTest, FiveElements) {
    std::vector<int> elements = {1,2,3,4,5};
    InsertElementsToBothArrays(elements);
    PopElements(4);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
    PopElements(1);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
}


TEST_F(HashedArrayTreeTest, SixteenElements) {
    std::vector<int> elements = CreateElementsArray(16);
    InsertElementsToBothArrays(elements);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));

}

TEST_F(HashedArrayTreeTest, SeventeenElements) {
    std::vector<int> elements = CreateElementsArray(17);
    InsertElementsToBothArrays(elements);
    PopElements(2);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
    PopElements(14);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
}


TEST_F(HashedArrayTreeTest, OneTwentyFiveElements) {
    std::vector<int> elements = CreateElementsArray(250);
    InsertElementsToBothArrays(elements);
    PopElements(125);

    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));

}

TEST_F(HashedArrayTreeTest, TwoFiftySixElements) {
    std::vector<int> elements = CreateElementsArray(256);
    InsertElementsToBothArrays(elements);
    PopElements(200);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));

}

TEST_F(HashedArrayTreeTest, _1024Elements) {
    std::vector<int> elements = CreateElementsArray(1024);
    InsertElementsToBothArrays(elements);
    PopElements(1000);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
    InsertElementsToBothArrays(elements);
    PopElements(50);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));

}

TEST_F(HashedArrayTreeTest, _1025Elements) {
    std::vector<int> elements = CreateElementsArray(1025);
    InsertElementsToBothArrays(elements);
    PopElements(3);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
    PopElements(1000);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
}

TEST_F(HashedArrayTreeTest, _4096Elements) {
    std::vector<int> elements = CreateElementsArray(4096);
    InsertElementsToBothArrays(elements);
    PopElements(4000);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));

}

TEST_F(HashedArrayTreeTest, _4097Elements) {
    std::vector<int> elements = CreateElementsArray(4097);
    InsertElementsToBothArrays(elements);
    PopElements(4070);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));

}

TEST_F(HashedArrayTreeTest, _33123Elements) {
    std::vector<int> elements = CreateElementsArray(33123);
    InsertElementsToBothArrays(elements);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
    PopElements(33120);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));

}


TEST_F(HashedArrayTreeTest, TwoFiftySeven) {
    std::vector<int> elements = CreateElementsArray(257);
    InsertElementsToBothArrays(elements);
    PopElements(250);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));

}

TEST_F(HashedArrayTreeTest, _3_Push_Two_Pop_One_Push) {
    std::vector<int> elements = CreateElementsArray(3);
    InsertElementsToBothArrays(elements);
    PopElements(2);
    elements = CreateElementsArray(1);
    InsertElementsToBothArrays(elements);

    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));

}

TEST_F(HashedArrayTreeTest, _257PushBack_100_Pop_Back_500_PushBack_400_PopBack) {
    std::vector<int> elements = CreateElementsArray(257);
    InsertElementsToBothArrays(elements);
    PopElements(100);
    elements = CreateElementsArray(500);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
    InsertElementsToBothArrays(elements);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));
    PopElements(400);
    EXPECT_TRUE(CompareArrays(hashedArrayTree_, vector_array_));

}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}