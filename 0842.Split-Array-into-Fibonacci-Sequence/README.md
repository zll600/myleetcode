# [842. Split Array into Fibonacci Sequence](https://leetcode.com/problems/split-array-into-fibonacci-sequence/)

## 题目

You are given a string of digits `num`, such as `"123456579"`. We can split it into a Fibonacci-like sequence `[123, 456, 579]`.

Formally, a **Fibonacci-like** sequence is a list `f` of non-negative integers such that:

- `0 <= f[i] < 231`, (that is, each integer fits in a **32-bit** signed integer type),
- `f.length >= 3`, and
- `f[i] + f[i + 1] == f[i + 2]` for all `0 <= i < f.length - 2`.

Note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number `0` itself.

Return any Fibonacci-like sequence split from `num`, or return `[]` if it cannot be done.


**Example 1:**

```
Input: num = "1101111"
Output: [11,0,11,11]
Explanation: The output [110, 1, 111] would also be accepted.
```

**Example 2:**

```
Input: num = "112358130"
Output: []
Explanation: The task is impossible.
```

**Example 3:**

```
Input: num = "0123"
Output: []
Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.
```

 

**Constraints:**

- `1 <= num.length <= 200`
- `num` contains only digits.

## 题目大意

给定一个数字字符串 `num`，如 `"123456579"`，我们可以将其切分为 类斐波那契数列 `[123, 456, 579]`

斐波那契式序列是一个非负整数列表 `F`，且满足：

- `0 <= F[i] <= 2^31 - 1`，（也就是说，每个整数都符合 32 位有符号整数类型）；
- `F.length >= 3`；
- 对于所有的`0 <= i < F.length - 2`，都有 `F[i] + F[i+1] = F[i+2]` 成立。

另外，请注意，将字符串拆分成小块时，每个块的数字一定不要以零开头，除非这个块是数字 0 本身。返回从 S 拆分出来的所有斐波那契式的序列块，如果不能拆分则返回 []。


## 解题思路

这道题的话大概率是要用 回溯来解决的，这里的剪枝条件要考虑好，否则可能会超时

这里的剪枝条件有：

- 不能出现前导 0，
- 分割出来的数字要能够被 int 表示，
- 如果分割出来的数字已经大于 前面两个之和，

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.com/problems/split-array-into-fibonacci-sequence/submissions/)

主要是剪枝的条件需要多思考一下，否则回溯法容易超时

````java
class Solution {
    public List<Integer> splitIntoFibonacci(String S) {
        List<Integer> res = new ArrayList<>();
        backtrack(S.toCharArray(), res, 0);
        return res;
    }

    public boolean backtrack(char[] digit, List<Integer> res, int index) {
        //边界条件判断，如果截取完了，并且res长度大于等于3，表示找到了一个组合。
        if (index == digit.length && res.size() >= 3) {
            return true;
        }
        for (int i = index; i < digit.length; i++) {
            //两位以上的数字不能以0开头
            if (digit[index] == '0' && i > index) {
                break;
            }
            //截取字符串转化为数字
            long num = subDigit(digit, index, i + 1);
            //如果截取的数字大于int的最大值，则终止截取
            if (num > Integer.MAX_VALUE) {
                break;
            }
            int size = res.size();
            //如果截取的数字大于res中前两个数字的和，说明这次截取的太大，直接终止，因为后面越截取越大
            if (size >= 2 && num > res.get(size - 1) + res.get(size - 2)) {
                break;
            }
            if (size <= 1 || num == res.get(size - 1) + res.get(size - 2)) {
                //把数字num添加到集合res中
                res.add((int) num);
                //如果找到了就直接返回
                if (backtrack(digit, res, i + 1))
                    return true;
                //如果没找到，就会走回溯这一步，然后把上一步添加到集合res中的数字给移除掉
                res.remove(res.size() - 1);
            }
        }
        return false;
    }

    //相当于截取字符串S中的子串然后转换为十进制数字
    private long subDigit(char[] digit, int start, int end) {
        long res = 0;
        for (int i = start; i < end; i++) {
            res = res * 10 + digit[i] - '0';
        }
        return res;
    }
}

````
