/**
 * @file    timeit.hpp
 * @brief   A simple measure time way
 * @version 0.1
 *
 * Copyright (c) 2022 Maysara Elshewehy (xeerx.com) (maysara.elshewehy@gmail.com)
 *
 * Distributed under the MIT License (MIT) 
*/

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <numeric>
#include <chrono>

// DON'T USE IT, IT JUST HELPER FOR THE FUNCTION timeit()
class __timeit
{
    private:
    // name of test
    std::string name;

    // average result between all test results
    size_t result = 0;

    // storing test results
    std::vector<size_t> results;

    public:

    // constructor: init name
    __timeit(std::string n) : name{n} {}

    // print result in seconds
    void seconds() { std::cout << name << result / 1000 / 1000 << "[" << "s" << "]" << std::endl; }
    // print result in milliseconds
    void milliseconds() { std::cout << name  << result / 1000 << "[" << "ms" << "]" << std::endl; }
    // print result in microseconds
    void microseconds() { std::cout << name  << result << "[" << "µs" << "]" << std::endl; }

    // get average result between all test results and set `result`
    void get()          { result = std::reduce(results.begin(), results.end()) / results.size(); }
    // push test `result` to `results`
    void set(size_t val){ results.push_back(val); }
};

// USE IT WITH ANY TYPE OF FUNCTIONS AND ANY NUMBER/TYPE OF PARAMETERS
template <class F, typename ...A>
__timeit timeit(std::string name, int count, F func, A&& ...args)
{
    // create `__timeit` class and set name
    __timeit clss("[TIMEIT] [" + name + "]: ");

    // loop
    for (size_t i = 0; i < count; i++)
    {
        // get time at beginning
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        // execute function
        func(std::forward<A>(args)...);

        // get time at finishing
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        // call `set()` function to push result to results vector
        clss.set(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
    }

    // now call `get()` function to get average result between all test results and set `result`
    clss.get();

    // return to class object, so we can call units functions like: timeit(...).second(); easy right? :]
    return clss;
}
