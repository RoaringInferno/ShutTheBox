#include "dice.hpp"

d6::d6() :
    gen(std::random_device()()),
    dis(1, 6)
{
}

d6::~d6()
{
}

d6::result_t d6::roll()
{
    return dis(gen);
}
