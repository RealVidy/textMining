#include "../headers/interpreter.hpp"

#define MAX(a, b)(a > b ? a : b)

Interpreter::Interpreter(std::string file) : filename (file)
{
    std::ifstream istream(file);
    boost::archive::binary_iarchive iar(istream);

    iar >> this->p;

    istream.close();
}

void Interpreter::getResults(unsigned short distance, std::string word)
{
    maxDist = distance;
    this->word = word;

    browse(this->p->root);
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

void Interpreter::browse(Node* n)
{
    for (Node::nodeMap::iterator it = n->sons.begin();
            it != n->sons.end();
            ++it)
        getNextWord(it->second, 0, 0, 0, "");
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

// Current node,i: index word in node, j: index in word searched, distance
void Interpreter::getNextWord(Node* n, unsigned short i, unsigned short j, unsigned short dist, std::string curWord)
{
    if (dist > maxDist || (int)n->length + 1 - (int)word.length() > (int)maxDist)
        return;

    // Stop case
    if (i > n->length || j > word.length())
    {
        std::string accWord("");
        accWord += n->c;
        for (unsigned short a = 0; a < n->length; ++a)
            accWord += p->suffixes[n->index + a];
        
        unsigned short dist1 = dist + word.length() - j;
        unsigned short dist2 = dist + n->length - i + 1;

        if (n->isWord && dist1 <= maxDist && dist2 <= maxDist)
        {
            // Insert Result
            unsigned short myDist = MAX(dist1, dist2);
            std::string myWord = curWord + accWord;
            std::list<Result>::iterator it;

            insertionSort(myWord, myDist, n->freq);
        }

        // Do we have to look in the sons?
        if (i > n->length)
            for (Node::nodeMap::iterator it = n->sons.begin();
                it != n->sons.end();
                ++it)
                getNextWord(it->second, 0, j, dist, curWord + accWord);

        return;
    }

    // If i == 0 we must look at n->c, otherwise, suffixes
    if ((i == 0 && n->c != word[j]) ||
            (i > 0 && p->suffixes[n->index + i - 1] != word[j]))
    {
        // Substitution
        getNextWord(n, i + 1, j + 1, dist + 1, curWord);
        // Insertion
        getNextWord(n, i, j + 1, dist + 1, curWord);
        // Suppression
        getNextWord(n, i + 1, j, dist + 1, curWord);
    }
    else
        getNextWord(n, i + 1, j + 1, dist, curWord); // equal letters
}

/*
   size_t Interpreter::getNextWord(Node* n, unsigned short curIndex, unsigned short curDist, std::string& suf, int& i)
   {
   int dist = 0;
   int insertDist = 0;
   std::string sufString;
   char c;

   if (n->c != this->word[curIndex])
   ++dist;

   suf += n->c;
   for (; (i < (int)n->length) && (curIndex + i < (int)this->word.length()) &&
   (curDist + dist <= maxDist); ++i)
   {
   c = p->suffixes[n->index + i];
   if (c != this->word[curIndex + i + 1])
   ++dist;
   suf += c;
   }

   for (size_t j = i; j < n->length; ++j)
   suf += p->suffixes[n->index + j];

   if (curDist + dist + n->length - i > maxDist)
   return maxDist + 1;

   return dist + n->length - i;
   }

*/


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
    int size_header = 3;
    size_t *metadata;
    int nul = 0;

    struct stat st;
    stat(filename.c_str(), &st);
    size_t map_size = st.st_size;


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
    metadata = static_cast<size_t*>(mmap(NULL, map_size,
					PROT_READ, MAP_SHARED,
					fd, 0));
    if (metadata == MAP_FAILED)
    {
	close(fd);
	std::cerr << "Error mmapping the file" << std::endl;
	exit(-1);
    }
    
    std::cout << "-- Metadatas -- " << std::endl;
    for (int i = 0; i < size_header; i++)
	printf("%d: %d\n", i, metadata[i]);

    // Get suffixes array
    char* suffixes = (char *) malloc(sizeof(char) * 18);

    nul = lseek(fd, metadata[1], SEEK_CUR);
    nul = read(fd, suffixes, metadata[0]);

    std::cout << "-- Suffixes -- "<< std::endl;
    for (size_t i = 0; i < metadata[0]; i++)
	printf("%d: %c\n", i, suffixes[i]);

    // Get patricia trie root
    int *index = (int*) malloc(sizeof(int));

    nul = lseek(fd,  metadata[2], SEEK_CUR);
    nul = read(fd, index, sizeof(int));

    nul = nul;

    printf("0: %i\n", *index);

    // Get
    // Free maps
    free(suffixes);
    free(index);
    munmap(metadata, map_size);

    close(fd);
}
