#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

#include "../patriciaTrie/patriciaTrie.hpp"

typedef std::vector<std::string> stringVec;

class Interpreter
{
    public:
    Interpreter(int distance, std::string word);
    stringVec getResults(void);

    private:

    void browse(stringVec& r, Node* n, std::string curW, unsigned short curDist,
            , unsigned short curIndex);

    int distance(Node* n, unsigned short curIndex, unsigned short curDist);
    int maxDist;
    std::string word;
    stringVec results;
    PatriciaTrie* p;
};

#endif // !INTERPRETER_HPP
