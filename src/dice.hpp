#pragma once

#include <random>

class d6
{
private:
    typedef unsigned char result_t;
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<result_t> dis;
public:
    d6();
    ~d6();

    result_t roll();
};