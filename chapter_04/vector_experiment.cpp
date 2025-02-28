#include <iostream> //<1>
#include <vector>  //<2>

void vector_experiment()
{
    std::vector numbers{0, 1}; //<3>
    for(const auto & number: numbers)  //<4>
    {
        std::cout << number << '\n'; //<5>
    }
}

int main()
{
    vector_experiment();
}


