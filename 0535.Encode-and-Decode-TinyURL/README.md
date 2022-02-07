# [535. Encode and Decode TinyURL](https://leetcode.com/problems/encode-and-decode-tinyurl/)

## 题目

> Note: This is a companion problem to the [System Design](https://leetcode.com/discuss/interview-question/system-design/) problem: [Design TinyURL](https://leetcode.com/discuss/interview-question/124658/Design-a-URL-Shortener-(-TinyURL-)-System/).

TinyURL is a URL shortening service where you enter a URL such as `https://leetcode.com/problems/design-tinyurl` and it returns a short URL such as `http://tinyurl.com/4e9iAk`. Design a class to encode a URL and decode a tiny URL.

There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.

Implement the `Solution` class:

- `Solution()` Initializes the object of the system.
- `String encode(String longUrl)` Returns a tiny URL for the given `longUrl`.
- `String decode(String shortUrl)` Returns the original long URL for the given `shortUrl`. It is guaranteed that the given `shortUrl` was encoded by the same object.

 

**Example 1:**

```
Input: url = "https://leetcode.com/problems/design-tinyurl"
Output: "https://leetcode.com/problems/design-tinyurl"

Explanation:
Solution obj = new Solution();
string tiny = obj.encode(url); // returns the encoded tiny url.
string ans = obj.decode(tiny); // returns the original url after deconding it.
```

 

**Constraints:**

- `1 <= url.length <= 104`
- `url` is guranteed to be a valid URL.

## 题目大意

TinyURL是一种URL简化服务， 比如：当你输入一个URL https://leetcode.com/problems/design-tinyurl 时，它将返回一个简化的URL http://tinyurl.com/4e9iAk.

要求：设计一个 TinyURL 的加密 encode 和解密 decode 的方法。你的加密和解密算法如何设计和运作是没有限制的，你只需要保证一个URL可以被加密成一个TinyURL，并且这个TinyURL可以用解密方法恢复成原本的URL。

实现 `Solution` 类

- `Solution()` 初始化对象
- `String encode(String longUrl)` 返回一个给定的 `longUrl` 的 `tiny URl `
- `String decode(String shortUrl)` 返回给定的 `shortUrl` 对应的 `longUrl` ，

## 解题思路

这道题目要想 ac 不难，但是想要做好的话，就要用到一些字符串哈希的知识了，

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/encode-and-decode-tinyurl/solution/c-zi-fu-chuan-zhuan-huan-wei-njin-zhi-shu-jin-xing/)

这里的重点是将字符串散列之后，然后得出一个随机的较短的字符串，这里涉及的具体的散列的算法我也不太懂、

````c++
class Solution {
public:
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string short_url = HashToString(Hash(longUrl));
        relat_[short_url] = longUrl;
        return short_url;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return relat_[shortUrl];
    }

 private:
    const unsigned long long kbase_ = 11;
    const string kcode_ = "0123456789zbcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int klen_ = 62;
    unordered_map<string, string> relat_;
    
    // 对字符串做一个散列
    unsigned long long Hash(const string& str) {
        unsigned long long hash = 0;
        for (char c : str) {
            hash *= kbase_;
            hash += c;
        }
        return hash;
    }
    
    // 从哈希值映射到对应的字符串中
    string HashToString(unsigned long long hash) {
        string res = "";
        while (hash) {
            res += kcode_[hash % klen_];
            hash /= klen_;
        }
        return res;
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
````
