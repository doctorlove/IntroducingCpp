#include <iostream> //<1>

int main() //<2>
{
    std::cout << "Please enter a number.\n>"; //<3>
    int number{}; //<4>
    std::cin >> number; //<5>
    std::cout << number <<'\n'; //<6>
}
