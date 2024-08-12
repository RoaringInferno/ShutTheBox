#pragma once

#include <string>

class IO
{
private:
    std::string output_buffer; // Stores the output buffer
public:
    IO();
    ~IO();

    void print(const std::string& message); // Print a message to the console
    void push(const std::string& message); // Push a message to the output buffer
    void clear(); // Clear the output buffer
    void flush(); // Flush the output buffer

    std::string& get_output_buffer(); // Get the output buffer
    void get_input(std::string& input_buffer) const; // Get input from the console

    void clear_console(); // Clear the console
};