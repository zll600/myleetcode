#include "hash_object.h"
#include "hash_table.h"
#include "hash_table_test.h"

#include <cassert>


namespace walk {

void HashTableTest::RunAllTests() {
    TestAddExists();
    TestRemove();
    TestGet();
    TestProbing();
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

void HashTableTest::TestProbing() {
    HashTable states(8);

    HashObject tx;
    tx.set_key("Texas");
    tx.set_value("Austin");

    HashObject ca;
    ca.set_key("California");
    ca.set_value("Sacramento");

    HashObject nm;
    nm.set_key("New Mexico");
    nm.set_value("Santa Fe");

    HashObject fl;
    fl.set_key("Florida");
    fl.set_value("Tallahassee");

    HashObject oregon;
    oregon.set_key("Oregon");
    oregon.set_value("Salem");

    HashObject wa;
    wa.set_key("Washington");
    wa.set_value("Olympia");

    HashObject ut;
    ut.set_key("Utah");
    ut.set_value("Salt Lake City");

    HashObject ny;
    ny.set_key("New York");
    ny.set_value("Albany");

    HashObject mn;
    mn.set_key("Minnesota");
    mn.set_value("St. Paul");

    states.Add(&tx);  // 1
    states.Add(&ca);  // 0
    states.Add(&nm);  //
    states.Add(&fl);
    states.Add(&oregon);
    states.Add(&wa);
    states.Add(&ut);
    states.Add(&ny);
    states.Add(&mn);
}

}   // namespace walk
