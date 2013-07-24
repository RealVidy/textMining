#ifndef PATRICIA_TRIE_HPP
# define PATRICIA_TRIE_HPP

# include <vector>
# include <iostream>
# include <fstream>
# include <cctype>

struct node {
    node* sons[36] = {nullptr};
    int index;
    int freq;
    short length;
    char c;

    node(int index, int freq, int length, char c);
};

class PatriciaTrie
{
    private:
        node* root = nullptr;
        std::string filename;
        std::vector<char> suffixes;

    private:
        int add(std::string word, int freq, node* n);
        int burstDown(int index, int freq, node* n);

    public:
        PatriciaTrie(std::string f);
        ~PatriciaTrie();

    public:
        int compile(void);
};

#endif
