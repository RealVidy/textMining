#include "interpreter.hpp"

Interpreter::Interpreter(int distance, std::string word, std::string file):
    maxDist(distance), word(word)
{
    std::ifstream istream(file);
    boost::archive::binary_iarchive iar(istream);

    iar >> this->p;
}

void Interpreter::browse(Node* n, std::string curWord, unsigned short curIndex, unsigned short curDist)
{
    for (Node::nodeMap::iterator it = n->sons.begin();
            it != n->sons.end();
            ++it)
    {
        std::string suf("");
        size_t i = 0;
        int res = distance(it->second, curIndex, curDist, suf, i);

        if (res < 0)
            continue;
        if (it->second->isWord && res + word.length() - i - 1 <= maxDist)
            std::cout << curWord + suf << std::endl;

        // Then dist in children
    }

}

stringVec Interpreter::getResults(void)
{
    std::string curWord("");
    unsigned short curIndex = 0;
    unsigned short curDist = 0;

    browse(this->p->root, curWord, curIndex, curDist);

    return this->results;
}

int Interpreter::distance(Node* n, unsigned short curIndex, unsigned short curDist, std::string& suf, size_t& i)
{
    int dist = 0;
    char c;

    if (n->c != this->word[curIndex])
        ++dist;
        
    suf += n->c;
    for (; (i < n->length) && (curIndex + i < this->word.length()) &&
            (curDist + dist < maxDist); ++i)
    {
        c = p->suffixes[n->index + i];
        if (c != this->word[curIndex + i + 1])
            ++dist;
        suf += c;
    }

    if (curDist + dist > maxDist)
        return -1;

    return dist;
}

