#include <iostream>
#include <limits>

int main()
{
    const double largest = std::numeric_limits<double>::max(); //<1>
    std::cout << "Please enter a number up to " << largest << ".\n>";  //<2>
    double number{};
    std::cin >> number;
    std::cout << number << '\n';
    if(!std::cin.eof() && std::cin.peek()!='\n') //<3>
    {
        std::cout << "Unused input\n";  //<4>
    }

}
