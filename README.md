# Timeit
A quick test to measure code time

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
