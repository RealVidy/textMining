#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

#include "../patriciaTrie/patriciaTrie.hpp"

typedef std::map<std::string, std::pair<unsigned short, size_t>> resMap;

class Interpreter
{
    public:
    Interpreter(std::string file);
    void getResults(unsigned short distance, std::string word);

    private:

    void browse(Node* n);
    unsigned short maxDist;
    void getNextWord(Node* n, unsigned short i, unsigned short j, unsigned short dist, std::string curWord);
    std::string word;
    resMap results;
    PatriciaTrie* p;
};

#endif // !INTERPRETER_HPP
