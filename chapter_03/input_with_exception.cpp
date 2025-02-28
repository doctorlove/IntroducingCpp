#include <exception> //<1>
#include <iostream>

double get_number(std::istream & input_stream) //<2>
{
    double number{}; //<3>
    input_stream >> number;
    if(input_stream)
    {
        return number; //<4>
    }
    throw std::exception{}; //<5>
}

int main()
{
    try //<1>
    { //<2>
        std::cout << "Please enter a number.\n>";
        double number = get_number(std::cin);
        std::cout << "Got " << number << " thanks!\n";
    } //<3>
    catch(const std::exception& ex) //<4>
    { //<5>
        std::cout << "Something went wrong\n";
    } //<6>
}

