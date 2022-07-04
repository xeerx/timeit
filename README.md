# C++ Timeit
A quick c++ library to measure/compare code execution time

## Features
- **Easy**  include and just call `timeit()` or `compareit()`
- **Fast**  It just calculates the average time in the loop
- **Light** No lots of code, just two functions is written
- **CrossPlatform** It doesn't using any third party libraries, so it should work anywhere

## Syntax
```cpp
// measure time of function
timeit(count, function, args).unit();   // using any function/arguments type: will return value

// compare time between two functions
compareit(count, function1, function2); // using any function type: will print result
compareit(timeit(..), timeit(..));      // using timeit: will print result
```

## Example 1: measure time of function
```cpp
void func(int a, int b){ /* ... */ } 
std::cout << timeit(1000, func, 5, 5).nanoseconds() << "[ns]" << std::endl;
// -> 1155144590 [ns]
```

## Example 2: measure time of lambda
```cpp
std::cout << timeit(1000, []{ /* ... */  }).nanoseconds() << "[ns]" << std::endl;
// -> 1155144590 [ns]
```

## Example 3: compare time between two functions
```cpp
void func1(){ /* ... */ } 
void func2(){ /* ... */ }
compareit(1000,func1,func2);
// if func1 faster  -> [COMPARE IT] first(1546210342)  > second(452181663) x3.419
// if func2 faster  -> [COMPARE IT] second(1546210342) > first(452181663)  x3.419
// if func1 = func2 -> [COMPARE IT] second(452181663) = first(452181663)
```

## Example 4: compare time between two lambda
```cpp
compareit(1000,[]{ /* ... */  },[]{ /* ... */  });
```


## Example 5: compare time between two functions using timeit()
```cpp
void func1(int a, int b){ /* ... */ } 
void func2(int a, int b){ /* ... */ }
compareit(timeit(1000,func1,5,5),timeit(1000,func2,5,5)); // in this case we don't neet to count
```

## Timeit Class Units/Methods
- **hours**
- **minutes**
- **seconds**
- **milliseconds**
- **microseconds** 
- **nanoseconds**

- **duration** `std::chrono::high_resolution_clock::duration`
