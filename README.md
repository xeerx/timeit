# C++ Timeit
A quick C++ library to measure/compare code execution time

## Features
- **High Resolution** using a perfect algorithm to get the best result
- **Easy**  include and just call `timeit()` or `compareit()`
- **Fast**  It just loop to find the median result
- **Light** No lots of code, just simple little functions
- **CrossPlatform** It doesn't use any third party libraries, so it should work anywhere

## Syntax
```cpp
// measure time of function
timeit(count, function, args).unit();   // return value

// compare time between two functions
compareit(count, function1, function2); // print result
compareit(timeit(..), timeit(..));      // print result

// repeat function
repeatit(count, function, args);
```

## High Resolution

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
[COMPARE IT] first(675)  > second(22) x30
[COMPARE IT] first(697)  > second(22) x31
[COMPARE IT] first(698)  > second(23) x30
```

## Units
- **hours**
- **minutes**
- **seconds**
- **milliseconds**
- **microseconds** 
- **nanoseconds**
