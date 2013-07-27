#include "../patriciaTrie/patriciaTrie.hpp"

int main(int argc, char** argv)
{
    std::string file;

    if (argc == 2)
        file = std::string(argv[1]);
    else
        file = std::string("dico.bin");

    PatriciaTrie* p;

    std::ifstream istream(file);
    boost::archive::binary_iarchive iar(istream);

    iar >> p;

    p->print();

    delete p;
}
