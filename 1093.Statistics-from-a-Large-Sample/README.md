# [1093. Statistics from a Large Sample](https://leetcode.com/problems/statistics-from-a-large-sample/)

## 题目

You are given a large sample of integers in the range `[0, 255]`. Since the sample is so large, it is represented by an array `count` where `count[k]` is the **number of times** that `k` appears in the sample.

Calculate the following statistics:

- `minimum`: The minimum element in the sample.

- `maximum`: The maximum element in the sample.

- `mean`: The average of the sample, calculated as the total sum of all elements divided by the total number of elements.

- ```
  median
  ```

  : 

  - If the sample has an odd number of elements, then the `median` is the middle element once the sample is sorted.
  - If the sample has an even number of elements, then the `median` is the average of the two middle elements once the sample is sorted.

- `mode`: The number that appears the most in the sample. It is guaranteed to be **unique**.

Return *the statistics of the sample as an array of floating-point numbers* `[minimum, maximum, mean, median, mode]`*. Answers within* `10-5` *of the actual answer will be accepted.*

 

**Example 1:**

```
Input: count = [0,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
Output: [1.00000,3.00000,2.37500,2.50000,3.00000]
Explanation: The sample represented by count is [1,2,2,2,3,3,3,3].
The minimum and maximum are 1 and 3 respectively.
The mean is (1+2+2+2+3+3+3+3) / 8 = 19 / 8 = 2.375.
Since the size of the sample is even, the median is the average of the two middle elements 2 and 3, which is 2.5.
The mode is 3 as it appears the most in the sample.
```

**Example 2:**

```
Input: count = [0,4,3,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
Output: [1.00000,4.00000,2.18182,2.00000,1.00000]
Explanation: The sample represented by count is [1,1,1,1,2,2,2,3,3,4,4].
The minimum and maximum are 1 and 4 respectively.
The mean is (1+1+1+1+2+2+2+3+3+4+4) / 11 = 24 / 11 = 2.18181818... (for display purposes, the output shows the rounded number 2.18182).
Since the size of the sample is odd, the median is the middle element 2.
The mode is 1 as it appears the most in the sample.
```

 

**Constraints:**

- `count.length == 256`
- `0 <= count[i] <= 109`
- `1 <= sum(count) <= 109`
- The mode of the sample that `count` represents is **unique**.

我们对 0 到 255 之间的整数进行采样，并将结果存储在数组 count 中：count[k] 就是整数 k 的采样个数。

我们以 浮点数 数组的形式，分别返回样本的最小值、最大值、平均值、中位数和众数。其中，众数是保证唯一的。我们先来回顾一下中位数的知识：

- 如果样本中的元素有序，并且元素数量为奇数时，中位数为最中间的那个元素；
- 如果样本中的元素有序，并且元素数量为偶数时，中位数为中间的两个元素的平均值。

## 解题思路

### Solution 1:

这里遍历两次，

- 第一次计算最大值、最小值、众数、平均数、并算出总元素的个数，为第二次遍历做准备
- 第二次计算中位数

这里需要注意的有

- go 本身是强类型的，不会执行 整型到浮点型的自动转化
- 注意 第 len / 2 数 和 下标为 len / 2 + 1 的数是不同的，

````Go
func sampleStats(count []int) []float64 {
    maxVal := -1.0
    minVal := -1.0
    totalSum := 0.0
    totalCnt := 0
    mode := -1.0
    mostFreq := -1

    for k, val := range count {
        if val == 0 {
            continue
        }

        // 第一个不为 0 的
        if minVal < 0 {
            minVal = float64(k)
        }
        // 最后一个不为 0 的
        maxVal = float64(k)

        // 计算平均数
        totalSum += float64(k * val)
        totalCnt += val

        // 寻找众数
        if val > mostFreq {
            mode = float64(k)
            mostFreq = val
        }
    }
    mean := totalSum / float64(totalCnt)

    // 找中位数
    median := 0.0
    if (totalCnt & 1) == 1 {
        // 如果总长度是奇数，找第 len / 2 + 1(不是下标，是个数)
        medIdx := totalCnt >> 1
        cnt := 0
        for k, val := range count {
            cnt += val
            if cnt > medIdx {
                median = float64(k)
                break
            }
        }
    } else {
        // 如果总长度是偶数，找到 len / 2 和 len / 2 + 1
        medIdx := totalCnt >> 1
        left, right := -1, -1
        cnt := 0

        for k, val := range count {
            cnt += val

            if left < 0 && cnt > medIdx - 1 {
                left = k
            }
            if right < 0 && cnt > medIdx {
                right = k
            }

            if left > 0 && right > 0 {
                break
            }
        }
        median = float64((left + right)) / 2.0
    }

    return []float64{minVal, maxVal, mean, median, mode}
}
````
