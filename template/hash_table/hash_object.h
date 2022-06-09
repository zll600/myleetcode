#ifndef __HASHOBJECT_H__
#define __HASHOBJECT_H__

#include <string>

namespace walk {

class HashObject {
 public:
    HashObject() =default;
    ~HashObject() =default;
    HashObject(const HashObject&) =default;
    HashObject& operator=(const HashObject&) =default;

    std::string get_key() const { return key_; }
    void set_key(const std::string& key) { key_ = key; }

    std::string get_value() const { return value_; }
    void set_value(const std::string& value) { value_ = value; }

    void SetAsDummy() {
        key_ = GetDummyKey();
        value_ = "";
    }

    static std::string GetDummyKey() { return "<Dummy>"; }
    static std::string GetNullKey() { return "<Null>"; }
 private:
    std::string key_;
    std::string value_;
};
    
}   // namespace walk

#endif // __HASHOBJECT_H__
