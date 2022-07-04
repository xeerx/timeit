/**
 * @file    timeit.hpp
 * @brief   A simple measure time library
 * @version 0.2
 *
 * Copyright (c) 2022 Maysara Elshewehy (xeerx.com) (maysara.elshewehy@gmail.com)
 *
 * Distributed under the MIT License (MIT) 
*/

#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <chrono>

// DON'T USE IT, IT JUST HELPER FOR THE FUNCTION timeit()
class timeit_unit_caller
{
    private:
    // name of test
    std::string name;

    public:

    unsigned long int result = {};

    // constructor: init name
    timeit_unit_caller(std::string n) : name{n} {}

    // print result in seconds
    void seconds() { std::cout << name << result / 1000 / 1000 / 1000 << "[" << "s" << "]" << std::endl; }
    // print result in milliseconds
    void milliseconds() { std::cout << name  << result / 1000 / 1000 << "[" << "ms" << "]" << std::endl; }
    // print result in microseconds
    void microseconds() { std::cout << name  << result / 1000 << "[" << "µs" << "]" << std::endl; }
    // print result in nanoseconds
    void nanoseconds() { std::cout << name  << result << "[" << "ns" << "]" << std::endl; }
};

// USE IT WITH ANY TYPE OF FUNCTIONS AND ANY NUMBER/TYPE OF PARAMETERS
template <class F, typename ...A>
auto timeit(std::string name, int count, F func, A&& ...args)
{
    // create `timeit_unit_caller` class and set name
    timeit_unit_caller clss("[TIMEIT] [" + name + "]: ");
    std::chrono::steady_clock::duration total_duration = {};

    // loop
    for (size_t i = 0; i < count; i++)
    {
        // get time at beginning
        auto begin = std::chrono::steady_clock::now();

        // execute function
        func(std::forward<A>(args)...);

        // get time at finishing
        auto end = std::chrono::steady_clock::now();

        // call `set()` function to push result to results vector
        total_duration += end - begin;
    }

    clss.result  = total_duration.count() / count;
    return clss;
}
