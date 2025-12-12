#include <iostream>
#include <string_view> //<1>

void show_characters_before(std::string_view value, //<2>
        char character)
{
    auto position = value.find(character);
    if(position != std::string::npos)
    {
        std::string_view partial = value.substr(0, position);
        std::cout << "Before " << character <<  ": " << partial<< '\n';
    }
    else
    {
        std::cout << character << " not found\n";
    }
}

int main(int argc, char *argv[])
{
    for(int i = 0; i<argc; ++i)
    {
        std::cout << "Argument " << argv[i] << '\n';
        show_characters_before(argv[i], '/'); //<3>
        show_characters_before(argv[i], '\\'); //<4>
    }
}
