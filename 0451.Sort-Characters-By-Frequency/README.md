# [451. Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/)

## 题目

Given a string `s`, sort it in **decreasing order** based on the **frequency** of the characters. The **frequency** of a character is the number of times it appears in the string.

Return *the sorted string*. If there are multiple answers, return *any of them*.

 

**Example 1:**

```
Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
```

**Example 2:**

```
Input: s = "cccaaa"
Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times, so both "cccaaa" and "aaaccc" are valid answers.
Note that "cacaca" is incorrect, as the same characters must be together.
```

**Example 3:**

```
Input: s = "Aabb"
Output: "bbAa"
Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
```

 

**Constraints:**

- `1 <= s.length <= 5 * 105`
- `s` consists of uppercase and lowercase English letters and digits.

## 题目大意

给定一个字符串 s，按照字母出现的频率对其进行降序排序，字母的频率是只它在字符串中出现的次数，

然会排序后的字符串，如果有多个答案，返回一个即可

字符串中包含 大写字母、小写字母和数字

## 解题思路

传闻这道题时Google 的面试题

### 解法1

利用map 来作字频统计，然后构建一个大顶堆来按序输出堆顶元素

* 这里注意一点，`pair<const int, int>`为元素是，优先级队列和 map 都需要自己提供排序函数
* 另外 `pair<const int, int>` 是不能复制的

`````c++
class Solution {
public:
    // 如果字频不同，按照字频倒序
    // 如果字频相同，按照字典序升序
    struct cmp {
        bool operator()(const pair<const char, int>& a,
                     const pair<const char, int>& b) {
            if (a.second != b.second) {
                return a.second < b.second;
            }
            return a.second < b.second;
        }
    };
    
    string frequencySort(string str) {
        unordered_map<char, int> freq;
        for (char c : str) {
            freq[c]++;
        }
        
        // 这里构建一个大顶堆，
        // 注意对于 T = pair 类型，必须要自己提供比较函数
        priority_queue<pair<char, int>, vector<pair<char, int>>, cmp> heap;
        
        for (auto it = freq.begin(); it != freq.end(); it++) {
            // 注意这里必须重新构造一个 pair<char, int>类型的数据
            // pair<const char, int> 是不可拷贝的，
            heap.push(make_pair(it->first, it->second));
        }
        
        string res = "";
        while (!heap.empty()) {
            pair<char, int> item = heap.top();
            heap.pop();
            
            for (int i = 0; i < item.second; i++) {
                res += item.first;
            }
        }
        return res;
    }
};
`````

### 解法2

这里也可以不用堆，因为所有的数字和大小写字母加起来时有限的，所有可以用一个数组来代替，不过这里对数组进行排序时，需要提供自己的排序函数

````
````

### 解法3

这种解法省内存但是时间复杂度不低

`````c++
class Solution {
public:
    string frequencySort(string str) {
        unordered_map<char, int> freq;
        for (char c : str) {
            freq[c]++;
        }
        
        // 这里注意 lambda 必须使用引用捕获
        sort(str.begin(), str.end(), [&](const char a, const char b) -> bool {
            return freq[a] != freq[b] ? freq[a] > freq[b] : a < b;
        });
        
        return str;
    }
};
`````

