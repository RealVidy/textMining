#include "../headers/patriciatrie.hpp"

int main(int argc, char** argv)
{
    int nul;
    const rlim_t lRamSize = 1024 * 1024 * 512;
    struct rlimit rl;

    nul = getrlimit(RLIMIT_DATA, &rl);
    nul = nul;

    rl.rlim_max = lRamSize;
    setrlimit(RLIMIT_DATA, &rl);

    std::string file, out;

    if (argc == 3)
    {
        file = std::string(argv[1]);
	out = std::string(argv[2]);
    }
    else
	std::cerr << "Error - Invalid usage './TextMiningCompiler inputFile outputFile'" << std::endl;

    PatriciaTrie *p = new PatriciaTrie(file);

    p->compile(out);

    delete(p);

    return 0;
}
