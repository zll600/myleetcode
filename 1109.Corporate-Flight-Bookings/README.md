# [1109. Corporate Flight Bookings](https://leetcode.cn/problems/corporate-flight-bookings/)

## 题目

There are `n` flights that are labeled from `1` to `n`.

You are given an array of flight bookings `bookings`, where `bookings[i] = [firsti, lasti, seatsi]` represents a booking for flights `firsti` through `lasti` (**inclusive**) with `seatsi` seats reserved for **each flight** in the range.

Return *an array* `answer` *of length* `n`*, where* `answer[i]` *is the total number of seats reserved for flight* `i`.

 

**Example 1:**

```
Input: bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
Output: [10,55,45,25,25]
Explanation:
Flight labels:        1   2   3   4   5
Booking 1 reserved:  10  10
Booking 2 reserved:      20  20
Booking 3 reserved:      25  25  25  25
Total seats:         10  55  45  25  25
Hence, answer = [10,55,45,25,25]
```

**Example 2:**

```
Input: bookings = [[1,2,10],[2,2,15]], n = 2
Output: [10,25]
Explanation:
Flight labels:        1   2
Booking 1 reserved:  10  10
Booking 2 reserved:      15
Total seats:         10  25
Hence, answer = [10,25]
```

 

**Constraints:**

- `1 <= n <= 2 * 104`
- `1 <= bookings.length <= 2 * 104`
- `bookings[i].length == 3`
- `1 <= firsti <= lasti <= n`
- `1 <= seatsi <= 104`

## 题目大意

这里有 `n` 个航班，它们分别从 `1` 到 `n` 进行编号

有一份航班预订表 `bookings` ，表中第 `i` 条预订记录 `bookings[i] = [firsti, lasti, seatsi]` 意味着在从 `firsti` 到 `lasti` （包含 `firsti` 和 `lasti` ）的 每个航班 上预订了 `seatsi` 个座位

请你返回一个长度为 `n` 的数组 `answer`，里面的元素是每个航班预定的座位总数

## 解题思路

这里还是很容易看出，有涉及数组的区间修改和单点查询，所以还是可以想到使用 差分数组来做的

### Solution 1: 差分数组

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/corporate-flight-bookings/solution/gong-shui-san-xie-yi-ti-shuang-jie-chai-fm1ef/)

````c++
// 差分数组
class Difference {
 public:
    Difference(const vector<int>& nums) : data_(vector<int>(nums.size())) {
        data_[0] = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            data_[i] = nums[i - 1] - nums[i - 1];
        }
    }

    void Incr(int i, int j, int val) {
        data_[i] += val;
        if (j + 1 < data_.size()) {
            data_[j + 1] -= val;
        }
    }

    vector<int> Res() {
        vector<int> nums(data_.size(), 0);
        nums[0] = data_[0];
        for (int i = 1; i < data_.size(); ++i) {
            nums[i] = nums[i - 1] + data_[i];
        }
        return nums;
    }

 private:
    vector<int> data_;
};

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> nums(n, 0);
        Difference df(nums);

        for (const auto& booking : bookings) {
            int i = booking[0] - 1;
            int j = booking[1] - 1;
            int val = booking[2];

            df.Incr(i, j, val);
        }

        return df.Res();
    }
};
````
