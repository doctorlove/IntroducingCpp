#include <expected> 
#include <iostream>
#include <string>

std::expected<double, std::string> get_number(std::istream & input_stream) 
{
    double number{};
    input_stream >> number;
    if(input_stream)
    {
        return number;
    }
    return std::unexpected{"That's not a number"}; 
}

int main()
{
    std::cout << "Please enter a number.\n>";
    auto number = get_number(std::cin);
    while(number.has_value()) //<1>
    { //<2>
        std::cout << "Got " << number.value() << " thanks!\n>"; 
        number = get_number(std::cin); 
    }
    std::cout << number.error() << '\n'; //<3>
}

