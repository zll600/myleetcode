# [901. Online Stock Span](https://leetcode.com/problems/online-stock-span/)

## 题目

Design an algorithm that collects daily price quotes for some stock and returns **the span** of that stock's price for the current day.

The **span** of the stock's price today is defined as the maximum number of consecutive days (starting from today and going backward) for which the stock price was less than or equal to today's price.

- For example, if the price of a stock over the next `7` days were `[100,80,60,70,60,75,85]`, then the stock spans would be `[1,1,1,2,1,4,6]`.

Implement the `StockSpanner` class:

- `StockSpanner()` Initializes the object of the class.
- `int next(int price)` Returns the **span** of the stock's price given that today's price is `price`.

 

**Example 1:**

```
Input
["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
[[], [100], [80], [60], [70], [60], [75], [85]]
Output
[null, 1, 1, 1, 2, 1, 4, 6]

Explanation
StockSpanner stockSpanner = new StockSpanner();
stockSpanner.next(100); // return 1
stockSpanner.next(80);  // return 1
stockSpanner.next(60);  // return 1
stockSpanner.next(70);  // return 2
stockSpanner.next(60);  // return 1
stockSpanner.next(75);  // return 4, because the last 4 prices (including today's price of 75) were less than or equal to today's price.
stockSpanner.next(85);  // return 6
```

 

**Constraints:**

- `1 <= price <= 105`
- At most `104` calls will be made to `next`.

## 题目大意

编写一个 StockSpanner 类，返回当日股票价格变化的跨度，

今日股票价格的跨度被定义为股票价格小于或等于今天价格的最大连续日数（从今天开始往回数，包括今天）。

## 解题思路

* 可以利用一个单调栈来做，维护一个单调递增的下标。

## 代码

````c++
class StockSpanner {
public:
    StockSpanner() {
        
    }
    
    int next(int price) {
        int res = 1;
        if (span.empty()) {
            span.push_back(res);
            prices.push_back(price);
            
            return res;
        }
        
        for (int i = prices.size() - 1; i >= 0 && price >= prices[i]; i -= span[i]) {
            res += span[i];
        }
        span.push_back(res);
        prices.push_back(price);
        
        return res;
    }
    
 private:
    vector<int> span;
    vector<int> prices;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
````

