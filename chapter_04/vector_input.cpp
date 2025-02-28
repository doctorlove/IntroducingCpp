#include <expected>
#include <limits>
#include <iostream>
#include <vector>

void vector_experiment()
{
    std::vector<int> numbers{0, 1};
    numbers.push_back(-123); //<1>
    for(const auto & number: numbers)
    {
        std::cout << number << '\n';
    }
}

void vector_insert()
{
    std::vector<int> numbers{0, 1};
    numbers.insert(numbers.begin(), -123); //<1>
    for(const auto & number: numbers)
    {
        std::cout << number << '\n';
    }
}

std::expected<double, std::string> get_number(std::istream & input_stream)
{
    double number{};
    input_stream >> number;
    if(input_stream)
    {
        return number;
    }
    input_stream.clear(); 
    input_stream.ignore( 
	std::numeric_limits<std::streamsize>::max(),
	'\n'
    );
    return std::unexpected{"That's not a number"};
}


int main()
{
     //vector_insert();
    std::cout << "Please enter some numbers.\n>";
    std::vector<double> numbers{};
    auto number = get_number(std::cin);
    while(number.has_value()) //<1>
    {
        numbers.push_back(number.value()); //<2>
        std::cout << "Got " << number.value() << " thanks!\n>";
        number = get_number(std::cin);  //<3>
    }
    std::cout << number.error() << '\n';

    std::cout <<"You entered\n";
    for(const auto & number: numbers) //<4>
    {
        std::cout << number << '\n';
    }
}

