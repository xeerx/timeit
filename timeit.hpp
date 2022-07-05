/**
 * @file    timeit.hpp
 * @brief   A quick C++ library to measure/compare code execution time
 * @version 0.8.1
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
#include <iomanip>      // std::setprecision
#include <stdexcept>    // std::runtime_error
#include <utility>      // std::pair

double medianit(std::vector<std::size_t> & v) noexcept(false)  
{
    if(v.empty()) throw std::runtime_error("The vector must not be empty");
    
    const auto middleItr = v.begin() + v.size() / 2;

    std::nth_element(v.begin(), middleItr, v.end());

    if (v.size() % 2 == 0) 
    {
        const auto leftMiddleItr = std::max_element(v.begin(), middleItr);
        return (*leftMiddleItr + *middleItr) / 2.0; 
    } 

    return static_cast<double>(*middleItr);
}

class timeit
{
    using clock = std::chrono::steady_clock;

    private: 
    std::size_t result = 0;

    public:
    template <class F, typename ...A>
    timeit(const std::size_t count, const F func, A&& ...args) noexcept(false) 
    {
        if(count == 0) throw std::runtime_error("The count must not be zero");
        std::vector<std::size_t> results {};

        for (std::size_t i = 0; i < count; i++)
        {
            auto begin = clock::now();
            func(std::forward<A>(args)...);
            auto end   = clock::now();
            results.push_back((end - begin).count());
        }

        result = medianit(results);
    }

    std::size_t nanoseconds () { return result;                  }
    std::size_t microseconds() { return nanoseconds   () / 1000; }
    std::size_t milliseconds() { return microseconds  () / 1000; }
    std::size_t seconds     () { return milliseconds  () / 1000; }
    std::size_t minutes     () { return seconds       () / 60;   }
    std::size_t hours       () { return minutes       () / 60;   }
};


template <class F, typename ...A>
void repeatit(const std::size_t count, const F func, A&& ...args)
{
    for (std::size_t i = 0; i < count; i++) func(std::forward<A>(args)...);
}

class compareit
{
    private:
    std::size_t func1_result = 0, func2_result = 0;

    template <class F>
    void calc(std::size_t& result, const std::size_t count, const F func) noexcept
    {
        std::vector<std::size_t> results {};

        for (std::size_t i = 0; i < 10; i++) results.push_back(timeit(count,func).nanoseconds());

        result = medianit(results);
    }

    void handler() noexcept
    {
        if(func1_result == func2_result) 
        {
            #ifdef __unix__
                std::cout 
                << "\033[1;33m" << "[COMPARE IT]" << "\033[0m"
                << "\033[0;34m" << " first(" << "\033[1;35m" << func1_result << "\033[0;34m" << ") " << "\033[0m"
                << "\033[1;33m" << "=" << "\033[0m"
                << "\033[0;34m" << " second(" << "\033[1;35m" << func2_result << "\033[0;34m" << ") " << "\033[0m \n";
            #else
                std::cout << "[COMPARE IT]" << " first(" << func1_result << ") = second(" << func2_result << ") \n";
            #endif

            return;
        }

        const std::pair<std::size_t, std::size_t> bounds = std::minmax(func1_result,func2_result);
        
        const std::size_t xtimes = bounds.first == 0 ? 1 : (bounds.second / bounds.first);
        
        const bool first_is_max = bounds.second == func1_result;

        #ifdef __unix__
            std::cout 
            << "\033[1;33m" << "[COMPARE IT]" << "\033[0m"
            << "\033[0;34m" << (first_is_max ? " first(" : " second(")  << "\033[1;35m"  << (first_is_max? func1_result : func2_result) << "\033[0;34m" << ") " << "\033[0m"
            << "\033[1;33m" << ">" << "\033[0m"
            << "\033[0;34m" << (first_is_max ? " second(" : " first(")  << "\033[1;35m" << (first_is_max ? func2_result : func1_result) << "\033[0;34m" << ") " << "\033[0m"
            << "\033[1;31m" << "x" << std::fixed << std::setprecision(3) << xtimes << "\033[0m \n";
        #else
            std::cout 
            << "[COMPARE IT]" 
            << (first_is_max ? " first(" : " second(") << (first_is_max? func1_result : func2_result)<< ") >"
            << (first_is_max ? " second(" : " first(") << (first_is_max ? func2_result : func1_result) << ") x"
            << std::fixed << std::setprecision(3) << xtimes << "\n";
        #endif
        
        return;
    }

    public:
    template <class F>
    compareit(const std::size_t count, const F func1, const F func2) noexcept(false)
    {
        if(count == 0) throw std::runtime_error("The count must not be zero");

        calc(func1_result, count, func1);
        calc(func2_result, count, func2);
        handler();
    }
};
