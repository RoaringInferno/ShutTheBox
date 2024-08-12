#pragma once

#include <random>

class d6
{
public:
    typedef unsigned char result_t;
private:
    std::mt19937 gen;
    std::uniform_int_distribution<result_t> dis;
public:
    d6();
    ~d6();

    result_t roll();
};