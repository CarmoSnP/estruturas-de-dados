#include "../include/doubly_linked_list.hpp"
#include <gtest/gtest.h>

// Test fixture for setting up and tearing down the DoublyLinkedList instance
class DoublyLinkedListTest : public ::testing::Test {
  protected:
    void SetUp() override { list = new DoublyLinkedList<int>(); }

    void TearDown() override { delete list; }

    DoublyLinkedList<int> *list;
};

// Test case to check the initial size of the list
TEST_F(DoublyLinkedListTest, TestInitialSize) { EXPECT_EQ(list->size(), 0); }

// Test case to check if the list is empty initially
TEST_F(DoublyLinkedListTest, TestIsEmpty) { EXPECT_TRUE(list->empty()); }

// Test case to push back an element and check the size
TEST_F(DoublyLinkedListTest, TestPushBack) {
    list->push_back(10);
    EXPECT_EQ(list->size(), 1);
    EXPECT_FALSE(list->empty());
}

// Test case to push front an element and check the size
TEST_F(DoublyLinkedListTest, TestPushFront) {
    list->push_front(20);
    EXPECT_EQ(list->size(), 1);
    EXPECT_FALSE(list->empty());
}

// Test case to check if an element can be found
TEST_F(DoublyLinkedListTest, TestFind) {
    list->push_back(10);
    list->push_back(20);

    auto it = list->find(20);
    EXPECT_NE(it, list->end()); // Expect an iterator pointing to the 20
    EXPECT_EQ(*it, 20); // The value pointed to by the iterator should be 20
}

// Test case to check the pop_back method
TEST_F(DoublyLinkedListTest, TestPopBack) {
    list->push_back(10);
    list->push_back(20);
    list->pop_back();

    EXPECT_EQ(list->size(), 1);
    EXPECT_FALSE(list->empty());

    auto it = list->find(20);
    EXPECT_EQ(
        it, list->end()); // After pop_back, 20 should no longer be in the list
}

// Test case to check the push_front and pop_front methods together
TEST_F(DoublyLinkedListTest, TestPushFrontAndPopFront) {
    list->push_front(30);
    list->push_front(40);
    EXPECT_EQ(list->size(), 2);

    list->pop_front();
    EXPECT_EQ(list->size(), 1);
    auto it = list->find(30);
    EXPECT_NE(it, list->end());

    it = list->find(40);
    EXPECT_EQ(it, list->end());
}

// Test case to check if contains method works correctly
TEST_F(DoublyLinkedListTest, TestContains) {
    list->push_back(10);
    list->push_back(20);

    EXPECT_TRUE(list->contains(10));  // Should contain 10
    EXPECT_FALSE(list->contains(30)); // Should not contain 30
}

// Test case to check the operator[] for accessing elements
TEST_F(DoublyLinkedListTest, TestOperatorAccess) {
    list->push_back(50);
    list->push_back(60);

    EXPECT_EQ((*list)[0], 50); // Check if we can access the first element
    EXPECT_EQ((*list)[1], 60); // Check if we can access the second element
}

// Test case to check the erase method
TEST_F(DoublyLinkedListTest, TestErase) {
    list->push_back(10);
    list->push_back(20);
    list->push_back(30);

    auto it1 = list->find(10);
    auto it2 = list->find(20);

    list->erase(it1, it2 + 1);

    EXPECT_EQ(list->size(), 1); // Only one element should remain in the list
    EXPECT_FALSE(list->contains(10)); // 10 should have been erased
    EXPECT_FALSE(list->contains(20)); // 20 should have been erased
}

// Test case for the clear method
TEST_F(DoublyLinkedListTest, TestClear) {
    list->push_back(10);
    std::cout<<"push back 1:\n";
    list->push_back(20);
    std::cout<<"push back 2:\n";
    list->push_back(30);
    std::cout<<"push back 3:\n";

    list->clear();
    std::cout<<"clear:\n";

    EXPECT_EQ(list->size(), 0);
    EXPECT_TRUE(list->empty());

    std::cout<<"clear end\n";
}

