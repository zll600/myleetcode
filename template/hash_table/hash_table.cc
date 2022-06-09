#include "hash_object.h"
#include "hash_table.h"

#include <cassert>

namespace walk {

HashTable::HashTable(size_t size) : size_(size) {
    data_ = new HashObject[size];
    assert(data_ != nullptr);

    for (size_t i = 0; i < size_; ++i) {
        data_[i].set_key(HashObject::GetNullKey());
    }
}

HashTable::~HashTable() {
    delete [] data_;
}

int HashTable::Hash(const std::string& key) const {
    int hash_value = 0;

    int key_len = key.size();
    for (int i = 0; i < key_len; ++i) {
        hash_value = hash_value * 31 + key[i];
    }
    return hash_value % size_;
}

void HashTable::Add(HashObject *object) {
    int index = Hash(object->get_key());
    int original_index = index;
    int dummy_index = -1;

    bool found = false;
    while (data_[index].get_key() != HashObject::GetNullKey()) {
        if (data_[index].get_key() == object->get_key()) {
            found = true;
            break;
        } else if (data_[index].get_key() == HashObject::GetDummyKey()) {
            dummy_index = index;
        }
        index = (index + 1) % size_;
        if (index == original_index) {
            return;
        }
    }

    if (!found && dummy_index != -1) {
        index = dummy_index;
    }

    data_[index].set_key(object->get_key());
    data_[index].set_value(object->get_value());
}

bool HashTable::Exists(const std::string& key) const {
    int index = Hash(key);
    int original_index = index;
    bool found = false;

    while (data_[index].get_key() != HashObject::GetNullKey()) {
        if (data_[index].get_key() == key) {
            found = true;
            break;
        }
        index = (index + 1) % size_;
        if (index == original_index) {
            break;
        }
    }
    return found;
}

}   //  namespace walk
