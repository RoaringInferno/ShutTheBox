#include "io.hpp"

#include <iostream>

void IO::print(const std::string &message)
{
    std::cout << message;
}

void IO::push(const std::string &message)
{
    output_buffer += message; // Append the message to the output buffer
}

void IO::clear()
{
    output_buffer.clear();
}

void IO::flush()
{
    std::cout << output_buffer << std::flush; // Flush the output buffer to the console
    clear();
}

std::string &IO::get_output_buffer()
{
    return output_buffer;
}

void IO::get_input(std::string &input_buffer) const
{
    std::cin >> input_buffer; // Get input from the console
}

void IO::clear_console()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls"); // Clear the console on Windows
#else
    system("clear"); // Clear the console on Unix
#endif
}
