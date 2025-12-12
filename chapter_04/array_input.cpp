#include <array>
#include <expected>
#include <iostream>
#include <limits>
#include <string>

void array_experiment()
{
    std::array<double, 5> numbers{}; //<1>
    std::cout << numbers[0] << '\n'; //<2>
    numbers[0] = 2.5; //<3>
    std::cout << numbers[0] << '\n'; //<4>
}

std::expected<double, std::string> get_number(std::istream & input_stream)
{
    double number{};
    input_stream >> number;
    if(input_stream)
    {
        return number;
    }
    input_stream.clear();  // <1>
    input_stream.ignore( //<2>
	std::numeric_limits<std::streamsize>::max(),
	'\n'
    );
    return std::unexpected{"That's not a number"};
}

void show_numbers(const std::array<double, 5u> & numbers)
{
    for(const auto number: numbers) //<1>
    {
        std::cout << number << '\n'; //<2>
    }
}

void max_number(const std::array<double, 5u> & numbers)
{
    double biggest = numbers[0]; //<1>
    for(const auto number: numbers) //<2>
    {
        if(number > biggest) //<3>
	{
            biggest = number; //<4>
	}
    }
    std::cout << "The biggest number is " << biggest << '\n'; //<5>
}

int main()
{
    std::cout << "Please enter some numbers.\n";
    std::array<double, 5u> numbers{}; //<1>
    size_t count = 0u; //<2>
    while(count < numbers.size()) //<3>
    {
        std::cout << '>';
        auto number = get_number(std::cin);
        if(number.has_value())
        {
            numbers[count] = number.value(); //<4>
            std::cout << "Got " << number.value() << " thanks!\n"; 
        }
        else
        {
            std::cout << number.error() << "\n";
        }
        ++count; //<5>
    }
    show_numbers(numbers);
}


