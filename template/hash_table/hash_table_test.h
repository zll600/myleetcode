#ifndef __HASHTABLE_TEST_H__
#define __HASHTABLE_TEST_H__

namespace walk {

class HashTableTest {
 public:
    void RunAllTests();

    void TestAddExists();
    void TestProbing();
    void TestGet();
    void TestRemove();
};

}   // namespace walk

#endif // __HASHTABLE_TEST_H__
