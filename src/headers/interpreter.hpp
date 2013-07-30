#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

# include "includes.hpp"
# include "patriciatrie.hpp"

# include <list>

//# include <google/profiler.h>

class Result
{
    public:
        Result(const std::string& word, const unsigned short distance, const size_t freq):
            word(word),
            distance(distance),
            freq(freq)
    {
    }
        bool operator<(const Result& rhs) const
        {
            return ((distance < rhs.distance) ||
                    (distance == rhs.distance && freq > rhs.freq) ||
                    (distance == rhs.distance && freq == rhs.freq && word < rhs.word));
        }

        bool operator==(const Result& rhs) const
        {
            return (word == rhs.word);
        }

        bool operator!=(const Result& rhs) const
        {
            return !(*this == rhs);
        }

        std::string word;
        unsigned short distance;
        size_t freq;
};

class Interpreter
{
    public:
    Interpreter(std::string file);
    void getResults(const unsigned short distance, const std::string word);

    private:
    void insertionSort(const std::string& word, const unsigned short distance, const size_t freq);
    void getWord(const Node* n, std::string curWord);
    int distance(const std::string& truncWord, const std::string& curWord);
    int LCS(const std::string& str1, const std::string& str2);

    unsigned short maxDist;
    std::string word;
    std::list<Result> results;
    PatriciaTrie* p;
    Node* root = nullptr;

private:
    int decompress(FILE* sources, FILE* dst);
    int d[512][512];
    int currArray[512];
    int prevArray[512];

public:
    void loadData(std::string filename);
};

#endif // !INTERPRETER_HPP
