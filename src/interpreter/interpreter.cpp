#include "../headers/interpreter.hpp"

#define MIN(a, b)(a < b ? a : b)
#define MAX(a, b)(a > b ? a : b)
#define ABS(a)(a < 0 ? -a : a)

Interpreter::Interpreter(std::string file) : filename (file)
{
/*    std::ifstream istream(file);
    boost::archive::binary_iarchive iar(istream);

    iar >> this->p;

    std::cerr << "Loading done" << std::endl;

    istream.close();*/
}

void Interpreter::getResults(unsigned short distance, std::string word)
{
    maxDist = distance;
    this->word = word;

    for (Node::nodeMap::iterator it = this->p->root->sons.begin();
            it != this->p->root->sons.end();
            ++it)
        getWord(it->second, "");

    std::list<Result>::iterator it = results.begin();
    std::cout << "[";


    for (size_t i = results.size(); i > 1; ++it, --i)
    {
        std::cout << "{\"word\":\"" << it->word << "\"," <<
            "\"freq\":" << it->freq << ",\"distance\":" << it->distance << "},";
    }

    if (results.size() > 0)
        std::cout << "{\"word\":\"" << it->word << "\"," <<
            "\"freq\":" << it->freq << ",\"distance\":" << it->distance << "}";

    std::cout << "]" << std::endl;
}

int minimum(int a, int b, int c)
{
    return MIN(a, MIN(b, c));
}

int Interpreter::distance(std::string& truncWord, std::string& curWord)
{
    int lenStr1 = truncWord.length();
    int lenStr2 = curWord.length();
    int i, j, cost;

    int **d = new int*[lenStr1 + 1];

    for(int k = 0; k <= lenStr1; ++k)
        d[k] = new int[lenStr2 + 1];

    //for loop is inclusive, need table 1 row/column larger than string length.
    for (i = 0; i <= lenStr1; ++i)
        d[i][0] = i;
    for (j = 0; j <= lenStr2; ++j)
        d[0][j] = j;
    //Pseudo-code assumes string indices start at 1, not 0.
    //If implemented, make sure to start comparing at 1st letter of strings.
    for (i = 1; i <= lenStr1; ++i)
        for (j = 1; j <= lenStr2; ++j)
        {
            if (truncWord[i - 1] == curWord[j - 1])
                cost = 0;
            else
                cost = 1;

            d[i][j] = minimum(d[i-1][j] + 1, // deletion
                    d[i][j-1] + 1,     // insertion
                    d[i-1][j-1] + cost);   // substitution

            if(i > 1 && j > 1 && truncWord[i - 1] == curWord[j-2] && truncWord[i-2] == curWord[j - 1])
                d[i][j] = MIN(d[i][j], d[i-2][j-2] + cost);  // transposition
        }

    int result = d[lenStr1][lenStr2];

    for (int i = 0; i <= lenStr1; ++i)
        delete[] d[i];
    delete[] d;
    return result;
}

void Interpreter::getWord(Node* n, std::string curWord)
{
    /*
       if (ABS((int)word.length() - (int)curWord.length()) > maxDist)
       return;
       */
    curWord += n->c;

    for (size_t i = 0; i < n->length; ++i)
        curWord += p->suffixes[n->index + i];

    if (n->isWord)
    {
        unsigned short myDist = distance(word, curWord);
        if (myDist <= maxDist)
            insertionSort(curWord, myDist, n->freq);
    }
    if (word.length() > curWord.length())
    {
        // Prefix already too far?
        std::string tmp = word.substr(0, curWord.length());
        //std::cout << tmp << std::endl;
        if (distance(tmp, curWord) > maxDist)
            return;
    }

    for (Node::nodeMap::iterator it = n->sons.begin();
            it != n->sons.end();
            ++it)
        getWord(it->second, curWord);
}

void Interpreter::insertionSort(std::string& word, unsigned short distance, size_t freq)
{
    std::list<Result>::iterator it = results.begin();
    Result newRes(word, distance, freq);

    for (; newRes != *it && *it < newRes && it != results.end(); ++it);

    if (it != results.end() && newRes == *it)
    {
        if (distance < it->distance)
            it->distance = distance;
    }
    else
        results.insert(it, newRes);
}

void print_extract_data(Header* pHeader, char* pSuffixes,
		   dataNode* pNode,size_t* pSons)
{
    std::cout << " -- HEADER -- " << std::endl;
    std::cout << "> Nombre de suffixes: " << pHeader->nb_suffixes << std::endl;
    std::cout << "> Offset des suffixes: " << pHeader->suffixes_offset << std::endl;
    std::cout << "> Nombre de node: " << pHeader->nb_node << std::endl;
    std::cout << "> Offset du trie: " << pHeader->trie_offset << std::endl;

    pSuffixes = pSuffixes;
    std::cout << " -- SUFFIXES -- " << std::endl;
    for (size_t i = 0; i < pHeader->nb_suffixes; i++)
	std::cout << (pSuffixes[i]) << " ";
    std::cout << std::endl;

    std::cout << " -- NODES -- " << std::endl;
    int fact = 0;
    for (size_t i = 0; i < pHeader->nb_node; i++)
    {
	std::cout << "> Node " << pNode[i].no << ":" << std::endl;
	std::cout << ">> Frequence: " << pNode[i].freq << std::endl;
	std::cout << ">> Index: " << pNode[i].index << std::endl;
	std::cout << ">> Longeur: " << pNode[i].length << std::endl;
	std::cout << ">> Char: " << pNode[i].c << std::endl;
	std::cout << ">> Is word: " << pNode[i].isWord << std::endl;
	std::cout << ">> Nombre de fils: " << pNode[i].nbSons << std::endl;

	std::cout << ">> Sons: ";
	for (size_t j = 0; j < pNode[i].nbSons; j++)
	    std::cout << pSons[fact + j] << " ";
	fact += pNode[i].nbSons;
	std::cout << std::endl << std::endl;;
    }
pSons = pSons;
}

void Interpreter::loadData(std::string filename)
{
    struct stat st;
    stat(filename.c_str(), &st);
    int filesize = st.st_size;
    int fd = -1;
    unsigned char* pFile = NULL;

    fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
	perror("Error opening file for reading");
	exit(EXIT_FAILURE);
    }

    filesize = lseek(fd, 0, SEEK_END);
    pFile = (unsigned char*)  mmap(0, filesize,
				   PROT_READ,
				   MAP_SHARED, fd, 0);
    if (pFile == MAP_FAILED)
    {
	close(fd);
	perror("Error mmapping the file");
	exit(EXIT_FAILURE);
    }

    Header* pHeader = (Header*) pFile;
    char* pSuffixes = (char*) (pFile + pHeader->suffixes_offset);
    dataNode* pNode = (dataNode*) (pFile + pHeader->trie_offset);
    size_t padding = (pHeader->nb_suffixes % 4) == 0 ? 0 : 4 - (pHeader->nb_suffixes % 4);
    size_t* pSons = (size_t*) (pFile + sizeof(Header) + padding + 
			       pHeader->nb_suffixes * sizeof(char) + 
			       pHeader->nb_node * sizeof(dataNode));

    std::cout << (&pNode[1]) << std::endl;

    pNode = pNode;
    pSons = pSons;
    pSuffixes= pSuffixes;
    pHeader= pHeader;
    print_extract_data(pHeader, pSuffixes, pNode, pSons); 
}
