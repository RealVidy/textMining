#include "../headers/interpreter.hpp"

#define MIN(a, b)(a < b ? a : b)
#define MAX(a, b)(a > b ? a : b)

Interpreter::Interpreter(std::string file)
{
    std::ifstream istream(file);
    boost::archive::binary_iarchive iar(istream);

    iar >> this->p;

    std::cerr << "Loading done" << std::endl;
    /*
    std::string tmp("minc");
    std::string tmp2("mbia");
    std::cerr << LCS(tmp, tmp2, tmp2.length()) << " " << distance(tmp, tmp2, tmp2.length()) << std::endl;

    tmp = std::string("mince");
    tmp2 = std::string("mbiance");
    std::cerr << LCS(tmp, tmp2, tmp2.length()) << " " << distance(tmp, tmp2, tmp2.length()) << std::endl;
    */
    istream.close();
}

void Interpreter::getResults(const unsigned short dist, const std::string word)
{
    maxDist = dist;
    this->word = word;

    results.clear();

    std::string curWord("");

    curWord.resize(BUFFER_SIZE);

    for (Node::nodeMap::iterator it = this->p->root->sons.begin();
            it != this->p->root->sons.end();
            ++it)
        getWord(it->second, curWord, 0);

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
 
void Interpreter::getWord(const Node* n, std::string& curWord, size_t index)
{
    int tmpDist = 0;

    curWord[index ++] = n->c;

    for (size_t i = 0; i < n->length; ++i)
        curWord[index++] = p->suffixes[n->index + i];

    if (n->isWord)
    {
        unsigned short myDist = distance(word, curWord, index);
        if (myDist <= maxDist)
            insertionSort(curWord, myDist, n->freq, index);
    }

    if (word.length() > index)//curWord.length())
    {
        // Prefix already too far?
        std::string tmp = word.substr(0, index);//curWord.length());
        if ((tmpDist = distance(tmp, curWord, index)) > maxDist && 
                tmpDist - LCS(word.substr(0, index + 1), curWord, index, tmpDist - maxDist) > maxDist)
        {
            /*
            std::cerr << tmp << " " << curWord.substr(0, index) << " " <<
                distance(tmp, curWord, index) << " " << LCS(tmp, curWord, index) << " " <<
                distance(tmp, curWord, index) - LCS(tmp, curWord, index) << std::endl;
                */
            return;
        }
    }
    else
    {
        if ((tmpDist = distance(word, curWord, index)) > maxDist &&
                tmpDist - LCS(word, curWord, index, tmpDist - maxDist) > maxDist)
        {
            /*
            std::cerr << word << " " << curWord.substr(0, index) << " " <<
                distance(word, curWord, index) << " " << LCS(word, curWord, index) << " " <<
               distance(word, curWord, index) - LCS(word, curWord, index) << std::endl;
               */
            return;
        }
    }

    for (Node::nodeMap::const_iterator it = n->sons.begin();
            it != n->sons.end();
            ++it)
        getWord(it->second, curWord, index);
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
    //Pseudo-code assumes string indices start at 1, not 0.
    //If implemented, make sure to start comparing at 1st letter of strings.
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


/*

   int Interpreter::decompress(FILE* source, FILE* dest)
   {
   int ret;
   unsigned have;
   z_stream strm;
   unsigned char in[CHUNK];
   unsigned char out[CHUNK];

// allocate inflate state
strm.zalloc = Z_NULL;
strm.zfree = Z_NULL;
strm.opaque = Z_NULL;
strm.avail_in = 0;
strm.next_in = Z_NULL;
ret = inflateInit(&strm);
if (ret != Z_OK)
return ret;

//decompress until deflate stream ends or end of file 
do {
strm.avail_in = fread(in, 1, CHUNK, source);
if (ferror(source)) {
(void)inflateEnd(&strm);
return Z_ERRNO;
}
if (strm.avail_in == 0)
break;
strm.next_in = in;

// run inflate() on input until output buffer not full 
do {
strm.avail_out = CHUNK;
strm.next_out = out;
ret = inflate(&strm, Z_NO_FLUSH);
assert(ret != Z_STREAM_ERROR);  // state not clobbered 
switch (ret) {
case Z_NEED_DICT:
ret = Z_DATA_ERROR;     // and fall through 
case Z_DATA_ERROR:
case Z_MEM_ERROR:
(void)inflateEnd(&strm);
return ret;
}
have = CHUNK - strm.avail_out;
if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
(void)inflateEnd(&strm);
return Z_ERRNO;
}
} while (strm.avail_out == 0);

// done when inflate() says it's done 
} while (ret != Z_STREAM_END);

// clean up and return 
(void)inflateEnd(&strm);
return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}
*/

void Interpreter::loadData(std::string filename)
{
    int nul = 0;

    /*
       struct stat st;
       stat(filename.c_str(), &st);
       size_t map_size = st.st_size;
       */
    /*
       FILE* in = fopen(filename.c_str(), "r+");
       std::string file_uncompress = filename + "_uncompress";
       FILE* out = fopen(file_uncompress.c_str(), "r+");

       decompress(in, out);
       */


    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1)
    {
        std::cerr << "Error opening file for reading" << std::endl;
        exit(-1);
    }

    // Get metadata
    size_t metadata[3];;

    nul = read(fd, metadata, sizeof(size_t) * 3);

    // Print metadata
    // 1: taille des suffixes
    // 2: offset des suffixes
    // 3: offset root trie
    std::cout << " -- METADATA -- " << std::endl;
    for (size_t i : metadata)
        std::cout << "> " << i << std::endl;

    // Get Suffixes
    char *suffixies = (char*) malloc(sizeof(char) * metadata[0]);

    nul = lseek(fd, metadata[1], SEEK_SET);
    std::cout << "SEEK_CUR: " << nul << std::endl;

    nul = read(fd, suffixies, metadata[0]);

    std::cout << " -- SUFFIXIES -- " << std::endl;
    for (size_t i = 0; i < metadata[0]; i++)
        std::cout << *(suffixies + i) << " ";
    std::cout << std::endl;

    // Get root
    dataNode* root = (dataNode*) malloc(sizeof(dataNode));

    //nul = fseek(file, , SEEK_CUR);
    std::cout <<"SEEK_CUR: " << lseek(fd, 41, SEEK_SET) << std::endl;
    nul = read(fd, root, sizeof(dataNode));

    std::cout << " -- ROOT -- " << std::endl;
    std::cout << "> Index: " << root->index << std::endl;
    std::cout << "> Frequence: " << root->freq << std::endl;
    std::cout << "> Length: " << root->length << std::endl;
    std::cout << "> Char: " << root->c << std::endl;
    std::cout << "> Is word: " << root->isWord << std::endl;
    std::cout << "> Nb suns: " << root->nbSons << std::endl;

    // Clear memmory


    // To supress unused error
    nul = nul;

    free(suffixies);
    free(root);
    close(fd);
}
