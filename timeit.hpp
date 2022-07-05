/**
 * @file    timeit.hpp
 * @brief   A quick c++ library to measure/compare code execution time
 * @version 0.6
 *
 * Copyright (c) 2022 Maysara Elshewehy (xeerx.com) (maysara.elshewehy@gmail.com)
 *
 * Distributed under the MIT License (MIT) 
*/

#pragma once
#include <iostream>     // std::cout
#include <chrono>       // std::chrono
#include <functional>   // std::forward
#include <vector>       // std::vector
#include <algorithm>    // std::nth_element
#include <cstddef>      // std::size_t

class timeit
{
    using clock = std::chrono::high_resolution_clock;

    private: 
    std::vector<std::size_t> results {};
    std::size_t result = 0;

    public:
    template <class F, typename ...A>
    timeit(std::size_t count, F func, A&& ...args) 
    {
        for (std::size_t i = 0; i < count; i++)
        {
            auto begin = clock::now();
            func(std::forward<A>(args)...);
            auto end   = clock::now();
            results.push_back((end - begin).count());
        }

        // get median number in vector, this is the best way i found to get the best result !
        std::nth_element(results.begin(), results.begin() + results.size()/2, results.end());
        result = results[results.size()/2];

        results.clear();
    }

    std::size_t nanoseconds () { return result;                  }
    std::size_t microseconds() { return nanoseconds   () / 1000; }
    std::size_t milliseconds() { return microseconds  () / 1000; }
    std::size_t seconds     () { return milliseconds  () / 1000; }
    std::size_t minutes     () { return seconds       () / 60;   }
    std::size_t hours       () { return minutes       () / 60;   }
};


template <class F, typename ...A>
void repeatit(std::size_t count, F func, A&& ...args)
{
    for (std::size_t i = 0; i < count; i++) func(std::forward<A>(args)...);
}

class compareit
{
    using clock = std::chrono::high_resolution_clock;

    private:
    std::vector<std::size_t> results1 {}, results2 {};
    std::size_t result1 = 0, result2 = 0;

    public:
    template <class F>
    compareit(std::size_t count, F func1, F func2) 
    {
        calc(results1, result1, count, func1);
        calc(results2, result2, count, func2);
        handler();
    }

    template <class F>
    void calc(std::vector<std::size_t>& results, std::size_t& result, std::size_t count, F func)
    {
        for (std::size_t i = 0; i < 10; i++) results.push_back(timeit(count,func).nanoseconds());

        std::nth_element(results.begin(), results.begin() + results.size()/2, results.end());
        result = results[results.size()/2];

        results.clear();
    }

    void handler()
    {
        std::size_t max = 0, min = 0;
        if(result1 > result2) { max = result1; min = result2; } else if(result1 < result2) { max = result2; min = result1; } 
        else 
        {
            std::cout 
            << "\033[1;33m" << "[COMPARE IT]" << "\033[0m"
            << "\033[0;34m" << " first(" << "\033[1;35m" << result1 << "\033[0;34m" << ") " << "\033[0m"
            << "\033[1;33m" << "=" << "\033[0m"
            << "\033[0;34m" << " second(" << "\033[1;35m" << result2 << "\033[0;34m" << ") " << "\033[0m" << std::endl;
            return;
        }
        
        auto tot = (max + min);
        auto diff = (max - min);
        // auto percent = (static_cast<std::size_t>(diff) / tot) * 100;
        auto percent = (static_cast<std::size_t>(max) / min);
        
        bool t1Max = max == result1 ? true : false;

        std::cout 
        << "\033[1;33m" << "[COMPARE IT]" << "\033[0m"
        << "\033[0;34m" << (t1Max ? " first(" : " second(") << "\033[1;35m" << (t1Max? result1 : result2) << "\033[0;34m" << ") " << "\033[0m"
        << "\033[1;33m" << ">" << "\033[0m"
        << "\033[0;34m" << (t1Max ? " second(" : " first(")  << "\033[1;35m" << (t1Max ? result2 : result1) << "\033[0;34m" << ") " << "\033[0m"
        << "\033[1;31m" << "x" << std::fixed << std::setprecision(3) << percent << "\033[0m" << std::endl;
    }
};
