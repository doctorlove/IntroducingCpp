#include <expected> 
#include <iostream>
#include <string>

std::expected<double, std::string> get_number(std::istream & input_stream) //<1>
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
    while(true) //<2>
    { //<3>
        auto number = get_number(std::cin);
        if(number.has_value()) //<4>
        {
            std::cout << "Got " << number.value() << " thanks!\n>"; 
        }
        else
        {
            std::cout << number.error() << '\n'; //<5>
            break; //<6>
        }
    }
}

