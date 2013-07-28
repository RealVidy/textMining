#include "interpreter.hpp"

#define MIN(a, b)(a < b ? a : b)

Interpreter::Interpreter(std::string file)
{
    std::ifstream istream(file);
    boost::archive::binary_iarchive iar(istream);

    iar >> this->p;
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


