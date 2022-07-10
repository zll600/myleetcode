#include "myvector.h"

#include <cstdlib>
#include <cstdio>

#include <iostream>

namespace walk {

static const size_t kMinCapacity = 16;
static const size_t kGrowthFactor = 2;
static const size_t kShrinkFactor = 4;

size_t MyVector::DeterminCapacity(size_t capacity) {
    size_t true_capacity = kMinCapacity;
    
    while (capacity > true_capacity / kGrowthFactor) {
        true_capacity *= kGrowthFactor;
    }

    capacity_ = true_capacity;
    return true_capacity;
}

void MyVector::ResizeForSize(size_t candidate_size) {
    if (size_ < candidate_size) {
        if (size_ == capacity_) {
            IncreaseSize();
        }
    } else if (size_ > candidate_size) {
        if (size_ < capacity_ / kShrinkFactor) {
            DecreaseSize();
        }
    }
}

void MyVector::IncreaseSize() {
    size_t old_capacity = capacity_;
    size_t new_capacity = DeterminCapacity(old_capacity);

    if (old_capacity != new_capacity) {
        std::unique_ptr<int[]> new_data(new int[new_capacity]);

        for (int i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }
}

void MyVector::DecreaseSize() {
    size_t old_capacity = capacity_;
    size_t new_capacity = old_capacity / 2;

    if (new_capacity < kMinCapacity) {
        new_capacity = kMinCapacity;
    }

    if (new_capacity != old_capacity) {
        std::unique_ptr<int[]> new_data(new int[new_capacity]);

        for (int i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }

        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }
}

MyVector::MyVector(size_t capacity) : capacity_(capacity), size_(0) {
    if (capacity < 1) {
        std::cout << "Cannot make vector of that size" << std::endl;
        exit(EXIT_FAILURE);
    }

    int true_capacity = DeterminCapacity(capacity);
    data_ = std::unique_ptr<int[]>(new int[true_capacity]);
}

MyVector::~MyVector() {
}

void MyVector::PushBack(int value) {
    ResizeForSize(size_ + 1);

    data_[size_] = value;
    ++size_;
}

int MyVector::Back() const {
    if (size_ == 0) {
        std::cout << "the vector is empty" << std::endl;
        exit(EXIT_FAILURE);
    }

    return data_[size_ - 1];
}

void MyVector::PopBack() {
    if (size_ == 0) {
        std::cout << "the vector is empty" << std::endl;
        exit(EXIT_FAILURE);
    }

    ResizeForSize(size_ - 1);

    --size_;
}

void MyVector::Prepend(int value) {
    Insert(0, value);
}

void MyVector::Insert(int index, int value) {
    if(index < 0 || index >= size_) {
        std::cout << "index out of bound" << std::endl;
        exit(EXIT_FAILURE);
    }

    ResizeForSize(size_ + 1);

    for (int i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }
    data_[index] = value;

    ++size_;
}

void MyVector::Delete(int index) {
    if (index < 0 || index >= size_) {
        std::cout << "in dex out of bound" << std::endl;
        exit(EXIT_FAILURE);
    }

    ResizeForSize(size_ - 1);

    for (int i = index; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }

    --size_;
}

void MyVector::Remove(int value) {
    for (int i = 0; i < size_; ++i) {
        if (value == data_[i]) {
            Delete(i);
            // 删除时会做左移操作
            --i;
        }
    }
}

int MyVector::Find(int value) const {
    int found_index = -1;

    for (int i = 0; i < size_; ++i) {
        if (data_[i] == value) {
            found_index = i;
            break;
        }
    }

    return found_index;
}

int MyVector::operator[](int index) const {
    if (index < 0 || index >= size_) {
        std::cout << "Index out of bound" << std::endl;
        exit(EXIT_FAILURE);
    }

    return data_[index];
}

void MyVector::DebugStr() const {
    std::cout << "size: " << size_
        << "capacity: " << capacity_
        << "items: " << std::endl;

    for (int i = 0; i < size_; ++i) {
        printf("%d: %d\n", i, data_[i]);
    }
}

}   // namespace walk
