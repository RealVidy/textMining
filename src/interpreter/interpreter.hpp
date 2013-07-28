#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

#include "../patriciaTrie/patriciaTrie.hpp"
#include <map>

typedef std::vector<std::string> stringVec;

class Interpreter
{
    public:
    Interpreter(std::string file);
    stringVec getResults(int distance, std::string word);

    private:

    void browse(Node* n);
    //size_t getNextWord(Node* n, unsigned short curIndex, unsigned short curDist, std::string& suf, int& i);
    size_t maxDist;
    void getNextWord(Node* n, int i, int j, int dist, std::string curWord);
    std::string word;
    stringVec results;
    PatriciaTrie* p;
};

#endif // !INTERPRETER_HPP
