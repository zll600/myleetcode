# [284. Peeking Iterator](https://leetcode.com/problems/peeking-iterator/)

## 题目

Design an iterator that supports the `peek` operation on an existing iterator in addition to the `hasNext` and the `next` operations.

Implement the `PeekingIterator` class:

- `PeekingIterator(Iterator<int> nums)` Initializes the object with the given integer iterator `iterator`.
- `int next()` Returns the next element in the array and moves the pointer to the next element.
- `boolean hasNext()` Returns `true` if there are still elements in the array.
- `int peek()` Returns the next element in the array **without** moving the pointer.

**Note:** Each language may have a different implementation of the constructor and `Iterator`, but they all support the `int next()` and `boolean hasNext()` functions.

 

**Example 1:**

```
Input
["PeekingIterator", "next", "peek", "next", "next", "hasNext"]
[[[1, 2, 3]], [], [], [], [], []]
Output
[null, 1, 2, 2, 3, false]

Explanation
PeekingIterator peekingIterator = new PeekingIterator([1, 2, 3]); // [1,2,3]
peekingIterator.next();    // return 1, the pointer moves to the next element [1,2,3].
peekingIterator.peek();    // return 2, the pointer does not move [1,2,3].
peekingIterator.next();    // return 2, the pointer moves to the next element [1,2,3]
peekingIterator.next();    // return 3, the pointer moves to the next element [1,2,3]
peekingIterator.hasNext(); // return False
```

 

**Constraints:**

- `1 <= nums.length <= 1000`
- `1 <= nums[i] <= 1000`
- All the calls to `next` and `peek` are valid.
- At most `1000` calls will be made to `next`, `hasNext`, and `peek`.

 

**Follow up:** How would you extend your design to be generic and work with all types, not just integer?

## 题目大意

实现一个迭代器，除了支持现有的 `hasNext`和 `next`操作，还支持额外的 peek 操作，

实现这样一个类：

* `PeekingIterator(Iterator<int> nums)`用给定的整数迭代器 `iterator`初始化这个对象，
* `int next()`返回数组中的下一个元素，并将指针指向下一个元素，
* `boolean hasNext()` 返回数组中 是否还有元素，
* `int peek()` 仅返回下一元素，但是不移动指针，

## 解题思路

这道题总的来说并不难，但却是挺经典的，可以参考这篇题解：https://leetcode.com/problems/peeking-iterator/discuss/1569292/C%2B%2B

### Solution 1:

具体的解法是：

* PeekingIterator 类中保存下一个值，和一个是否存在的标志

* `PeekingIterator(Iterator<int> nums)`初始化Iterator，设置 cur_（这里设置为 next_可能意思更明了）,和 exist_
* 后面的逻辑可以参考注释

````c++
/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *  public:
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
	    exist_ = Iterator::hasNext(); 
        if (exist_) {
            // 如果存在下一个元素，保存下来
            cur_ = Iterator::next();
        }
        
	}
	
    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        // 返回下一个元素，淡水不移动指针
        return cur_;
	}
	
	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
	    int tmp = cur_; // 保存下一个元素
        // 将指针移动道下一个元素处
        exist_ = Iterator::hasNext();
        if (exist_) {
            cur_ = Iterator::next();
        }
        return tmp; // 返回下一个元素
	}
	
	bool hasNext() const {
        // 是否存在下一个元素
	    return exist_;
	}
    
 private:
    int cur_; // 下一个元素
    bool exist_; // 下一个元素是否存在
};
````

