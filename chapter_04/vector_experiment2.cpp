#include <iostream>
#include <vector>

void vector_insert()
{
    std::vector<int> numbers{0, 1};
    auto iterator = numbers.begin(); //<1>
    numbers.insert(++iterator, -123); //<2>
    for(const auto & number: numbers)
    {
        std::cout << number << '\n';
    }
}

int main()
{
    vector_insert();
}


