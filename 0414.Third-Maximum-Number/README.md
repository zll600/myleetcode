# [414. Third Maximum Number](https://leetcode.com/problems/third-maximum-number/)

## 题目

Given an integer array `nums`, return *the **third distinct maximum** number in this array. If the third maximum does not exist, return the **maximum** number*.

 

**Example 1:**

```
Input: nums = [3,2,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2.
The third distinct maximum is 1.
```

**Example 2:**

```
Input: nums = [1,2]
Output: 2
Explanation:
The first distinct maximum is 2.
The second distinct maximum is 1.
The third distinct maximum does not exist, so the maximum (2) is returned instead.
```

**Example 3:**

```
Input: nums = [2,2,3,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2 (both 2's are counted together since they have the same value).
The third distinct maximum is 1.
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `-231 <= nums[i] <= 231 - 1`

 

**Follow up:** Can you find an `O(n)` solution?

## 题目大意

给定一个整数数组，返回第三个最大的数，如果不存在第三大的数，返回最大的数

进阶要求：使用O(n) 的算法来解决问题

## 解题思路

### 解法1（使用有限变量）

这种解法，利用 3 个变量，在遍历的过程中维护前三个最大的数，遍历结束后，如果第三大的数不是 哨兵值，就直接返回第三大的数，否则，可以认为数组中不存在第三大的数，则返回最大的数

`````go
func thirdMax(nums []int) int {
    a, b, c := math.MinInt64, math.MinInt64, math.MinInt64
	for _, v := range nums {
		if v > a {
			c = b
			b = a
			a = v
		} else if v < a && v > b {
			c = b
			b = v
		} else if v < b && v > c {
			c = v
		}
	}
	if c == math.MinInt64 {
		return a
	}
	return c
}
`````

### 解法2

使用 set 去重，大顶堆来取出第三大的值，

不过这里有一个坑，去重之后，如果不足 3 个元素，直接返回最后一个，这里也利用了 set 的排序容器的特点

```c++
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        set<int> hash;
        for (int num : nums) {
            hash.insert(num);
        }
        
        if (hash.size() < 3) {
            return *hash.crbegin();
        }

        priority_queue<int> heap;
        for (int num : hash) {
            heap.push(num);
        }
        
        heap.pop();
        heap.pop();
        
        return heap.top();
    }
};
```

### 解法3

使用 unordered_set 代替上面的 set ，将返回的任务放到大顶堆中

````c++
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        unordered_set<int> hash;
        for (int num : nums) {
            hash.insert(num);
        }

        priority_queue<int> heap;
        for (int num : hash) {
            heap.push(num);
        }
        
        // 如果去重之后不足三个，则直接返回堆顶
        if (heap.size() < 3) {
            return heap.top();
        }
        
        heap.pop();
        heap.pop();
        
        return heap.top();
    }
};
````

