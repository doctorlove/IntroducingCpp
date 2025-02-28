#include <expected> //<1>
#include <iostream>
#include <string> //<2>

std::expected<double, std::string> get_number(std::istream & input_stream) //<3>
{
    double number{};
    input_stream>> number;
    if(input_stream)
    {
        return number;
    }
    return std::unexpected{"That's not a number"}; //<4>
}

int main()
{
    std::cout << "Please enter a number.\n>";
    auto number = get_number(std::cin);  //<5>
    if(number.has_value())  //<6>
    {
        std::cout << "Got " << number.value() << " thanks!\n"; //<7>
    }
    else
    {
        std::cout << number.error() << '\n'; //<8>
    }
}

