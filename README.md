# C++ Timeit
A quick C++ library to measure/compare code execution time

## Features
- **High Resolution** using a perfect algorithm to get the best result
- **Easy**  include and just call `timeit()` or `compareit()`
- **Fast**  It just loop and find the median result
- **Light** No lots of code, just simple little functions
- **CrossPlatform** It doesn't use any third party libraries, so it should work anywhere

## Syntax
```cpp
// measure time of function
timeit(count, function, args).unit();   // return value

// compare time between two functions
compareit(count, function1, function2); // print result

// repeat function
repeatit(count, function, args);

// find median value in vector [Helper Function]
double medianit(std::vector<std::size_t> & v);
```

## High Resolution

- **to get `High Resolution` run your code in termianl, recommended `valgrind`**

- **when running code in an IDE like `vscode` the results often won't be correct**

### `timeit()`
```cpp
// simple function to test
void func() { for (auto i = 0; i < 10; i++) sqrt(i); }

// repeat `timeit()` 3 times with same values
repeatit(3,[]{ std::cout << timeit(1000, func).nanoseconds() << std::endl; });
```
__result__
```
22
22 
22
```

### `compareit()`
```cpp
// simple functions to test
void func1() { for (auto i = 0; i < 1000; i++) sqrt(i); }
void func2() { for (auto i = 0; i < 10; i++)   sqrt(i); }

// repeat `compareit()` 3 times with same values
repeatit(3,[]{ compareit(1000,func1,func2); });
```
__result__
```
[COMPARE IT] first(660)  > second(22) x30
[COMPARE IT] first(660)  > second(22) x30
[COMPARE IT] first(660)  > second(22) x30
```

## Units
- **hours**
- **minutes**
- **seconds**
- **milliseconds**
- **microseconds** 
- **nanoseconds**
