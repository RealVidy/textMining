#include "../headers/interpreter.hpp"

#define MIN(a, b)(a < b ? a : b)
#define MAX(a, b)(a > b ? a : b)

Interpreter::Interpreter(std::string file)
{
    std::cerr << "Loading begin" << std::endl;
    loadData(file);
    std::cerr << "Loading done" << std::endl;
}

void Interpreter::getResults(const unsigned short dist, const std::string word)
{
    numBreak = 0;
    maxDist = dist;
    this->word = word;

    results.clear();

    std::string curWord("");

    curWord.resize(BUFFER_SIZE);

    //  std::cerr << " -> " << pNode[0].nbSons << std::endl << std::endl;

    size_t acu = pNode[0].nbSons;
    for (int i = 0; i < pNode[0].nbSons; i++)
    {
        //	std::cerr << "-> " << pNode[pSons[i]].no << std::endl;
        //	std::cerr << "-> " << pNode[pSons[i]].length << std::endl;
        //	std::cerr << "-> " << pNode[pSons[i]].index << std::endl;
        //	std::cerr << "-> " << pNode[pSons[i]].nbSons << std::endl;
        //	std::cerr << std::endl;
        getWord(pNode[pSons[i]], curWord, 0, acu);
    }

    std::list<Result>::const_iterator it = results.begin();
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

void Interpreter::getWord(const dataNode& n, std::string& curWord, size_t index, size_t& acu)
{
    int tmpDist = 0;

    //    std::cerr << acu << " " << numBreak << " " << n.no << std::endl;

    if (numBreak > 0)
    {
        if ((int) n.no < numBreak + 1)
        {
            std::cerr << "OH SHIT" << std::endl;
        }

        acu += (int) n.no - numBreak - 1;
        numBreak = 0;
    }

    curWord[index++] = n.c;

    //    std::cerr << "1- "<< curWord.substr(0, index) << " " << n.length << " " << n.no << " " << acu << std::endl;
    for (size_t i = 0; i < n.length; ++i)
        curWord[index++] = pSuffixes[n.index + i];

    //  std::cerr << "2- "<< curWord.substr(0, index) << std::endl;

    if (n.isWord)
    {
        unsigned short myDist = distance(word, curWord, index);
        if (myDist <= maxDist)
            insertionSort(curWord, myDist, n.freq, index);
    }

    if (word.length() > index)//curWord.length())
    {
        // Prefix already too far?
        std::string tmp = word.substr(0, index);//curWord.length());
        if ((tmpDist = distance(tmp, curWord, index)) > maxDist && 
                tmpDist - LCS(word.substr(0, index + 1), curWord, index, tmpDist - maxDist) > maxDist)
        {
            numBreak = n.no;
            return;
        }
    }
    else
    {
        if ((tmpDist = distance(word, curWord, index)) > maxDist &&
                tmpDist - LCS(word, curWord, index, tmpDist - maxDist) > maxDist)
        {
            numBreak = n.no;
            return;
        }
    }

    size_t tmp = acu;
    acu += n.nbSons;

    for (int i = 0; i < n.nbSons; i++)
        getWord(pNode[pSons[i + tmp]], curWord, index, acu);
}

int Interpreter::distance(const std::string& truncWord, const std::string& curWord, const size_t index)
{
    const int lenStr1 = truncWord.length();
    const int lenStr2 = index;
    int i, j, cost;

    //for loop is inclusive, need table 1 row/column larger than string length.
    for (i = 0; i <= lenStr1; ++i)
        d[i][0] = i;
    for (j = 0; j <= lenStr2; ++j)
        d[0][j] = j;
    for (i = 1; i <= lenStr1; ++i)
        for (j = 1; j <= lenStr2; ++j)
        {
            if (truncWord[i - 1] == curWord[j - 1])
                cost = 0;
            else
                cost = 1;

            d[i][j] = MIN(d[i-1][j] + 1, // deletion
                    MIN(d[i][j-1] + 1,     // insertion
                        d[i-1][j-1] + cost));   // substitution

            if(i > 1 && j > 1 && truncWord[i - 1] == curWord[j-2] && truncWord[i-2] == curWord[j - 1])
                d[i][j] = MIN(d[i][j], d[i-2][j-2] + cost);  // transposition
        }

    int result = d[lenStr1][lenStr2];

    return result;
}

void Interpreter::insertionSort(std::string myWord,
        const unsigned short distance, const size_t freq, const size_t index)
{
    std::list<Result>::iterator it = results.begin();
    myWord.resize(index);
    //std::cerr << myWord << std::endl;
    Result newRes(myWord, distance, freq);

    for (; it != results.end() && newRes != *it && *it < newRes; ++it);

    if (it != results.end() && newRes == *it)
    {
        if (distance < it->distance)
            it->distance = distance;
    }
    else
        results.insert(it, newRes);
}

int Interpreter::LCS(const std::string& str1, const std::string& str2,
        const size_t index, const size_t limit)
{
    size_t res;
    size_t k;

    for (size_t i = 0; i < str1.length(); ++i)
    {
        res = 0;
        k = i;

        for (size_t j = 0; j < index && k < str1.length(); ++j)
        {
            if (str1[k] == str2[j])
            {
                ++res;
                ++k;
            }
            if (res >= limit)
                return res;
        }
    }

    return 0;
}

void print_extract_data(Header* pHeader, char* pSuffixes,
        dataNode* pNode, int* pSons)
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
        for (int j = 0; j < pNode[i].nbSons; j++)
            std::cout << pSons[fact + j] << " ";
        fact += pNode[i].nbSons;
        std::cout << std::endl << std::endl;;
    }
}


void Interpreter::loadData(std::string filename)
{
    struct stat st;
    stat(filename.c_str(), &st);
    int filesize = st.st_size;
    int fd = -1;
    unsigned char* pFile = NULL;

    fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    pFile = (unsigned char*) mmap(0, filesize,
            PROT_READ, MAP_STACK | MAP_SHARED | MAP_POPULATE, fd, 0);

    if (pFile == MAP_FAILED)
    {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    pHeader = (Header*) pFile;
    pSuffixes = (char*) (pFile + pHeader->suffixes_offset);
    pNode = (dataNode*) (pFile + pHeader->trie_offset);
    size_t padding = (pHeader->nb_suffixes % 4) == 0 ? 0 : 4 - (pHeader->nb_suffixes % 4);
    pSons = (int*) (pFile + sizeof(Header) + padding + 
            pHeader->nb_suffixes * sizeof(char) + 
            pHeader->nb_node * sizeof(dataNode));

    //    print_extract_data(pHeader, pSuffixes, pNode, pSons);
}
