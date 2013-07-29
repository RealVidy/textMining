/**
 * \file
 */

#ifndef PATRICIA_TRIE_HPP
# define PATRICIA_TRIE_HPP

# define CHUNK (16384)
# define BLOCK_SIZE (16)

# include "includes.hpp"

struct Node
{
    typedef std::map<char, Node*> nodeMap;

    nodeMap sons;
    size_t index;
    size_t freq;
    unsigned short length;
    char c;
    bool isWord;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
	{
	    int i = version;
	    i = i;

	    ar & sons;
	    ar & index;
	    ar & freq;
	    ar & length;
	    ar & c;
	    ar & isWord; 
	}

    void print(void);
    Node(size_t index, size_t freq, unsigned short length, char c);
    Node(void);
    ~Node(void);
};


class PatriciaTrie
{
private:
    std::string filename;

private:
    int add(std::string word, int freq, Node* n);
    Node* burstDown(size_t index, size_t i, size_t freq, Node* n);
    void browse(std::string word, Node* n);

public:
    PatriciaTrie(std::string f);
    PatriciaTrie(void);
    ~PatriciaTrie(void);

public:
    int compile(void);
    void print(void);
    Node* root = nullptr;
    std::vector<char> suffixes;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
	{
	    int i = version;
	    i = i;

	    ar & suffixes;
	    ar & root;
	}

private:
    int compress(FILE* souce, FILE* dest, int level);

private:
    std::vector<std::pair<std::vector<int>, std::pair<int, Node*>>> new_trie;
    void deepthFirstSearch(Node *n, int father);

public:
    void createRawFile(std::string filename);

};

#endif
