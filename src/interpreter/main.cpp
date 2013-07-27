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

    std::cout << distance << " " << word << std::endl;

    PatriciaTrie* p;

    std::ifstream istream(file);
    boost::archive::binary_iarchive iar(istream);

    iar >> p;

    p->print();

    delete p;
}
