# C++ Timeit
A quick c++ library to measure/compare code execution time

## Features
- **Easy**  include and just call `timeit()` or `compareit()`
- **Fast**  It just loop to find the median result
- **Light** No lots of code, just simple little functions
- **CrossPlatform** It doesn't using any third party libraries, so it should work anywhere

## Syntax
```cpp
// measure time of function
timeit(count, function, args).unit();   // return value

// compare time between two functions
compareit(count, function1, function2); // print result
compareit(timeit(..), timeit(..));      // print result

// repeat function
repeat(count, function, args);
```

## Units
- **hours**
- **minutes**
- **seconds**
- **milliseconds**
- **microseconds** 
- **nanoseconds**
