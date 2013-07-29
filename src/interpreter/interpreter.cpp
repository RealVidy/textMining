#include "interpreter.hpp"

#define MAX(a, b)(a > b ? a : b)

Interpreter::Interpreter(std::string file)
{
    std::ifstream istream(file);
    boost::archive::binary_iarchive iar(istream);

    iar >> this->p;
}

void Interpreter::getResults(unsigned short distance, std::string word)
{
    maxDist = distance;
    this->word = word;

    browse(this->p->root);

    for (auto& r : results)
        std::cout << r.first << " Distance: " << r.second.first <<
            " Frequency: " << r.second.second << std::endl;
}

void Interpreter::browse(Node* n)
{
    for (Node::nodeMap::iterator it = n->sons.begin();
            it != n->sons.end();
            ++it)
        getNextWord(it->second, 0, 0, 0, "");
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
            unsigned short myDist = MAX(dist1, dist2);
            std::string myWord = curWord + accWord;
            resMap::iterator it;

            if ((it = results.find(myWord)) == results.end() || it->second.first > myDist)
                results[myWord] = std::pair<unsigned short, size_t>(myDist, n->freq);
        }

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

