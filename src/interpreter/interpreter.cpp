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

