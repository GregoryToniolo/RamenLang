#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "tokenizer.hpp"
#include "parser.hpp"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "ERROR: Invalid number of arguments!" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "ERROR: Unable to open file: \"" << argv[1] << "\". File does not exist" << std::endl;
        return 2;
    }

    std::ofstream output("output.cpp", std::ios::trunc);
    if (!output)
    {
        std::cerr << "ERROR: Unable to open output file!" << std::endl;
        return 3;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<Token> tokens = parse(line);
        printTokens(tokens, output);
    }
    output.close();
    file.close();
    return 0;
}
