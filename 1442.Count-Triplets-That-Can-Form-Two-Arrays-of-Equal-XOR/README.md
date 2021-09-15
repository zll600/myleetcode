# [1442. Count Triplets That Can Form Two Arrays of Equal XOR](https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/)

## 题目

Given an array of integers `arr`.

We want to select three indices `i`, `j` and `k` where `(0 <= i < j <= k < arr.length)`.

Let's define `a` and `b` as follows:

- `a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]`
- `b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]`

Note that **^** denotes the **bitwise-xor** operation.

Return *the number of triplets* (`i`, `j` and `k`) Where `a == b`.

 

**Example 1:**

```
Input: arr = [2,3,1,6,7]
Output: 4
Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)
```

**Example 2:**

```
Input: arr = [1,1,1,1,1]
Output: 10
```

**Example 3:**

```
Input: arr = [2,3]
Output: 0
```

**Example 4:**

```
Input: arr = [1,3,5,7,9]
Output: 3
```

**Example 5:**

```
Input: arr = [7,11,12,9,5,2,7,17,22]
Output: 8
```

 

**Constraints:**

- `1 <= arr.length <= 300`
- `1 <= arr[i] <= 10^8`

## 题目大意

给定一个数组arr，从中选取三个下标i, j, k满足（0 <= i  < j < k < arr.length），a，b 定义如下：

- `a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]`
- `b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]`

注意：^代表位异或操作，返回满足条件的三元组的数目

## 解题思路

* 这道题目可以前缀异或来做，这里注意的i，j，k三者的大小关系是 0 <= i < j <= k < arr.length,
* 这道题目还可以简化计算，利用 x ^ x = 0 ，x ^ 0 = x，的性质，题目最后要求的是 a == b，那么只要找到所有元素异或为0的区间[i, k]，`xors[i, k] = xors[k] ^ xors[i - 1] = 0`即为`xors[k] = xors[i - 1]` 即为`xors[k] ^ xors[i - 1] = 0`，求出所有的 [i, k],则k 的范围就是所有的 k - i 之和

## 代码

````c++
class Solution {
public:
    // 枚举每一个位置
    int countTriplets1(vector<int>& arr) {
        int size = arr.size();
        
        vector<int> xors(size + 1, 0);
        for (int i = 1; i <= size; ++i) {
            xors[i] = xors[i - 1] ^ arr[i - 1];
        }
        
        int res = 0;
        for (int i = 1; i <= size; ++i) {
            for (int j = i + 1; j <= size; ++j) {
                for (int k = j; k <= size; ++k) {
                    int a = xors[j - 1] ^ xors[i - 1];
                    int b = xors[k] ^ xors[j - 1];
                    if (a == b) {
                        ++res;
                    }
                }
            }
        }
        
        return res;
    }
    
    int countTriplets(vector<int>& arr) {
        int size = arr.size();
        
        vector<int> xors(size + 1, 0);
        for (int i = 1; i <= size; ++i) {
            xors[i] = xors[i - 1] ^ arr[i - 1];
        }
        
        int res = 0;
        for (int i = 1; i <= size; ++i) {
            for (int k = i + 1; k <= size; ++k) {
                /*
                int cur = xors[k];
                
                if (i > 1) {    // 前面计算xors时插入了一个0，所以这里为了不应响最后的记过，必须保证 i > 1，才可进行异或
                    cur ^= xors[i - 1];
                }
                if (cur == 0) {
                    res += k - i;
                }*/
                
                if (xors[i - 1] == xors[k]) {
                    res += k - i;
                }
            }
        }
        
        return res;
    }
};
````

