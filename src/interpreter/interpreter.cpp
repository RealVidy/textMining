#include "interpreter.hpp"

#define MIN(a, b)(a < b ? a : b)

Interpreter::Interpreter(std::string file) : filename (file)
{
}

stringVec Interpreter::getResults(int distance, std::string word)
{
    maxDist = distance;
    this->word = word;

    browse(this->p->root);

    return this->results;
}

void Interpreter::browse(Node* n)
{
    for (Node::nodeMap::iterator it = n->sons.begin();
            it != n->sons.end();
            ++it)
        getNextWord(it->second, 0, 0, 0, "");
}

size_t myMin(size_t dist1, size_t dist2, size_t dist3)
{
    return MIN(dist1, MIN(dist2, dist3));
}

// Current node,i: index word in node, j: index in word searched, distance
void Interpreter::getNextWord(Node* n, int i, int j, int dist, std::string curWord)
{
    if (dist > maxDist || (int)(n->length + 1 - word.length()) > (int)maxDist)
        return;

    // Stop case
    if (i > n->length || j > word.length())
    {
        std::string accWord("");
        accWord += n->c;
        for (size_t a = 0; a < n->length; ++a)
            accWord += p->suffixes[n->index + a];
        if (n->isWord && dist + word.length() - j <= maxDist && dist + n->length - i + 1 <= maxDist)
            std::cout << curWord + accWord << std::endl;

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

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source))
	{
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;
	
	do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            
	    switch (ret)
	    {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = CHUNK - strm.avail_out;

            if (fwrite(out, 1, have, dest) != have || ferror(dest))
	    {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
	} while (strm.avail_out == 0);
    } while (ret != Z_STREAM_END);

    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

void Interpreter::loadData(std::string filename)
{
    std::ifstream file(filename);
    std::string content;

    file >> content;

    std::cout << content << std::endl;
}
