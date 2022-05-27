# [2043. Simple Bank System](https://leetcode.com/problems/simple-bank-system/)

## 题目

You have been  tasked with writing a program for a popular bank that will automate all  its incoming transactions (transfer, deposit, and withdraw). The bank  has `n` accounts numbered from `1` to `n`. The initial balance of each account is stored in a **0-indexed** integer array `balance`, with the `(i + 1)th` account having an initial balance of `balance[i]`.

Execute all the **valid** transactions. A transaction is **valid** if:

- The given account number(s) are between `1` and `n`, and
- The amount of money withdrawn or transferred from is **less than or equal** to the balance of the account.

Implement the `Bank` class:

- `Bank(long[] balance)` Initializes the object with the **0-indexed** integer array `balance`.
- `boolean transfer(int account1, int account2, long money)` Transfers `money` dollars from the account numbered `account1` to the account numbered `account2`. Return `true` if the transaction was successful, `false` otherwise.
- `boolean deposit(int account, long money)` Deposit `money` dollars into the account numbered `account`. Return `true` if the transaction was successful, `false` otherwise.
- `boolean withdraw(int account, long money)` Withdraw `money` dollars from the account numbered `account`. Return `true` if the transaction was successful, `false` otherwise.

 

**Example 1:**

```
Input
["Bank", "withdraw", "transfer", "deposit", "transfer", "withdraw"]
[[[10, 100, 20, 50, 30]], [3, 10], [5, 1, 20], [5, 20], [3, 4, 15], [10, 50]]
Output
[null, true, true, true, false, false]

Explanation
Bank bank = new Bank([10, 100, 20, 50, 30]);
bank.withdraw(3, 10);    // return true, account 3 has a balance of $20, so it is valid to withdraw $10.
                         // Account 3 has $20 - $10 = $10.
bank.transfer(5, 1, 20); // return true, account 5 has a balance of $30, so it is valid to transfer $20.
                         // Account 5 has $30 - $20 = $10, and account 1 has $10 + $20 = $30.
bank.deposit(5, 20);     // return true, it is valid to deposit $20 to account 5.
                         // Account 5 has $10 + $20 = $30.
bank.transfer(3, 4, 15); // return false, the current balance of account 3 is $10,
                         // so it is invalid to transfer $15 from it.
bank.withdraw(10, 50);   // return false, it is invalid because account 10 does not exist.
```

 

**Constraints:**

- `n == balance.length`
- `1 <= n, account, account1, account2 <= 10^5`
- `0 <= balance[i], money <= 1012`
- At most `104` calls will be made to **each** function `transfer`, `deposit`, `withdraw`.

## 题目大意

你的任务是为一个很受欢迎的银行设计一款程序，以自动化执行所有传入的交易（转账，存款和取款）。银行共有 `n` 个账户，编号从 `1` 到 `n`  

每个账号的初始余额存储在一个下标从 `0` 开始的整数数组 `balance` 中，其中第 `(i + 1)` 个账户的初始余额是 `balance[i]` 

请你执行所有 *有效的* 交易。如果满足下面全部条件，则交易 *有效* ：

- 指定的账户数量在 `1` 和 `n` 之间，且
- 取款或者转账需要的钱的总数 小于或者等于 账户余额。

实现 `Bank` 类：

- `Bank(long[] balance)` 使用下标从 `0` 开始的整数数组 `balance` 初始化该对象
- `boolean transfer(int account1, int account2, long money)` 从编号为 `account1` 的账户向编号为  `account2` 的账户转帐 `money` 美元。如果交易成功，返回 true ，否则，返回 false 
- `boolean deposit(int account, long money)` 向编号为 `account` 的账户存款` money` 美元。如果交易成功，返回 `true` ；否则，返回 `false` 
- `boolean withdraw(int account, long money)` 从编号为 `account` 的账户取款 `money` 美元。如果交易成功，返回 `true` ；否则，返回 `false`

## 解题思路

这道题目还是比较简单的，考虑好特殊情况就可以了

### Solution 1:

````c++
class Bank {
public:
    Bank(vector<long long>& balance) : data_(balance) {
    }
    
    bool transfer(int account1, int account2, long long money) {
        if (!IsValid(account1) || !IsValid(account2)) {
            return false;
        }
        if (data_[account1 - 1] < money) {
            return false;
        }
        data_[account1 - 1] -= money;
        data_[account2 - 1] += money;
        return true;
    }
    
    bool deposit(int account, long long money) {
        if (!IsValid(account)) {
            return false;
        }
        data_[account - 1] += money;
        return true;
    }
    
    bool withdraw(int account, long long money) {
        if (!IsValid(account)) {
            return false;
        }
        if (data_[account - 1] < money) {
            return false;
        }
        
        data_[account - 1] -= money;
        return true;
    }
    
 private:
    vector<long long> data_;
    
    bool IsValid(int x) {
        return x >= 1 && x <= data_.size();
    }
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */
````
