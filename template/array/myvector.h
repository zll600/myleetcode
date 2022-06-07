#ifndef __MYVECTOR_H__
#define __MYVECTOR_H__

#include <memory>

namespace walk {

class MyVector {
 public:
    MyVector(size_t capacity_);
    MyVector(const MyVector& rhs);
    MyVector& operator=(const MyVector& rhs);
    ~MyVector();

    size_t get_size() const { return size_; } 
    size_t get_capacity() const { return capacity_; }
    bool IsEmpty() const { return size_ == 0; }
    void PushBack(int value);
    int Back() const;
    void PopBack();
    void Prepend(int value);
    void Insert(int index, int value);
    void Delete(int index);
    void Remove(const int value);
    int Find(int value) const;

    int operator[](int index) const;

    void DebugStr() const;
 private:
    size_t capacity_;
    size_t size_;
    std::unique_ptr<int[]> data_;

    size_t DeterminCapacity(size_t capacity_);
    void ResizeForSize(size_t candidate_size);
    void IncreaseSize();
    void DecreaseSize();
};

}   // namespace walk

#endif // __MYVECTOR_H__
