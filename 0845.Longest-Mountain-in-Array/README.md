# [845. Longest Mountain in Array](https://leetcode.com/problems/longest-mountain-in-array/)

## 题目

Let's call any (contiguous) subarray B (of A) a mountain if the following properties hold:  

- B.length >= 3
- There exists some 0 < i < B.length - 1 such that B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ... > B[B.length - 1]
  (Note that B could be any subarray of A, including the entire array A.)

Given an array A of integers, return the length of the longest mountain. 

Return 0 if there is no mountain.




Example 1:

```c
Input: [2,1,4,7,3,2,5]
Output: 5
Explanation: The largest mountain is [1,4,7,3,2] which has length 5.
```

Example 2:

```c
Input: [2,2,2]
Output: 0
Explanation: There is no mountain.
```

Note:

- 0 <= A.length <= 10000
- 0 <= A[i] <= 10000


Follow up:

- Can you solve it using only one pass?
- Can you solve it in O(1) space?

## 题目大意

给定一个整数数组`A`，找到数组中最长的“山”的**子数组**

满足是“山”的子数组的要求：

* 数组长度大于等于3
* 数组的值先严格递增，在严格递减，必须既有增也有减

## 解题思路

利用滑动窗口，不过在窗口扩大的时候需要注意**严格上升**和**严格下降**的转换

* 上升的条件：
  * 上升标志为真，
  * 元素 right + 1 > right
  * 元素 right + 1 > left (防止因为跳过元素相等的情况，而判断错误)
* 下降的条件：
  * 窗口大小不为一(即：left != right)
  * 元素 right + 1 < right

还有需要注意的一点，如例2中所示，如果出现**多个元素相等**的情况，代码必须可以跳过相等的部分，

## 代码

````c++
class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int size = arr.size();
        if (size < 3) {
            return 0;
        }
        
        int left = 0;
        int right = 0;
        int res = 0;
        bool incr = true;
        
        while (left < size) {
            if (right + 1 < size
               && ((incr && arr[left] < arr[right + 1] && arr[right] < arr[right + 1])  
                  || (left != right && arr[right + 1] < arr[right]))) {
                if (arr[right] > arr[right + 1]) {
                    incr = false;
                }
                ++right;
            } else {
                if (left != right && !incr) {
                    res = max(res, right - left + 1);
                }
                
                ++left;								// 这里开始就是为了防止出现元素相等的情况出现
                									// 左边界必须也只能一点一点右移，不能跳跃式右移
                if (left > right) {	
                    right = left;
                }
                
                if (left == right) {
                    incr = true;
                }
            }
        }
        return res;
    }
};
````





