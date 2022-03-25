# [989. Add to Array-Form of Integer](https://leetcode.com/problems/add-to-array-form-of-integer/)

## 题目

The **array-form** of an integer `num` is an array representing its digits in left to right order.

- For example, for `num = 1321`, the array form is `[1,3,2,1]`.

Given `num`, the **array-form** of an integer, and an integer `k`, return *the **array-form** of the integer* `num + k`.

 

**Example 1:**

```
Input: num = [1,2,0,0], k = 34
Output: [1,2,3,4]
Explanation: 1200 + 34 = 1234
```

**Example 2:**

```
Input: num = [2,7,4], k = 181
Output: [4,5,5]
Explanation: 274 + 181 = 455
```

**Example 3:**

```
Input: num = [2,1,5], k = 806
Output: [1,0,2,1]
Explanation: 215 + 806 = 1021
```

 

**Constraints:**

- `1 <= num.length <= 104`
- `0 <= num[i] <= 9`
- `num` does not contain any leading zeros except for the zero itself.
- `1 <= k <= 104`

## 题目大意

给定一个用数组形式表示的数 `num`，按照从左到右的顺序

- 举例：`num = 1321`，其数组形式是 `[1,3,2,1]`

给定数组形式的 `num` 和一个整数 `k`，返回数组形式的 `num + k`

## 解题思路


### Solution 1: 将数组转化为数字

这种解法的问题在于，这道题目的数字可能很大，所以如果先转化为数字再进行计算，可能会发生溢出

```c++
class Solution {
public:
    vector<int> addToArrayForm(vector<int>& num, int k) {
        long long res = ArrToNum(num);
        return NumToArr(res + k);
    }
    
 private:
    long long ArrToNum(const vector<int>& nums) {
        long res = 0;
        
        const int len = nums.size();
        for (int i = 0; i < len; ++i) {
            res = res * 10 + nums[i];
        }
        
        return res;
    }
    
    vector<int> NumToArr(long long num) {
        vector<int> res;
        
        while (num) {
            res.push_back(num % 10);
            num /= 10;
        }
        reverse(res.begin(), res.end());
        
        return res;
    }
};
````
### Solution 2: 将数字转化为数组

````c++
class Solution {
public:
    vector<int> addToArrayForm(vector<int>& num, int k) {
        vector<int> add = NumToArr(k);
        vector<int> res;

        const int len1 = num.size();
        const int len2 = add.size();
        int idx1 = len1 - 1, idx2 = len2 - 1;
        int carry = 0;
        while (idx1 >= 0 || idx2 >= 0 || carry != 0) {
            int num1 = idx1 >= 0 ? num[idx1] : 0;
            int num2 = idx2 >= 0 ? add[idx2] : 0;

            int sum = num1 + num2 + carry;
            carry = sum / 10;
            sum %= 10;
            // cout << num1 << " --- " << num2 << " --- " << sum << endl;
            res.push_back(sum);

            --idx1;
            --idx2;
        }
        reverse(res.begin(), res.end());

        return res;
    }

 private:
    vector<int> NumToArr(long long num) {
        vector<int> res;

        while (num) {
            res.push_back(num % 10);
            num /= 10;
        }
        reverse(res.begin(), res.end());

        return res;
    }
};
````
