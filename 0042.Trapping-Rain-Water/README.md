# [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)

## 题目

Given `n` non-negative integers representing an elevation map where the width of each bar is `1`, compute how much water it can trap after raining.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png)

```
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
```

**Example 2:**

```
Input: height = [4,2,0,3,2,5]
Output: 9
```

 

**Constraints:**

- `n == height.length`
- `1 <= n <= 2 * 104`
- `0 <= height[i] <= 105`

## 题目大意

给定一个非负整数的数组表示一个条形图，其宽度为1，计算下雨之后，能容纳多少水

## 解题思路

这道题的解法，可以参考这篇题解：

https://leetcode-cn.com/problems/trapping-rain-water/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-w-8/

### 解法1（单调栈）

这个解法可以参考这篇题解：https://leetcode-cn.com/problems/trapping-rain-water/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-w-8/

具体做法是维护一个单调递减的单调栈，如果新元素大于栈顶元素，说明有可能可以接到雨水，所以出栈进行计算

模拟以下可以发现，这里出栈进行计算，其实是一层一层计算的，建议自己动手去模拟

如果元素为0，那就按0 算

每次计算的时候，高度是新栈顶和当前元素中最小的一个（木桶效应），宽度是 right - left - 1，计算面积，更新最大值

`````c++
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        stack<int> sta;  //  这里利用一个单调递减的单调栈
        const int size = height.size();
        
        for (int i = 0; i < size; ++i) {
            while (!sta.empty() && height[sta.top()] < height[i]) {  // 如果遇到比栈顶大的元素，则出栈计算
                int cur = sta.top();  // 当前栈顶元素
                sta.pop();
                if (sta.empty()) {  // 如果栈为空，跳出循环
                    break;
                }
                int left = sta.top();  // 新的栈顶
                int right = i;
                int h = min(height[right], height[left]) - height[cur];  // 取最小的高度，做差
                ans += (right - left - 1) * h;  // 计算面积
            }
            sta.push(i);  // 新的位置入栈
        }
        
        return ans;
    }
};
`````

### 解法2（按行算）

具体做法就是，逐层进行计算，现取得最大的层数，作为循环的终点，则层数遍历的范围就是  [1,max_val]，左右边界都是可以取到的

在每层计算时，知道大于等于当前层数的元素，表示可以开始计算了，因为是逐层计算，所以每次符合条件，至多 +1，这个可以自己手动模拟一下

`````c++
class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0;
        const auto max_val = max_element(height.begin(), height.end());  // 这里预先取得最大的元素
        
        const int size = height.size();
        for (int i = 1; i <= *max_val; ++i) {  // 从 0 开始到最高的元素，逐层计算
            bool start = false;
            int tmp_sum = 0;
            
            for (int j = 0; j < size; ++j) {
                if (start && height[j] < i) {
                    ++tmp_sum;
                }
                
                if (height[j] >= i) {  // 如果遍历到一个大于等于当前层数的高度，则可以开始进行计算
                    start = true;  // 可以开始计算
                    res += tmp_sum;  // 累加上次的结果
                    tmp_sum = 0;
                }
            }
        }
        
        return res;
    }
};
`````

### 解法3（按列算）

按列来计算，就是从 中间开始向左右两边开始扩，分别找到两侧最大的元素，选出两侧中最小的一个，如果这个最小值比当前元素大则可以存水，否则不能存水

`````c++
class Solution {
public:
    int trap(vector<int>& height) {
        int sum = 0;
        
        const int size = height.size();
        // 按列查找，从中间开始，分别向左向右扩，范围是 [1, size - 2]
        for (int i = 1; i < size - 1; ++i) {
            // 找到左边最高的位置
            auto left = max_element(height.begin(), height.begin() + i);
            // 找到右边最高的位置
            auto right = max_element(height.begin() + i + 1, height.end());
            
            int h = min(*left, *right);
            if (h > height[i]) {  // 只有当两侧最矮的列比当前列还高时，才有水
                sum += h - height[i];
            }
        }
        
        return sum;
    }
};
`````

### 解法4（动态规划）

核心思想还是按照列来算，在不过这里提前计算了每个位置的左边最大的和右边最大的，在计算这两个数组的过程中使用了动态规划，这里的状态转移方程也比较简单

`````c++
class Solution {
public:
    int trap(vector<int>& height) {
        const int size = height.size();
        // 按列查找，从中间开始，分别向左向右扩，范围是 [1, size - 2]
        vector<int> max_left(size, 0);
        vector<int> max_right(size, 0);
        
        // 在计算这两个数组的时候使用了动态规划
        // 只计算 [1, size - 2] 范围内，两侧用不到
        for (int i = 1; i < size - 1; ++i) {
            max_left[i] = max(max_left[i - 1], height[i - 1]);
        }
        for (int i = size - 2; i >= 1; --i) {
            max_right[i] = max(max_right[i + 1], height[i + 1]);
        }
        
        int sum = 0;
        for (int  i = 1; i < size - 1; ++i) {
            int min_val = min(max_left[i], max_right[i]);
            if (min_val > height[i]) {
                sum += min_val - height[i];
            }
        }
        
        return sum;
    }
};
`````

### 解法5（双指针）

这种解法从两边向中间计算，这种解法其实并不是很好理解

````c++
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) {
            return 0;
        }
        
        const int size = height.size();
        int max_left = 0;
        int max_right = 0;
        int left = 1;  // 左指针
        int right = size - 2;  // 右指针
        
        int res = 0;
        for (int i = 1; i < size - 1; ++i) {
            // 从左向右，此时最矮的列取左边
            if (height[left - 1] < height[right + 1]) { 
                max_left = max(max_left, height[left - 1]);
                int min_val = max_left;
                if (min_val > height[left]) {  // 可以计算左侧
                    res += min_val - height[left];
                }
                ++left;
            } else {
                // 从右向左，此时最矮的列，取右边
                max_right = max(max_right, height[right + 1]);
                int min_val = max_right;
                if (min_val > height[right]) {  // 可以计算右侧
                    res += min_val - height[right];
                }
                --right;
            }
        }
        return res;
    }
};
````

