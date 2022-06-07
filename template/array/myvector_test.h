#ifndef __MYVECTORTEST_H__
#define __MYVECTORTEST_H__

#include "myvector.h"

namespace walk {

class MyVectorTest {
 public:
    void RunTests() const;
    void TestSize() const;
    // Tests increases and decreases in capacity based on number of items stored.
    void TestCapacity() const;
    void TestIsEmpty() const;
    void TestGetValueAt() const;
    void TestPop() const;
    void TestInsert() const;
    void TestPrepend() const;
    void TestDelete() const;
    void TestRemove() const;
    void TestFind() const;
};

}   // namespace walk


#endif // __MYVECTORTEST_H__
