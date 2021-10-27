# [306. Additive Number](https://leetcode.com/problems/additive-number/)

## 题目

Additive number is a string whose digits can form additive sequence.

A valid additive sequence should contain **at least** three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.

Given a string containing only digits `'0'-'9'`, write a function to determine if it's an additive number.

**Note:** Numbers in the additive sequence **cannot** have leading zeros, so sequence `1, 2, 03` or `1, 02, 3` is invalid.

 

**Example 1:**

```
Input: "112358"
Output: true
Explanation: The digits can form an additive sequence: 1, 1, 2, 3, 5, 8. 
             1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
```

**Example 2:**

```
Input: "199100199"
Output: true
Explanation: The additive sequence is: 1, 99, 100, 199. 
             1 + 99 = 100, 99 + 100 = 199
```

 

**Constraints:**

- `num` consists only of digits `'0'-'9'`.
- `1 <= num.length <= 35`

**Follow up:**
How would you handle overflow for very large input integers?

## 题目大意

累加数是一个字符串，组成它的数字可以形成累加序列。一个有效的累加序列必须至少包含 3 个数。除了最开始的两个数以外，字符串中的其他数都等于它之前两个数相加的和。给定一个只包含数字 ‘0’-‘9’ 的字符串，编写一个算法来判断给定输入是否是累加数。说明: 累加序列里的数不会以 0 开头，所以不会出现 1, 2, 03 或者 1, 02, 3 的情况。

**进阶要求**：如果给定一个很大的数，如何判断解决溢出问题

## 解题思路

### Solution 1:

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/additive-number/solution/29xing-dai-ma-jie-jun-chou-by-mr_mingren-gfoi/

```c++
// class Solution {
// public:
//     bool isAdditiveNumber(string num) {
//         if (num.size() < 3) {  // 如果字符串长度小于 3 直接返回错误
//             return false;
//         }
        
//         const int size = num.size();
//         // 先切分第一个数
//         for (int i = 0; i < size / 2; ++i) {
//             // 如果第一个数第一位是0，且第一个数不止一位，直接返回 false
//             if (num[0] == '0' && i > 0) {
//                 return false;
//             }
//             // 切分第二个数，
//             for (int j = i + 1; j < i + 1 + (size - i - 1) / 2; ++j) {
//                 // 如果第二个数的第一位是0，且第二个数不止一位，直接返回 false
//                 if (num[i + 1] == '0' && j > i + 1) {
//                     break;
//                 }
                
//                 long long first = stoll(num.substr(i, i + 1));
//                 long long second = stoll(num.substr(i + 1, j - i));
//                 // 递归判断其余部分
//                 if (DFS(num, j + 1, first, second)) {
//                     return true;
//                 }
//             }
//         }
        
//         return false;
//     }
    
//  private:
//     bool DFS(const string& num, int idx, long long first, long long second) {
//         if (idx == num.size()) {  // 递归终止条件
//             return true;
//         }
        
//         const int size = num.size();
//         // 切割第三个数出来
//         for (int i = idx; i < size; ++i) {
//             // 如果第一个位置为0，且切分出来的数万多于一位，直接返回错误
//             if (num[idx] == '0' && i > idx) {
//                 return false;
//             }
            
//             long long cur = stoll(num.substr(idx, i - idx + 1));
//             // 如果当前切分出来的数已经大于前面两个数之和，直接返回
//             if (cur > first + second) {
//                 return false;
//             }
//             // 如果当前数等于前两个数之和，则继续切分
//             if (cur == first + second) {
//                 // 如果递归匹配成功则直接返回
//                 if (DFS(num, i + 1, second, cur)) {
//                     return true;
//                 }
//                 // 否则结束循环
//                 break;
//             }
//         }
        
//         // 直接返回错误
//         return false;
//     }
// };

class Solution {
public:
    bool func(string& num, long long pre, long long cur, int now, int n){
        if(now == n)    return true;//说明num已经遍历完了，并且都符合要求
        for(int i=now; i<n; ++i){
            if(num[now]=='0'&&i>now)    return false;//判断是否属于0开头的数字
            long long a = stoll(num.substr(now,i-now+1));
            if(a>pre+cur)   return false; //这个表示最新的这个数字已经大于前两个之和了，后面肯定都不成立了。
            if(a==pre + cur){
                if(func(num,cur,a,i+1,n))   return true;
                break;
            }
        }
        return false;
    }
    bool isAdditiveNumber(string num) {
        int n = num.size();
        for(int i=0; i<n/2; ++i){//这个范围是因为第一个数最长也不到总长度的一半
            if(num[0]=='0' && i>0)  return false;//判断是否属于0开头的数字
            for(int j=i+1; j<i+1+(n-i-1)/2; ++j){//同i的范围
                if(num[i+1]=='0' && j>i+1)   continue;//判断是否属于0开头的数字
                long long pre = stoll(num.substr(0,i+1));
                long long cur = stoll(num.substr(i+1,j-i));
                if(func(num,pre,cur,j+1,n))    return true;
            }
        }
        return false;
    }
};
```

### Solution 2:

这种解法可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0300~0399/0306.Additive-Number/

这里暂不实现留待以后更正

````
````

