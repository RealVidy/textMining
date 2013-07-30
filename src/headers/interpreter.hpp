#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

# include "includes.hpp"
# include "patriciatrie.hpp"

#include <list>

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
    unsigned short maxDist;
    void insertionSort(std::string& word, unsigned short distance, size_t freq);
    void getWord(Node* n, std::string curWord);
    int distance(std::string& truncWord, std::string& curWord);
    std::string word;
    std::list<Result> results;
    PatriciaTrie* p;

private:
    int decompress(FILE* sources, FILE* dst);

public:
    void loadData(std::string filename);
};

#endif // !INTERPRETER_HPP
