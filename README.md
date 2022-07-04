# Timeit
A quick test to measure code time

## Features
- **Easy**  include and just call `timeit()`
- **Fast**  It just calculates the average time in the loop
- **Light** No lots of code, just one function is written
- **CrossPlatform** It doesn't using any third party libraries, so it should work anywhere

## Syntax
```cpp
timeit(name, count, function, args).unit();
```

## Example
```cpp
#include "timeit.hpp"

void func(int a, int b){ /* do something */ }

timeit("test1", 1000, func, 5, 5).microseconds();
```
_result_
```
[TIMEIT] [test1]: 500192[µs]
```

## Units
- **seconds**
- **milliseconds**
- **microseconds**
- **nanoseconds**
