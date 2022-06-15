# [1169. Invalid Transactions](https://leetcode.cn/problems/invalid-transactions/)

## 题目

A transaction is possibly invalid if:

- the amount exceeds `$1000`, or;
- if it occurs within (and including) `60` minutes of another transaction with the **same name** in a **different city**.

You are given an array of strings `transaction` where `transactions[i]` consists of comma-separated values representing the name, time (in minutes), amount, and city of the transaction.

Return a list of `transactions` that are possibly invalid. You may return the answer in **any order**.

 

**Example 1:**

```
Input: transactions = ["alice,20,800,mtv","alice,50,100,beijing"]
Output: ["alice,20,800,mtv","alice,50,100,beijing"]
Explanation: The first transaction is invalid because the second transaction occurs within a difference of 60 minutes, have the same name and is in a different city. Similarly the second one is invalid too.
```

**Example 2:**

```
Input: transactions = ["alice,20,800,mtv","alice,50,1200,mtv"]
Output: ["alice,50,1200,mtv"]
```

**Example 3:**

```
Input: transactions = ["alice,20,800,mtv","bob,50,1200,mtv"]
Output: ["bob,50,1200,mtv"]
```

 

**Constraints:**

- `transactions.length <= 1000`
- Each `transactions[i]` takes the form `"{name},{time},{amount},{city}"`
- Each `{name}` and `{city}` consist of lowercase English letters, and have lengths between `1` and `10`.
- Each `{time}` consist of digits, and represent an integer between `0` and `1000`.
- Each `{amount}` consist of digits, and represent an integer between `0` and `2000`.

## 题目大意

如果出现下述两种情况，*交易* 可能无效：

-   交易金额超过 `$1000`
-   或者，它和 *另一个城市* 中 *同名* 的另一笔交易相隔不超过 `60` 分钟（包含 `60` 分钟整）

给定字符串数组交易清单 `transaction` 。每个交易字符串 `transactions[i]` 由一些用逗号分隔的值组成，这些值分别表示交易的 *名称*，*时间（以分钟计）*，*金额* 以及 *城市*

返回 `transactions`，返回可能无效的交易列表。你可以按 任何顺序 返回答案

### 解题思路

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/invalid-transactions/solution/1169-czhong-gui-zhong-ju-de-zhi-bai-jie-em0jy/)

处理好细节就可以了，思路上没有难理解的地方

关键就在于map 

````c++
struct Transaction {
    int id;
    int time;
    int amount;
    string city;
    string full;

    Transaction(int _id, int _time, int _amount, string _city, string _full)
        : id(_id), time(_time), amount(_amount), city(_city), full(_full) {}
};

class Solution {
public:
    vector<string> invalidTransactions(vector<string>& transactions) {
        unordered_map<string, vector<Transaction>> name_to_transactions;
        vector<string> res;

        vector<int> used(transactions.size());
        for (int i = 0; i < transactions.size(); ++i) {
            string name, time, amount, city;
            SplitString(transactions[i], name, time, amount, city);
            int time_digit = stoi(time), amount_digit = stoi(amount);
            if (amount_digit > 1000) {
                used[i] = true;
                res.push_back(transactions[i]);
            }

            for (const auto& elem : name_to_transactions[name]) {
                if (elem.city != city && abs(time_digit - elem.time) <= 60) {
                    if (!used[elem.id]) {
                        used[elem.id] = true;
                        res.push_back(elem.full);
                    }
                    if (!used[i]) {
                        used[i] = true;
                        res.push_back(transactions[i]);
                    }
                }
            }
            name_to_transactions[name].emplace_back(i, time_digit, amount_digit,
                                                    city, transactions[i]);
        }
        return res;
    }

 private:
    void SplitString(const string& transaction, string& name, string& time, string& amount,
                     string& city) {
        stringstream ss(transaction);
        getline(ss, name, ',');
        getline(ss, time, ',');
        getline(ss, amount, ',');
        getline(ss, city, ',');
    }
};
````
