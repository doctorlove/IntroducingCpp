#include <exception>
#include <iostream>
#include <stdexcept> //<1>

double get_number(std::istream & input_stream)
{
    double number{};
    input_stream >> number;
    if(input_stream)
    {
        if (number >= 0.0) //<2>
        {
            return number;
        }
        throw std::invalid_argument("Please provide a non-negative number"); //<3>
    }
    throw std::exception{}; //<4>
}

int main()
{
    try
    {
        std::cout << "Please enter a number.\n>";
        double number = get_number(std::cin);
        std::cout << "Got " << number << " thanks!\n";
    }
    catch(const std::invalid_argument & ex) //<1>
    {
        std::cout << ex.what() <<'\n';  //<2>
    }
    catch(const std::exception& ex) //<3>
    {
        std::cout << "Something went wrong\n";
    }
}