// Test inserting at the front
TEST_F(DoublyLinkedListTest, TestInsertAtFront) {
    list->push_back(10);
    list->insert(list->begin(), 5); // Insert at the front

    EXPECT_EQ(list->size(), 2);
    EXPECT_EQ((*list)[0], 5);
    EXPECT_EQ((*list)[1], 10);
}

// Test inserting at the back
TEST_F(DoublyLinkedListTest, TestInsertAtBack) {
    list->push_back(10);
    list->insert(list->end(), 20); // Insert at the back

    EXPECT_EQ(list->size(), 2);
    EXPECT_EQ((*list)[1], 20);
}

// Test inserting in the middle
TEST_F(DoublyLinkedListTest, TestInsertInMiddle) {
    list->push_back(10);
    list->push_back(30);
    auto it = list->begin();
    ++it;                 // Move to second element (10, 30)
    list->insert(it, 20); // Insert 20 between 10 and 30

    EXPECT_EQ(list->size(), 3);
    EXPECT_EQ((*list)[1], 20);
}

// Test that the iterator increment and decrement works correctly
TEST_F(DoublyLinkedListTest, TestIteratorIncrementDecrement) {
    list->push_back(10);
    list->push_back(20);

    auto it = list->begin();
    EXPECT_EQ(*it, 10);
    ++it; // Increment iterator
    EXPECT_EQ(*it, 20);
    --it; // Decrement iterator
    EXPECT_EQ(*it, 10);
}

// Test that the operator[] works for invalid access
TEST_F(DoublyLinkedListTest, TestOperatorInvalidAccess) {
    list->push_back(10);
    EXPECT_THROW((*list)[1], std::out_of_range); // Out of range access
}

// Test edge case of inserting into an empty list
TEST_F(DoublyLinkedListTest, TestInsertIntoEmptyList) {
    list->insert(list->begin(), 5); // Insert at the front of an empty list
    EXPECT_EQ(list->size(), 1);
    EXPECT_EQ((*list)[0], 5);
}

// Test edge case of popping from an empty list
TEST_F(DoublyLinkedListTest, TestPopFromEmptyList) {
    EXPECT_THROW(list->pop_back(), std::out_of_range);
    EXPECT_THROW(list->pop_front(), std::out_of_range);
}

// Test edge case of erase on a list with one element
TEST_F(DoublyLinkedListTest, TestEraseSingleElement) {
    list->push_back(10);
    auto it = list->begin();
    list->erase(it, it + 1);

    EXPECT_EQ(list->size(), 0); // List should be empty now
}

// Test the iterator for `find` in an empty list (should return `end`)
TEST_F(DoublyLinkedListTest, TestFindInEmptyList) {
    auto it = list->find(10);
    EXPECT_EQ(it, list->end()); // Should be equal to end iterator
}

// Test the contains method when the list is empty
TEST_F(DoublyLinkedListTest, TestContainsEmptyList) {
    EXPECT_FALSE(
        list->contains(10)); // Should return false as the list is empty
}

// Test if iterating over the list works correctly
TEST_F(DoublyLinkedListTest, TestIteratorTraversal) {
    list->push_back(10);
    std::cout<<"entrou no push 1:\n";
    list->push_back(20);
    std::cout<<"entrou no push 2:\n";

    std::cout<<"entrou no for:\n";
    size_t index = 0;
    for (auto it = list->begin(); it != list->end(); ++it) {
        if (index == 0) {
            EXPECT_EQ(*it, 10);
        } else if (index == 1) {
            EXPECT_EQ(*it, 20);
        }
        ++index;
    }
    std::cout<<"saiu do for:\n";
}

// Test reverse iteration (decrementing iterator)
TEST_F(DoublyLinkedListTest, TestIteratorReverse) {
    list->push_back(10);
    list->push_back(20);

    auto it = list->end();
    --it;
    EXPECT_EQ(*it, 20); // Should point to the last element

    --it;
    EXPECT_EQ(*it, 10); // Should point to the first element
}

