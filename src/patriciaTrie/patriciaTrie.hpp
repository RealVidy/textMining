#ifndef PATRICIA_TRIE_HPP
# define PATRICIA_TRIE_HPP

# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
# include <cctype>
# include <algorithm>
# include <string>

struct Node
{
    Node* sons[36] = {nullptr};
    size_t index;
    unsigned short freq;
    unsigned short length;
    char c;
    short nbSons;

    int addNbSons(int n);
    void print(void);
    Node(int index, int freq, int length, char c);
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
        Node* burstDown(size_t index, size_t i, unsigned short freq, Node* n);
        void browse(std::string word, Node* n);

    public:
        PatriciaTrie(std::string f);
        ~PatriciaTrie();

    public:
        int compile(void);
        void print(void);
};

#endif
