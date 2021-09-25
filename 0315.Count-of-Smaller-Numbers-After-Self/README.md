# [315. Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) 

## 题目

You are given an integer array `nums` and you have to return a new `counts` array. The `counts` array has the property where `counts[i]` is the number of smaller elements to the right of `nums[i]`.

 

**Example 1:**

```
Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
```

**Example 2:**

```
Input: nums = [-1]
Output: [0]
```

**Example 3:**

```
Input: nums = [-1,-1]
Output: [0,0]
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `-104 <= nums[i] <= 104`

## 题目大意

给定一个数组，你必须返回一个新的 counts 数组，这个新数组其中每一项是nums 对应位置数的有责小于该数的元素数目

## 解题思路

这道题和剑指的第 51 题比较相似，但是这里这里要求到某一个具体位置，所以还要涉及到如何定位元素，

这道题可以使用索引数组来定位元素，归并排序时合并的索引数组，而非原数组，比较的时候比较的原数组的值，

我们在求解逆序对的书目时可以在前有序数组要合并时进行记录，此时后有序数组中已经归并回去的元素必然比但钱要归并的前有序数组中的元素要小，这里就是可以加速计算，和避免重复计算的地方，

这道题目具体解析可以参考这篇题解：https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/solution/gui-bing-pai-xu-suo-yin-shu-zu-python-dai-ma-java-/

这道题目还可以利用线段树和树状数组来解决，这些留待以后实现

## 代码

```c++
class Solution1 {
public:
    // 暴力解法 TLE
    vector<int> countSmaller1(vector<int>& nums) {
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            int cnt = 0;
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] < nums[i]) {
                    cnt++;
                }
            }
            res.push_back(cnt);
        }
        
        return res;
    }
};

class Solution {
 public:
    vector<int> countSmaller(vector<int>& nums) {
        // 索引数组，归并回去的时候方便知道是那个下标中的元素，
        vector<int> index(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            index[i] = i;
        }
        vector<int> res(nums.size());
        vector<int> aux(nums.size());
        
        MergeSort(nums, index, 0, index.size() - 1, aux, res);
        
        return res;
    }
    
 private:
    
    void MergeCount(vector<int>& nums, vector<int>& index, int lo, int mid, int hi,
                   vector<int>& aux, vector<int>& res) {
        copy(index.begin() + lo, index.begin() + hi + 1, aux.begin() + lo);
        
        int i = lo;
        int j = mid + 1;
        
        for (int k = lo; k <= hi; k++) {
            if (i > mid) {
                index[k] = aux[j];
                j++;
            } else if (j > hi) {
                index[k] = aux[i];
                i++;
                
                res[index[k]] += hi - mid;
            } else if (nums[aux[i]] <= nums[aux[j]]) { // <= 保持排序的稳定性，在这道题目是必须条件
                index[k] = aux[i];
                i++;
                res[index[k]] += (j - mid - 1); // 不包括 j 和 mid   
            } else {
                index[k] = aux[j];
                j++;
            }
        }
    }
    
    void MergeSort(vector<int>& nums, vector<int>& index, int lo, int hi,
                   vector<int>& aux, vector<int>& res) {
        if (lo >= hi) { // 递归堆终止条件
            return;
        }
        
        int mid = lo + (hi - lo) / 2;
        MergeSort(nums, index, lo, mid, aux, res);
        MergeSort(nums, index, mid + 1, hi, aux, res);
        
        // 归并排序的优化，如果索引数组有序，则不存在逆序对
        if (nums[index[mid]] <= nums[index[mid + 1]]) {
            return;
        }
        
        MergeCount(nums, index, lo, mid, hi, aux, res);
    }
};
```

