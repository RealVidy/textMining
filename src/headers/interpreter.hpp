#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

# include "includes.hpp"
# include "patriciatrie.hpp"

typedef std::map<std::string, std::pair<unsigned short, size_t>> resMap;

class Interpreter
{
    private:
    std::string filename;
    Node* root = nullptr;

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

private:
    int decompress(FILE* sources, FILE* dst);

public:
    void loadData(std::string filename);
};

#endif // !INTERPRETER_HPP
