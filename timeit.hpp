/**
 * @file    timeit.hpp
 * @brief   A simple measure time library
 * @version 0.3
 *
 * Copyright (c) 2022 Maysara Elshewehy (xeerx.com) (maysara.elshewehy@gmail.com)
 *
 * Distributed under the MIT License (MIT) 
*/

#pragma once
#include <functional>
#include <chrono>

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
    
    timeit(const timeit &) = delete;
    timeit(     timeit &&) = delete;
    ~timeit             () = default;
};
