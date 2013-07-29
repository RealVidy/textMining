#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

# include "includes.hpp"
# include "patriciatrie.hpp"

#include <list>

typedef std::map<std::string, std::pair<unsigned short, size_t>> resMap;

class Result
{
    public:
        Result(std::string word, unsigned short distance, size_t freq):
            word(word),
            distance(distance),
            freq(freq)
    {
    }
        bool operator<(Result& rhs)
        {
            return ((distance < rhs.distance) ||
                    (distance == rhs.distance && freq > rhs.freq) ||
                    (distance == rhs.distance && freq == rhs.freq && word < rhs.word));
        }

        bool operator==(Result& rhs)
        {
            return (word == rhs.word);
        }

        bool operator!=(Result& rhs)
        {
            return !(*this == rhs);
        }

        std::string word;
        unsigned short distance;
        size_t freq;
};

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
    void insertionSort(std::string& word, unsigned short distance, size_t freq);
    std::string word;
    std::list<Result> results;
    PatriciaTrie* p;

private:
    int decompress(FILE* sources, FILE* dst);

public:
    void loadData(std::string filename);
};

#endif // !INTERPRETER_HPP
