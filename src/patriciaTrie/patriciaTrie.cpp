#include "patriciaTrie.hpp"

PatriciaTrie::PatriciaTrie(std::string f) : filename (f)
{
    root = new Node();
}

PatriciaTrie::~PatriciaTrie()
{
}

Node::Node(size_t index, size_t freq, unsigned short length, char c): isWord(false)
{
    this->index = index;
    this->freq = freq;
    this->length = length;
    this->c = c;
}

Node::Node(void): index(0), freq(0), length(0), c(0), isWord(false)
{
}

void Node::print(void)
{
    std::cout << "index " << index << " freq " << freq << " length " << length << " c " << c << std::endl;
}

void PatriciaTrie::browse(std::string word, Node* n)
{
    word += n->c;
    for (size_t i = n->index; i < n->length + n->index; ++i)
        word += this->suffixes[i];

    if (n->isWord)
        std::cout << word << " " << n->freq << std::endl;

    for (Node::nodeMap::iterator it = n->sons.begin(); it != n->sons.end(); ++it)
        browse(word, it->second);
}

void PatriciaTrie::print(void)
{
    std::string word("");

    for (Node::nodeMap::iterator it = this->root->sons.begin();
            it != this->root->sons.end();
            ++it)
        browse(word, it->second);
}

Node* PatriciaTrie::burstDown(size_t index, size_t i, size_t freq, Node* n)
{
    char c = this->suffixes[index + i];
    Node* newNode = nullptr;

    newNode = new Node(index, freq, i, n->c);

    n->length -= i + 1;
    n->c = c;
    n->index = index + i + 1;

    newNode->sons[c] = n;

    return newNode;
}

int PatriciaTrie::add(std::string word, int freq, Node* t)
{
    Node* n = nullptr;
    char firstC = word[0];

    Node::nodeMap::iterator it = t->sons.find(firstC);
    if (it != t->sons.end())
        n = it->second;

    if (n != nullptr) // If prefix letter exists
    {
        size_t i = 0;
        // Look in suffixes if the tail of the word is already registered
        while (i < n->length && (i + 1) < word.length() &&
                suffixes[n->index + i] == word[i + 1])
            ++i;

        if (i == n->length) // They share the same prefix
        {
            // "Test" was there and we add "tester". Now the node is stil "test" and
            // node below is "er" (not contiguous in memory).
            std::string leftOver = word.substr(i + 1, word.length() - i - 1);

            if (leftOver.length() > 0) // Else we had a duplicate.
                add(leftOver, freq, n);
        }
        else
        {
            // "Tester" was there and we add "test". Now the node is "test" and
            // node below is "er" contiguous in suffixes.
            Node* tmp;
            if ((tmp = burstDown(n->index, i, freq, n)) != nullptr)
                t->sons[firstC] = tmp;

            std::string leftOver = word.substr(i + 1, word.length() - i - 1);

            if (leftOver.length() > 0) // Else we had a duplicate.
                add(leftOver, freq, tmp);
        }
    }
    else // We create a leaf.
    {
        t->sons[firstC] = new Node(suffixes.size(), freq, word.length() - 1,
                firstC);
        t->sons[firstC]->isWord = true;

        // t->sons[firstC]->print();

        //std::cout << word << std::endl;
        for (std::string::const_iterator it = word.begin() + 1; it != word.end(); ++it)
        {
            //std::cout << *it;
            suffixes.push_back(*it);
        }
        //std::cout << std::endl;
    }

    return 0;
}

int PatriciaTrie::compile(void)
{
    std::ifstream file(filename, std::ios::in);

    if (file)
    {
        std::string line;

        // Read file
        while (std::getline(file, line))
        {
            std::string word;
            int freq;
            std::istringstream ss(line);

            // Get word and frequency for this line
            ss >> word >> freq;
            //std::cout << word << std::endl;

            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            add(word, freq, this->root);
        }

        file.close();
    }
    else
    {
        std::cerr << "Error - Cannot open file: '" << filename;
        std::cerr << "'" << std::cout;
        return -1;
    }
    return 0;
}
