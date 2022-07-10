#include "myvector_test.h"

#include <cassert>
#include <iostream>

namespace walk {

void MyVectorTest::RunTests() const {
    TestSize();
    TestIsEmpty();
    TestCapacity();
    TestGetValueAt();
    TestPop();
    TestInsert();
    TestPrepend();
    TestDelete();
    TestRemove();
    TestFind();
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
    MyVector tester{3};
    tester.PushBack(3);

    assert(tester.Back() == 3);
    tester.PushBack(8);
    tester.PushBack(9);
    assert(tester.get_size() == 3);

    tester.PopBack();
    tester.PopBack();
    assert(tester.get_size() == 1);
}

void MyVectorTest::TestInsert() const {
    MyVector tester{3};
    tester.PushBack(1);
    tester.PushBack(2);
    assert(tester.get_size() == 2);

    tester.Insert(0, 3);
    assert(tester[0] == 3);
}

void MyVectorTest::TestPrepend() const {
    MyVector tester{3};
    tester.PushBack(1);
    tester.PushBack(2);

    tester.Prepend(3);
    assert(tester[0] == 3);
}

void MyVectorTest::TestDelete() const {
    MyVector tester{4};
    tester.PushBack(1);
    tester.PushBack(2);
    tester.PushBack(3);
    tester.Delete(0);
    assert(tester[0] == 2);
}

void MyVectorTest::TestRemove() const {
    MyVector tester{4};
    tester.PushBack(1);
    tester.PushBack(2);
    tester.PushBack(3);
    tester.Remove(2); 

    assert(tester[1] == 3);
}
void MyVectorTest::TestFind() const {
    MyVector tester{4};
    tester.PushBack(1);
    tester.PushBack(2);
    tester.PushBack(3);

    assert(tester.Find(2) == 1);
}

}   // namespace walk
