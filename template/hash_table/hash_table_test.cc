#include "hash_object.h"
#include "hash_table.h"
#include "hash_table_test.h"

#include <cassert>


namespace walk {

void HashTableTest::RunAllTests() {
    TestAddExists();
    TestRemove();
    TestGet();
}

void HashTableTest::TestAddExists() {
    HashTable tester(100);
    HashObject ho{};
    ho.set_key("wang");
    ho.set_value("yunchi");

    tester.Add(&ho);

    assert(tester.Exists("wang"));
}

void HashTableTest::TestRemove() {
    HashObject ho;
    ho.set_key("wang");
    ho.set_value("yunchi");

    HashTable tester{3};
    tester.Add(&ho);
    assert(tester.Exists("wang"));

    tester.Remove("wang");
    assert(!tester.Exists("wang"));
}

void HashTableTest::TestGet() {
    HashObject ho;
    ho.set_key("wang");
    ho.set_value("yunchi");

    HashTable tester{3};
    tester.Add(&ho);
    assert(tester.Exists("wang"));
    assert(tester.Get("wang") == "yunchi");
}

}   // namespace walk
