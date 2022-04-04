# [591. Tag Validator](https://leetcode-cn.com/problems/tag-validator/)

Given a string representing a code snippet, implement a tag validator to parse the code and return whether it is valid.

A code snippet is valid if all the following rules hold:

1. The code must be wrapped in a **valid closed tag**. Otherwise, the code is invalid.
2. A **closed tag** (not necessarily valid) has exactly the following format : `<TAG_NAME>TAG_CONTENT</TAG_NAME>`. Among them, `<TAG_NAME>` is the start tag, and `</TAG_NAME>` is the end tag. The TAG_NAME in start and end tags should be the same. A closed tag is **valid** if and only if the TAG_NAME and TAG_CONTENT are valid.
3. A **valid** `TAG_NAME` only contain **upper-case letters**, and has length in range [1,9]. Otherwise, the `TAG_NAME` is **invalid**.
4. A **valid** `TAG_CONTENT` may contain other **valid closed tags**, **cdata** and any characters (see note1) **EXCEPT** unmatched `<`, unmatched start and end tag, and unmatched or closed tags with invalid TAG_NAME. Otherwise, the `TAG_CONTENT` is **invalid**.
5. A start tag is unmatched if no end tag exists with the same  TAG_NAME, and vice versa. However, you also need to consider the issue  of unbalanced when tags are nested.
6. A `<` is unmatched if you cannot find a subsequent `>`. And when you find a `<` or `</`, all the subsequent characters until the next `>` should be parsed as TAG_NAME (not necessarily valid).
7. The cdata has the following format : `<![CDATA[CDATA_CONTENT]]>`. The range of `CDATA_CONTENT` is defined as the characters between `<![CDATA[` and the **first subsequent** `]]>`.
8. `CDATA_CONTENT` may contain **any characters**. The function of cdata is to forbid the validator to parse `CDATA_CONTENT`, so even it has some characters that can be parsed as tag (no matter valid or invalid), you should treat it as **regular characters**.

 

**Example 1:**

```
Input: code = "<DIV>This is the first line <![CDATA[<div>]]></DIV>"
Output: true
Explanation: 
The code is wrapped in a closed tag : <DIV> and </DIV>. 
The TAG_NAME is valid, the TAG_CONTENT consists of some characters and cdata. 
Although CDATA_CONTENT has an unmatched start tag with invalid TAG_NAME, it should be considered as plain text, not parsed as a tag.
So TAG_CONTENT is valid, and then the code is valid. Thus return true.
```

**Example 2:**

```
Input: code = "<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>"
Output: true
Explanation:
We first separate the code into : start_tag|tag_content|end_tag.
start_tag -> "<DIV>"
end_tag -> "</DIV>"
tag_content could also be separated into : text1|cdata|text2.
text1 -> ">>  ![cdata[]] "
cdata -> "<![CDATA[<div>]>]]>", where the CDATA_CONTENT is "<div>]>"
text2 -> "]]>>]"
The reason why start_tag is NOT "<DIV>>>" is because of the rule 6.
The reason why cdata is NOT "<![CDATA[<div>]>]]>]]>" is because of the rule 7.
```

**Example 3:**

```
Input: code = "<A>  <B> </A>   </B>"
Output: false
Explanation: Unbalanced. If "<A>" is closed, then "<B>" must be unmatched, and vice versa.
```

 

**Constraints:**

- `1 <= code.length <= 500`
- `code` consists of English letters, digits, `'<'`, `'>'`, `'/'`, `'!'`, `'['`, `']'`, `'.'`, and `' '`.

## 题目大意

给定一个代码片段，实现一个验证器来解析这段代码，判断其是否有效，

符合下列条件的代码是有效的：

1. 代码必须被 *合法的闭合标签* 包围。否则，代码是无效的。
2. *闭合标签（不一定合法）* 要严格符合格式：`<TAG_NAME>TAG_CONTENT</TAG_NAME>`。其中，`<TAG_NAME>` 是起始标签，`</TAG_NAME>` 是结束标签。起始和结束标签中的 `TAG_NAME` 应当相同。当且仅当 `TAG_NAME` 和 `TAG_CONTENT` 都是合法的，闭合标签才是合法的。
3. 合法的 `TAG_NAME` 仅含有大写字母，长度在范围 `[1,9]` 之间。否则，该 `TAG_NAME` 是不合法的。
4. 合法的 `TAG_CONTENT` 可以包含其他合法的闭合标签，`cdata （请参考规则7）` 和 *任意字符（注意参考规则1）* 除了 不匹配的`<`、不匹配的起始和结束标签、不匹配的或带有不合法 `TAG_NAME` 的闭合标签。否则，`TAG_CONTENT` 是不合法的。
5. 一个起始标签，如果没有具有相同 `TAG_NAME` 的结束标签与之匹配，是不合法的。反之亦然。不过，你也需要考虑标签嵌套的问题。
6. 一个 `<` ，如果你找不到一个后续的 `>` 与之匹配，是不合法的。并且当你找到一个 `<` 或 `</` 时，所有直到下一个`>` 的前的字符，都应当被解析为 `TAG_NAME（不一定合法）`。
7. `cdata` 有如下格式：`<![CDATA[CDATA_CONTENT]]>` 。`CDATA_CONTENT` 的范围被定义成 `<![CDATA[ 和后续的第一个 ]]>` 之间的字符。
`CDATA_CONTENT` 可以包含任意字符。`cdata` 的功能是阻止验证器解析 `CDATA_CONTENT` ，所以即使其中有一些字符可以被解析为标签（无论合法还是不合法），也应该将它们视为常规字符

