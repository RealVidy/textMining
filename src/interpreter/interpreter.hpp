#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

#include "../patriciaTrie/patriciaTrie.hpp"

typedef std::vector<std::string> stringVec;

class Interpreter
{
    public:
    Interpreter(int distance, std::string word, std::string file);
    stringVec getResults(void);

    private:

    void browse(Node* n, std::string curWord, unsigned short curIndex, unsigned short curDist);
    int distance(Node* n, unsigned short curIndex, unsigned short curDist, std::string& suf, int& i);
    int maxDist;
    std::string word;
    stringVec results;
    PatriciaTrie* p;
};

#endif // !INTERPRETER_HPP
