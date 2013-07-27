#include "patriciaTrie/patriciaTrie.hpp"

int main(int argc, char** argv)
{
    std::string file;

    if (argc == 2)
        file = std::string(argv[1]);
    else
        file = std::string("wTest.txt");

    PatriciaTrie *p = new PatriciaTrie(file);

    p->compile();

    std::ofstream ostream("dico.bin");
    boost::archive::binary_oarchive oar(ostream);

    oar << p;
    
    delete(p);
    ostream.close();

    return 0;
}
