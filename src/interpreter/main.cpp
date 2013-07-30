#include "../headers/interpreter.hpp"

int main(int argc, char** argv)
{
    int nul;
    const rlim_t lRamSize = 1024 * 1024 * 512;
    struct rlimit rl;

    nul = getrlimit(RLIMIT_DATA, &rl);
    nul = nul;

    rl.rlim_max = lRamSize;
    setrlimit(RLIMIT_DATA, &rl);

    std::string file;
    std::string drop;
    int distance;
    std::string word;

    if (argc == 2)
        file = std::string(argv[1]);
    else
        file = std::string("dico.bin");

    Interpreter* inter = new Interpreter(file);

//    inter->loadData(file);


    while (std::cin >> drop >> distance >> word)
        inter->getResults(distance, word);

    delete inter;
}
