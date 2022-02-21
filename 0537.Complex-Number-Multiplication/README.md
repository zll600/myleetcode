# [537. Complex Number Multiplication](https://leetcode.com/problems/complex-number-multiplication/) 

A [complex number](https://en.wikipedia.org/wiki/Complex_number) can be represented as a string on the form `"**real**+**imaginary**i"` where:

- `real` is the real part and is an integer in the range `[-100, 100]`.
- `imaginary` is the imaginary part and is an integer in the range `[-100, 100]`.
- `i2 == -1`.

Given two complex numbers `num1` and `num2` as strings, return *a string of the complex number that represents their multiplications*.

 

**Example 1:**

```
Input: num1 = "1+1i", num2 = "1+1i"
Output: "0+2i"
Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
```

**Example 2:**

```
Input: num1 = "1+-1i", num2 = "1+-1i"
Output: "0+-2i"
Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.
```

 

**Constraints:**

- `num1` and `num2` are valid complex numbers.

## 题目大意 

复数 可以用字符串表示，遵循 "实部+虚部i" 的形式，并满足下述条件：

- `实部` 是一个整数，取值范围是 `[-100, 100]`
- `虚部` 也是一个整数，取值范围是 `[-100, 100]`
- `i2 == -1`

给你两个字符串表示的复数 `num1` 和 `num2` ，请你遵循复数表示形式，返回表示它们乘积的字符串。

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/complex-number-multiplication/solution/go-san-xing-jie-jue-by-endlesscheng-jfzf/)

### Solution 1:

````go
func complexNumberMultiply(num1 string, num2 string) string {
    x, _ := strconv.ParseComplex(num1, 64)
	y, _ := strconv.ParseComplex(num2, 64)
	return fmt.Sprintf("%d+%di", int(real(x*y)), int(imag(x*y)))
}
````



