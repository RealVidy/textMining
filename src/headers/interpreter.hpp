#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

# include "includes.hpp"
# include "patriciatrie.hpp"

# include <list>

# define BUFFER_SIZE 512

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
    void insertionSort(const std::string word, const unsigned short distance,
            const size_t freq, const size_t index);
    void getWord(const Node* n, std::string& curWord, size_t index);
    int distance(const std::string& truncWord, const std::string& curWord, const size_t index);
    int LCS(const std::string& str1, const std::string& str2,
            const size_t index, const size_t limit);

    unsigned short maxDist;
    std::string word;
    std::list<Result> results;
    PatriciaTrie* p;
    Node* root = nullptr;

private:
    int decompress(FILE* sources, FILE* dst);
    int d[BUFFER_SIZE][BUFFER_SIZE];
    //int currArray[BUFFER_SIZE];
    //int prevArray[BUFFER_SIZE];

public:
    void loadData(std::string filename);
};

#endif // !INTERPRETER_HPP
