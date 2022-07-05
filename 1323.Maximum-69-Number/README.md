#### [1323. Maximum 69 Number](https://leetcode.cn/problems/maximum-69-number/)

You are given a positive integer `num` consisting only of digits `6` and `9`.

Return *the maximum number you can get by changing **at most** one digit (*`6` *becomes* `9`*, and* `9` *becomes* `6`*)*.

 

**Example 1:**

```
Input: num = 9669
Output: 9969
Explanation: 
Changing the first digit results in 6669.
Changing the second digit results in 9969.
Changing the third digit results in 9699.
Changing the fourth digit results in 9666.
The maximum number is 9969.
```

**Example 2:**

```
Input: num = 9996
Output: 9999
Explanation: Changing the last digit 6 to 9 results in the maximum number.
```

**Example 3:**

```
Input: num = 9999
Output: 9999
Explanation: It is better not to apply any change.
```

 

**Constraints:**

- `1 <= num <= 104`
- `num` consists of only `6` and `9` digits.



给你一个仅由数字 6 和 9 组成的正整数 `num`。

你最多只能翻转一位数字，将 6 变成 9，或者把 9 变成 6 。

请返回你可以得到的最大数字



### Solution 1:  Simulation

水题，签个到

````c++
class Solution {
public:
    int maximum69Number (int num) {
        vector<int> arr;
        while (num) {
            arr.push_back(num % 10);
            num /= 10;
        }
        reverse(arr.begin(), arr.end());
        
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == 6) {
                arr[i] = 9;
                break;
            }
        }
        
        int ans = 0;
        for (size_t i = 0; i < arr.size(); ++i) {
            ans = ans * 10 + arr[i];
        }
        
        return ans;
    }
};
````

