/**
 * \file interpreter.hpp
 * \brief Structures pour le Patricia Trie
 * \author Florian Thommains, Victor Degliame
 * \date 31/07/2013
 */

#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

# include "patriciatrie.hpp"

# include <list>

# define BUFFER_SIZE 256

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
private:
    int numBreak;
    Header* pHeader;
    char* pSuffixes;
    dataNode* pNode;
    int* pSons;

    public:
    Interpreter(std::string file);
    ~Interpreter(){};
    void getResults(const unsigned short distance, const std::string word);

    private:
    void insertionSort(const std::string word, const unsigned short distance,
            const size_t freq, const size_t index);
    void getWord(const dataNode& n, std::string& curWord, size_t index, size_t& acu);
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
