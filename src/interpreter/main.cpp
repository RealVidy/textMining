#include "../headers/interpreter.hpp"

int main(int argc, char** argv)
{
    std::string file;
    std::string drop;
    int distance;
    std::string word;

    if (argc == 2)
        file = std::string(argv[1]);
    else
        file = std::string("dico.bin");


    Interpreter* inter = new Interpreter(file);

    inter->loadData("test");

    while (std::cin >> drop >> distance >> word)
        inter->getResults(distance, word);

    delete inter;
}
