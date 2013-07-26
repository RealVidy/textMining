#ifndef PATRICIA_TRIE_HPP
# define PATRICIA_TRIE_HPP

# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
# include <cctype>
# include <algorithm>
# include <string>
# include <unordered_map>

struct Node
{
    typedef std::unordered_map<char, Node*> nodeMap;

    nodeMap sons;
    size_t index;
    size_t freq;
    unsigned short length;
    char c;
    bool isWord;

    void print(void);
    Node(size_t index, size_t freq, unsigned short length, char c);
    Node(void);
};


class PatriciaTrie
{
    private:
        Node* root = nullptr;
        std::string filename;
        std::vector<char> suffixes;

    private:
        int add(std::string word, int freq, Node* n);
        Node* burstDown(size_t index, size_t i, size_t freq, Node* n);
        void browse(std::string word, Node* n);

    public:
        PatriciaTrie(std::string f);
        ~PatriciaTrie();

    public:
        int compile(void);
        void print(void);
};

#endif
