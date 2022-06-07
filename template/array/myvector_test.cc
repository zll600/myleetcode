#include "myvector_test.h"

#include <cassert>
#include <iostream>

namespace walk {

void MyVectorTest::RunTests() const {
    TestSize();
    TestIsEmpty();
    TestCapacity();
    TestGetValueAt();
}

void MyVectorTest::TestSize() const {
    walk::MyVector tester(3);
    assert(tester.get_size() == 0);

    int items_to_add = 5;
    for (int i = 0; i < items_to_add; ++i) {
        tester.PushBack(i + 1);
    }
    assert(tester.get_size() == items_to_add);
}

void MyVectorTest::TestCapacity() const {
     MyVector tester{4}; 
     assert(tester.get_capacity() == 16);

     for (size_t i = 0; i < 17; ++i) {
        tester.PushBack(i + 1);
     }
     assert(tester.get_capacity() == 16 * 2);

     for (size_t i = 0; i < 20; ++i) {
        tester.PushBack(i + 1);
     }
     assert(tester.get_capacity() == 16 * 4);

     for (size_t i = 0; i < 30; ++i) {
        tester.PopBack();
     }
    assert(tester.get_capacity() == 16 * 2);
    for (size_t i = 0; i < 7; ++i) {
        tester.PopBack();
    }
    assert(tester.get_capacity() == 16);
}

void MyVectorTest::TestIsEmpty() const {
    MyVector tester{3};

    assert(tester.IsEmpty());
}

void MyVectorTest::TestGetValueAt() const {
    MyVector tester{3};
    tester.PushBack(1);
    tester.PushBack(2);
    tester.PushBack(3);

    assert(tester[0] == 1);
    assert(tester[1] == 2);
    assert(tester[2] == 3);
}


void MyVectorTest::TestPop() const {
    
}
void MyVectorTest::TestInsert() const {}
void MyVectorTest::TestPrepend() const {}
void MyVectorTest::TestDelete() const {}
void MyVectorTest::TestRemove() const {}
void MyVectorTest::TestFind() const {}

}   // namespace walk
