#ifndef PATRICIA_TRIE_HPP
# define PATRICIA_TRIE_HPP

# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
# include <cctype>
# include <algorithm>
# include <string>
# include <map>

# include <boost/archive/binary_oarchive.hpp>
# include <boost/archive/binary_iarchive.hpp>

# include <boost/serialization/map.hpp>
# include <boost/serialization/vector.hpp>

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
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
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
        Node* root = nullptr;
        std::string filename;
        std::vector<char> suffixes;

    private:
        int add(std::string word, int freq, Node* n);
        Node* burstDown(size_t index, size_t i, size_t freq, Node* n);
        void browse(std::string word, Node* n);

private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
	ar & suffixes;
	ar & root;
    }

    public:
    PatriciaTrie(std::string f);
    PatriciaTrie(void);
    ~PatriciaTrie(void);

    public:
    int compile(void);
    void print(void);
};

#endif
