#include <cassert>
#include <limits>
#include <istream>
#include <iostream>
#include <string>
#include <sstream>

[[nodiscard]] bool get_number(std::istream & input_stream, double & number)
{
    input_stream >> number;
    if(input_stream)
    {
        return true;
    }
    else
    {
        input_stream.clear();
        input_stream.ignore(std::numeric_limits<std::streamsize>::max(), 
            '\n');
        return false;
    }
}

void test_code()
{
    {
        double value{};
        std::stringstream some_input{"1"};
        const bool ok = get_number(some_input, value);
        assert(ok);
        assert(value == 1);
    }

    {
        double value{};
        std::stringstream some_input{"q"};
        const bool ok = get_number(some_input, value);
        assert(!ok);
    }
}

int main()
{
    test_code();

    double number{};
    std::cout << "Please enter a number.\n>";
    const bool ok = get_number(std::cin, number);
    if(ok)
    {
        std::cout << "Got " << number << ", thanks!\n";
    }
    else
    {
        std::cout << "Something went wrong\n";
    }
}