## 解题思路

这道题目中有字符串匹配的问题，这里可以考虑使用栈来模拟,


### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/tag-validator/solution/jie-yong-you-xian-zhuang-tai-ji-de-si-xi-lsx8/)

这里借用有限状态机的思想，将解析字符串分为几种不同的状态，设置好每种状态下需要做的事情，和当前状态在什么条件下应该转移到哪种状态下

````c++
class Solution {
public:
    Solution() : cur_state_(ProgramState::A) {}

    bool isValid(string code) {
        // 这个栈用来匹配标签
        stack<string> tags;
        // 解析标签
        string tag;

        const int len = code.size();
        int i = 0;
        while (i < code.size()) {
            switch (cur_state_) {
                case ProgramState::A:
                    if (code[i]  == '<') {
                        // 如果解析到 '<'，说明开始进行起始标签的匹配，转移到 B
                        cur_state_ = ProgramState::B;
                        ++i;
                    } else {
                        /// 如果读取到其他内容，直接 return false
                        return false;
                    }
                    break;
                case ProgramState::B:
                    if (code[i] >= 'A' && code[i] <= 'Z') {
                        // 如果是大写字母，说明开始解析头部标签，转移到 C
                        tag += code[i];
                        cur_state_ = ProgramState::C;
                        ++i;
                    } else {
                        // 如果解析到其他内容，则直接返回错误
                        return false;
                    }
                    break;
                case ProgramState::C:
                    if (code[i] >= 'A' && code[i] <= 'Z') {
                        // 如果解析到大写字母，说明在解析标签，维持状态 c
                        tag += code[i];
                        ++i;
                    } else if (code[i] == '>') {
                        // 说明解析标签完毕

                        if (tag.size() > 9) {
                            // 如果长度不合要求，结束
                            return false;
                        } else {
                            // 压栈
                            tags.push(tag);
                            // 清楚内容
                            tag.clear();
                            // 转移到 D
                            cur_state_ = ProgramState::D;
                            ++i;
                        }
                    } else {
                        return false;
                    }
                    break;
                case ProgramState::D:
                    if (i < len - 8 && code.substr(i, 9) == string("<![CDATA[")) {
                        // 如果可以解析到 "<![CDATA["，
                        // 开始解析 cdata，转移到 状态 E
                        cur_state_ = ProgramState::E;
                        i += 9;
                    } else if (i < len - 1 && code.substr(i, 2) == string("</")) {
                        // 如果可以解析到 '</'，
                        // 开始解析结束标签，转移到状态 F
                        cur_state_ = ProgramState::F;
                        i += 2;
                    } else if (code[i] == '<') {
                        // 如果解析到这里说明 TAG_CONTENT 中存在嵌套标签
                        cur_state_ = ProgramState::B;
                        ++i;
                    } else {
                        ++i;
                    }
                    break;
                case ProgramState::E:
                    if (i < len - 2 && code.substr(i, 3) == string("]]>")) {
                        // cdata 解析完成，
                        // 转移到状态 D
                        cur_state_ = ProgramState::D;
                        i += 3;
                    } else {
                        ++i;
                    }
                    break;
                case ProgramState::F:
                    if (code[i] >= 'A' && code[i] <= 'Z') {
                        tag += code[i];
                        ++i;
                    } else if (code[i] == '>') {
                        // 终止标签解析完毕
                        if (tag.size() > 9) {
                            return false;
                        } else {
                            if (tags.top() != tag) {
                                return false;
                            }
                            // 与栈顶匹配
                            tags.pop();
                            // 情况内容
                            tag.clear();

                            // 转移到状态 D
                            cur_state_ = ProgramState::D;

                            ++i;
                            if (tags.empty() && i != len) {
                                return false;
                            }
                        }
                    } else {
                        return false;
                    }
                    break;
            }
        }

        return tags.empty() && cur_state_ == ProgramState::D;
    }
 private:
    // 设置不同的状态来解析
    enum class ProgramState {
        A, B, C, D, E, F
    };

    ProgramState cur_state_;
};
````
