#include "patriciaTrie.hpp"

int main(int argc, char** argv)
{
    std::string file, out;

    if (argc == 3)
    {
        file = std::string(argv[1]);
	out = std::string(argv[2]);
    }
    else
	std::cerr << "Error - Invalid usage './TextMiningCompiler inputFile outputFile'" << std::endl;

    PatriciaTrie *p = new PatriciaTrie(file);

    p->compile();

    std::ofstream ostream(out);
    boost::archive::binary_oarchive oar(ostream);

    oar << p;
    
    delete(p);
    ostream.close();

    return 0;
}
