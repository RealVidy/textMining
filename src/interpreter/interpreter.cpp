#include "interpreter.hpp"

Interpreter::Interpreter(int distance, std::string word):
    maxDist(distance), word(word)
{
    std::ifstream istream(file);
    boost::archive::binary_iarchive iar(istream);

    iar >> this->p;

    this->p->print();
}

stringVec Interpreter::getResults(void)
{
    std::string currentWord("");
    unsigned short curIndex = 0;
    unsigned short curDist = 0;

    for (Node::nodeMap::iterator it = p->root->sons.begin();
            it != p->root->sons.end();
            ++it)
    {
        std::cout << distance(it->second, curIndex, curDist) << std::endl;
    }

    return this->results;
}

int Interpreter::distance(Node* n, unsigned short curIndex, unsigned short curDist)
{
    int dist = 0;
    size_t i = 0;

    if (n->c != this->word[curIndex])
        ++dist;
        
    for (; (i < n->length) && (curIndex + i < this->word.length()) &&
            (curDist + dist < this->maxDist); ++i)
    {
        if (p->suffixes[n->index + i] != this->word[curIndex + i])
            ++dist;
    }

    return (dist + this->word.length() - i)
}

/*
void Interpreter::browse(stringVec& r, Node* n, std::string curW, unsigned short curDist, unsigned short curIndex)
{

}
*/
