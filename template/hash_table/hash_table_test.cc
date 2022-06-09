#include "hash_object.h"
#include "hash_table.h"
#include "hash_table_test.h"

#include <cassert>


namespace walk {

void HashTableTest::RunAllTests() {
    TestAddExists();
}

void HashTableTest::TestAddExists() {
    HashTable tester(100);
    HashObject ho{};
    ho.set_key("wang");
    ho.set_value("yunchi");

    tester.Add(&ho);

    assert(tester.Exists("wang"));
}

}   // namespace walk
