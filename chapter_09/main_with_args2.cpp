#include <iostream>
#include <string> //<1>

void show_characters_before(const std::string & value, //<2>
        char character) //<3>
{
    auto position = value.find(character); //<4>
    if(position != std::string::npos) //<5>
    {
        std::string partial = value.substr(0, position); //<6>
        std::cout << "Before " << character <<  ": " << partial<< '\n'; //<7>
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
        show_characters_before(argv[i], '/'); //<8>
        show_characters_before(argv[i], '\\'); //<9>
    }
}
