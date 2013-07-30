#include "../headers/interpreter.hpp"

#define MIN(a, b)(a < b ? a : b)
#define MAX(a, b)(a > b ? a : b)
#define ABS(a)(a < 0 ? -a : a)

Interpreter::Interpreter(std::string file) : filename (file)
{
    std::ifstream istream(file);
    boost::archive::binary_iarchive iar(istream);

    iar >> this->p;

    std::cerr << "Loading done" << std::endl;

    istream.close();
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

int Interpreter::distance(std::string curWord)
{
    int lenStr1 = word.length();
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
            if (word[i - 1] == curWord[j - 1])
                cost = 0;
            else
                cost = 1;

            d[i][j] = minimum(d[i-1][j] + 1, // deletion
                              d[i][j-1] + 1,     // insertion
                              d[i-1][j-1] + cost);   // substitution

                if(i > 1 && j > 1 && word[i - 1] == curWord[j-2] && word[i-2] == curWord[j - 1])
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
        unsigned short myDist = distance(curWord);
        if (myDist <= maxDist)
            insertionSort(curWord, myDist, n->freq);
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

int Interpreter::decompress(FILE* source, FILE* dest)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;     /* and fall through */
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

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

void Interpreter::loadData(std::string filename)
{
    int fd;
    int nul = 0;
    FILE* file = fopen(filename.c_str(), "r+");

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

    fd = open(filename.c_str(), O_RDONLY);
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

    nul = fseek(file, metadata[1], SEEK_CUR);
    nul = read(fd, suffixies, metadata[0]);

    std::cout << " -- SUFFIXIES -- " << std::endl;
    for (size_t i = 0; i < metadata[0]; i++)
	std::cout << *(suffixies + i) << " ";
    std::cout << std::endl;

    // Get root
    dataNode* root = (dataNode*) malloc(sizeof(dataNode));

    //nul = fseek(file, , SEEK_CUR);
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
    fclose(file);
    close(fd);
}
