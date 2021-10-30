# [1195. Fizz Buzz Multithreaded](https://leetcode-cn.com/problems/fizz-buzz-multithreaded/)

## 题目

You have the four functions:

- `printFizz` that prints the word `"Fizz"` to the console,
- `printBuzz` that prints the word `"Buzz"` to the console,
- `printFizzBuzz` that prints the word `"FizzBuzz"` to the console, and
- `printNumber` that prints a given integer to the console.

You are given an instance of the class `FizzBuzz` that has four functions: `fizz`, `buzz`, `fizzbuzz` and `number`. The same instance of `FizzBuzz` will be passed to four different threads:

- **Thread A:** calls `fizz()` that should output the word `"Fizz"`.
- **Thread B:** calls `buzz()` that should output the word `"Buzz"`.
- **Thread C:** calls `fizzbuzz()` that should output the word `"FizzBuzz"`.
- **Thread D:** calls `number()` that should only output the integers.

Modify the given class to output the series `[1, 2, "Fizz", 4, "Buzz", ...]` where the `ith` token (**1-indexed**) of the series is:

- `"FizzBuzz"` if `i` is divisible by `3` and `5`,
- `"Fizz"` if `i` is divisible by `3` and not `5`,
- `"Buzz"` if `i` is divisible by `5` and not `3`, or
- `i` if `i` is not divisible by `3` or `5`.

Implement the `FizzBuzz` class:

- `FizzBuzz(int n)` Initializes the object with the number `n` that represents the length of the sequence that should be printed.
- `void fizz(printFizz)` Calls `printFizz` to output `"Fizz"`.
- `void buzz(printBuzz)` Calls `printBuzz` to output `"Buzz"`.
- `void fizzbuzz(printFizzBuzz)` Calls `printFizzBuzz` to output `"FizzBuzz"`.
- `void number(printNumber)` Calls `printnumber` to output the numbers.

 

**Example 1:**

```
Input: n = 15
Output: [1,2,"fizz",4,"buzz","fizz",7,8,"fizz","buzz",11,"fizz",13,14,"fizzbuzz"]
```

**Example 2:**

```
Input: n = 5
Output: [1,2,"fizz",4,"buzz"]
```

 

**Constraints:**

- `1 <= n <= 50`

## 题目大意

你有四个函数

- `printFizz`  向控制台打印单词`"Fizz"`
- `printBuzz` 向控制台打印`"Buzz"`
- `printFizzBuzz` 向控制台打印`"FizzBuzz"`  
- `printNumber` 向控制台打印一个指定的数字

你有一个类 `FizzBuzz` 的实例，有四个函数，`fizz`,`buzz`,`fizzbuzz`,`number`，同一个 `FizzBuzz`实例将会被传递给四个不同的线程

- **Thread A:** calls `fizz()` that should output the word `"Fizz"`.
- **Thread B:** calls `buzz()` that should output the word `"Buzz"`.
- **Thread C:** calls `fizzbuzz()` that should output the word `"FizzBuzz"`.
- **Thread D:** calls `number()` that should only output the integers.

