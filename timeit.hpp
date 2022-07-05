/**
 * @file    timeit.hpp
 * @brief   A quick C++ library to measure/compare code execution time
 * @version 0.7.7
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

class timeit
{
    using clock = std::chrono::steady_clock;

    private: 
    std::vector<std::size_t> results {};
    std::size_t result = 0;

    public:
    template <class F, typename ...A>
    timeit(const std::size_t count, const F func, A&& ...args) noexcept(false) 
    {
        if(count == 0) throw std::runtime_error("The count must not be zero");

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
void repeatit(const std::size_t count, const F func, A&& ...args)
{
    for (std::size_t i = 0; i < count; i++) func(std::forward<A>(args)...);
}

class compareit
{
    using clock = std::chrono::steady_clock;

    private:
    std::vector<std::size_t> results1 {}, results2 {};
    std::size_t result1 = 0, result2 = 0;

    template <class F>
    void calc(std::vector<std::size_t>& results, std::size_t& result, const std::size_t count, const F func) noexcept
    {
        for (std::size_t i = 0; i < 10; i++) results.push_back(timeit(count,func).nanoseconds());

        std::nth_element(results.begin(), results.begin() + results.size()/2, results.end());
        result = results[results.size()/2];

        results.clear();
    }

    void handler() noexcept
    {
        if(result1 == result2) 
        {
            std::cout 
            << "\033[1;33m" << "[COMPARE IT]" << "\033[0m"
            << "\033[0;34m" << " first(" << "\033[1;35m" << result1 << "\033[0;34m" << ") " << "\033[0m"
            << "\033[1;33m" << "=" << "\033[0m"
            << "\033[0;34m" << " second(" << "\033[1;35m" << result2 << "\033[0;34m" << ") " << "\033[0m \n";
            return;
        }

        const std::pair<std::size_t, std::size_t> bounds = std::minmax(result1,result2);
        
        const std::size_t xtimes = bounds.first == 0 ? 1 : (bounds.second / bounds.first);
        
        const bool first_is_max = bounds.second == result1;

        std::cout 
        << "\033[1;33m" << "[COMPARE IT]" << "\033[0m"
        << "\033[0;34m" << (first_is_max ? " first(" : " second(")  << "\033[1;35m"  << (first_is_max? result1 : result2) << "\033[0;34m" << ") " << "\033[0m"
        << "\033[1;33m" << ">" << "\033[0m"
        << "\033[0;34m" << (first_is_max ? " second(" : " first(")  << "\033[1;35m" << (first_is_max ? result2 : result1) << "\033[0;34m" << ") " << "\033[0m"
        << "\033[1;31m" << "x" << std::fixed << std::setprecision(3) << xtimes << "\033[0m \n";
    }

    public:
    template <class F>
    compareit(const std::size_t count, const F func1, const F func2) noexcept(false)
    {
        if(count == 0) throw std::runtime_error("The count must not be zero");

        calc(results1, result1, count, func1);
        calc(results2, result2, count, func2);
        handler();
    }
};
