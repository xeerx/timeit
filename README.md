# C++ Timeit
A quick test to measure code time

## Features
- **Easy**  include and just call `timeit()`
- **Fast**  It just calculates the average time in the loop
- **Light** No lots of code, just one function is written
- **CrossPlatform** It doesn't using any third party libraries, so it should work anywhere

## Syntax
```cpp
timeit(count, function, args).unit();
```

## Example
```cpp
#include "timeit.hpp"

void func(int a, int b){ /* do something */ }

std::cout << timeit(1000, func, 5, 5).nanoseconds() << "[ns]" << std::endl;
```
_result_
```
1155144590 [ns]
```

## Another Example
```cpp
timit t(1000, func, 5, 5);
std::cout << t.seconds() << "[s]" << std::endl;
```

## Units / Methods
- **hours**
- **minutes**
- **seconds**
- **milliseconds**
- **microseconds**
- **nanoseconds**

- **get** `std::chrono::high_resolution_clock::duration`
