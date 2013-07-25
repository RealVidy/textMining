#ifndef PATRICIA_TRIE_HPP
# define PATRICIA_TRIE_HPP

# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
# include <cctype>
# include <algorithm>
# include <string>

struct node {
    node* sons[36] = {nullptr};
    size_t index;
    unsigned short freq;
    unsigned short length;
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
        node* burstDown(size_t index, size_t i, unsigned short freq, node* n);

    public:
        PatriciaTrie(std::string f);
        ~PatriciaTrie();

    public:
        int compile(void);
};

#endif