// Test adding large number of elements to check performance
TEST_F(DoublyLinkedListTest, TestLargeNumberOfElements) {
    for (int i = 0; i < 10000; ++i) {
        list->push_back(i);
    }
    EXPECT_EQ(list->size(), 10000);
    EXPECT_EQ((*list)[9999], 9999);
}

// Test iterators with negative offsets (operator + and -)
TEST_F(DoublyLinkedListTest, TestIteratorWithOffset) {
    list->push_back(10);
    list->push_back(20);

    auto it = list->begin();
    it = it + 1; // Move iterator forward by 1
    EXPECT_EQ(*it, 20);

    it = it - 1; // Move iterator backward by 1
    EXPECT_EQ(*it, 10);
}

// Test case to pop from an empty list
TEST_F(DoublyLinkedListTest, TestPopFrontFromEmptyList) {
    EXPECT_THROW(list->pop_front(),
                 std::out_of_range); // Should throw an exception
}

TEST_F(DoublyLinkedListTest, TestPopBackFromEmptyList) {
    EXPECT_THROW(list->pop_back(),
                 std::out_of_range); // Should throw an exception
}

// Test case to pop the only element in the list
TEST_F(DoublyLinkedListTest, TestPopFrontSingleElement) {
    list->push_back(10);
    list->pop_front();

    EXPECT_EQ(list->size(), 0); // The list should be empty after popping
    EXPECT_TRUE(list->empty()); // The list should be empty
}

TEST_F(DoublyLinkedListTest, TestPopBackSingleElement) {
    list->push_back(10);
    list->pop_back();

    EXPECT_EQ(list->size(), 0); // The list should be empty after popping
    EXPECT_TRUE(list->empty()); // The list should be empty
}

// Test case to erase elements from an empty list
TEST_F(DoublyLinkedListTest, TestEraseEmptyList) {
    auto it = list->begin();
    EXPECT_NO_THROW(
        list->erase(it, it));   // Erasing from an empty list should not throw
    EXPECT_EQ(list->size(), 0); // List should remain empty
}

// Test case to erase the only element in the list
TEST_F(DoublyLinkedListTest, TestEraseSingleElement2) {
    list->push_back(10);
    auto it = list->begin();
    list->erase(it, it + 1); // Erase the only element

    EXPECT_EQ(list->size(), 0); // The list should be empty
    EXPECT_TRUE(list->empty()); // The list should be empty
}

// Test case to erase the entire list
TEST_F(DoublyLinkedListTest, TestEraseEntireList) {
    list->push_back(10);
    list->push_back(20);
    auto it1 = list->begin();
    auto it2 = list->end();

    list->erase(it1, it2); // Erase all elements

    EXPECT_EQ(list->size(), 0); // List should be empty after erase
    EXPECT_TRUE(list->empty()); // The list should be empty
}

// Test case to check if pop_back correctly removes the last element
TEST_F(DoublyLinkedListTest, TestPopBackCorrectlyRemovesElement) {
    list->push_back(10);
    list->push_back(20);
    list->pop_back(); // Remove 20

    EXPECT_EQ(list->size(), 1); // List should have 1 element left
    EXPECT_EQ((*list)[0], 10);  // The remaining element should be 10
}

// Test case to check if pop_front correctly removes the first element
TEST_F(DoublyLinkedListTest, TestPopFrontCorrectlyRemovesElement) {
    list->push_back(10);
    list->push_back(20);
    list->pop_front(); // Remove 10

    EXPECT_EQ(list->size(), 1); // List should have 1 element left
    EXPECT_EQ((*list)[0], 20);  // The remaining element should be 20
}

