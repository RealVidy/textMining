#include "interpreter.hpp"

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

    std::cin >> drop >> distance >> word;

    Interpreter* inter = new Interpreter(distance, word, file);

    inter->getResults();

    delete inter;
}
