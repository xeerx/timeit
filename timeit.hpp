/**
 * @file    timeit.hpp
 * @brief   A quick c++ library to measure/compare code execution time
 * @version 0.4
 *
 * Copyright (c) 2022 Maysara Elshewehy (xeerx.com) (maysara.elshewehy@gmail.com)
 *
 * Distributed under the MIT License (MIT) 
*/

#pragma once
#include <functional>
#include <chrono>
#include <iostream>

class timeit
{
    // shortcut
    using cloak = std::chrono::high_resolution_clock;

    private: cloak::duration result {};

    public:
    template <class F, typename ...A>
    timeit(unsigned int count, F func, A&& ...args) 
    {
        for (size_t i = 0; i < count; i++)
        {
            auto begin = cloak::now();
            func(std::forward<A>(args)...);
            auto end = cloak::now();
            result += end - begin;
        }

        result = result / count;
    }

    auto nanoseconds () { return result.count();          }
    auto microseconds() { return nanoseconds   () / 1000; }
    auto milliseconds() { return microseconds  () / 1000; }
    auto seconds     () { return milliseconds  () / 1000; }
    auto minutes     () { return seconds       () / 60;   }
    auto hours       () { return minutes       () / 60;   }

    auto duration    () { return result;                  }

    timeit(const timeit &) = default;
    timeit(     timeit &&) = default;
    ~timeit             () = default;
};

class compareit
{
    public:
    template <class F>
    compareit(unsigned int count, F func1, F func2) 
    {
        unsigned long int t1 = timeit(count, func1).nanoseconds();
        unsigned long int  t2 = timeit(count, func2).nanoseconds();
        handler(count,t1,t2);
    }
    compareit(unsigned int count, timeit func1, timeit func2) 
    {
        handler(count,func1.nanoseconds(),func2.nanoseconds());
    }

    void handler(unsigned int count, unsigned long int  t1, unsigned long int t2)
    {
        unsigned long int max = 0, min = 0;
        if(t1 > t2) { max = t1; min = t2; } else if(t1 < t2) { max = t2; min = t1; } 
        else 
        {
            std::cout 
            << "\033[1;33m" << "[COMPARE IT]" << "\033[0m"
            << "\033[0;34m" << " first(" << "\033[1;35m" << t1 << "\033[0;34m" << ") " << "\033[0m"
            << "\033[1;33m" << "=" << "\033[0m"
            << "\033[0;34m" << " second(" << "\033[1;35m" << t2 << "\033[0;34m" << ") " << "\033[0m" << std::endl;
            return;
        }
        
        auto tot = (max + min);
        auto diff = (max - min);
        // auto percent = (static_cast<long double>(diff) / tot) * 100;
        auto percent = (static_cast<long double>(max) / min);
        
        bool t1Max = max == t1 ? true : false;

        std::cout 
        << "\033[1;33m" << "[COMPARE IT]" << "\033[0m"
        << "\033[0;34m" << (t1Max ? " first(" : " second(") << "\033[1;35m" << (t1Max? t1 : t2) << "\033[0;34m" << ") " << "\033[0m"
        << "\033[1;33m" << ">" << "\033[0m"
        << "\033[0;34m" << (t1Max ? " second(" : " first(")  << "\033[1;35m" << (t1Max ? t2 : t1) << "\033[0;34m" << ") " << "\033[0m"
        << "\033[1;31m" << "x" << std::fixed << std::setprecision(3) << percent << "\033[0m" << std::endl;
    }

    compareit(const compareit &) = default;
    compareit(     compareit &&) = default;
    ~compareit                () = default;
};
