#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <cstdint>

#include <string>

namespace walk {

class HashObject;

class HashTable {
 public:
    explicit HashTable(size_t size);
    ~HashTable();
    HashTable(const HashTable&) =delete;
    HashTable& operator=(const HashTable&) =delete;

    // add if key is not exist
    // update if key is exist
    void Add(HashObject *object);
    bool Exists(const std::string& key) const;
    void Remove(const std::string& key);
    std::string Get(const std::string& key) const;
    
    void DebugStr() const;

 private:
    size_t size_;
    HashObject *data_;

    // hash function
    int Hash(const std::string& key) const;
};

}   // namespace walk

#endif // __HASHTABLE_H__