// Test case to check size after erasing a range
TEST_F(DoublyLinkedListTest, TestEraseRange) {
    list->push_back(10);
    list->push_back(20);
    list->push_back(30);

    auto it1 = list->begin();
    auto it2 = list->begin();
    ++it2; // Move to second element (20)

    list->erase(it1, it2); // Erase 10

    EXPECT_EQ(list->size(), 2);       // List should have 2 elements left
    EXPECT_FALSE(list->contains(10)); // 10 should be erased
    EXPECT_TRUE(list->contains(20));  // 20 should remain
    EXPECT_TRUE(list->contains(30));  // 30 should remain
}

// Test case to erase when the range is empty (first == last)
TEST_F(DoublyLinkedListTest, TestEraseEmptyRange) {
    list->push_back(10);
    list->push_back(20);

    auto it = list->begin();
    list->erase(it, it); // Erase an empty range

    EXPECT_EQ(list->size(), 2); // List should remain unchanged
    EXPECT_EQ((*list)[0], 10);  // The first element should still be 10
    EXPECT_EQ((*list)[1], 20);  // The second element should still be 20
}

// Test case to erase the entire list (first == begin() and last == end())
TEST_F(DoublyLinkedListTest, TestEraseEntireList2) {
    list->push_back(10);
    list->push_back(20);
    list->push_back(30);

    auto it1 = list->begin();
    auto it2 = list->end();

    list->erase(it1, it2); // Erase the entire list

    EXPECT_EQ(list->size(), 0); // The list should be empty
    EXPECT_TRUE(list->empty()); // The list should be empty
}

// Test case to erase from the beginning to the middle of the list
TEST_F(DoublyLinkedListTest, TestEraseFromBeginToMiddle) {
    list->push_back(10);
    list->push_back(20);
    list->push_back(30);

    auto it1 = list->begin();
    auto it2 = list->begin();
    ++it2; // Move iterator to the second element (20)

    list->erase(it1, it2); // Erase the first element (10)

    EXPECT_EQ(list->size(), 2); // List should have 2 elements left
    EXPECT_EQ((*list)[0], 20);  // The first element should be 20
    EXPECT_EQ((*list)[1], 30);  // The second element should be 30
}

// Test case to erase from the middle to the end of the list
TEST_F(DoublyLinkedListTest, TestEraseFromMiddleToEnd) {
    list->push_back(10);
    list->push_back(20);
    list->push_back(30);

    auto it1 = list->begin();
    ++it1; // Move iterator to the second element (20)
    auto it2 = list->end();

    list->erase(it1, it2); // Erase from 20 to the end (30)

    EXPECT_EQ(list->size(), 1); // List should have 1 element left
    EXPECT_EQ((*list)[0], 10);  // The only remaining element should be 10
}

// Test case to erase from the middle of the list
TEST_F(DoublyLinkedListTest, TestEraseMiddleElement) {
    list->push_back(10);
    list->push_back(20);
    list->push_back(30);

    auto it1 = list->begin();
    ++it1; // Move iterator to the second element (20)
    auto it2 = it1;
    ++it2; // Move iterator to the third element (30)

    list->erase(it1, it2); // Erase the middle element (20)

    EXPECT_EQ(list->size(), 2); // List should have 2 elements left
    EXPECT_EQ((*list)[0], 10);  // The first element should be 10
    EXPECT_EQ((*list)[1], 30);  // The second element should be 30
}

// Test case to erase the last element in a list with one element
TEST_F(DoublyLinkedListTest, TestEraseLastElementSingleElement) {
    list->push_back(10);

    auto it = list->begin();
    list->erase(it, it + 1); // Erase the only element

    EXPECT_EQ(list->size(), 0); // The list should be empty
    EXPECT_TRUE(list->empty()); // The list should be empty
}

// Test case to erase a single element when the list has only one element
TEST_F(DoublyLinkedListTest, TestEraseSingleElement3) {
    list->push_back(10);

    auto it = list->begin();
    list->erase(it, it + 1); // Erase the only element

    EXPECT_EQ(list->size(), 0); // The list should be empty
    EXPECT_TRUE(list->empty()); // The list should be empty
}
